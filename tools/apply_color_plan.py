#!/usr/bin/env python3
"""把「敘述顏色規劃」（docs/martial_arts/敘述顏色規劃.xlsx）的主色套到技能檔的敘述上（使用者指示，2026-11-20）。

規劃表每列有：主色（整句的顏色）、輔色（句中要強調的部分），文字用範例名稱（無聊的傢伙、石假人…）。
這個工具把每一列對到技能檔裡的那句敘述，把整句的色碼換成主色（句尾補 NOR）。
輔色的部分（招名等）形式各異，由引擎或人工處理，不在這裡。

用法：python3 tools/apply_color_plan.py [--apply]     沒加 --apply 只列出會改哪些
"""
from pathlib import Path
import argparse, re, sys
sys.path.insert(0, str(Path(__file__).resolve().parent))
import build_narration_page as b
import openpyxl

ROOT = b.ROOT
PLAN = ROOT / 'docs/martial_arts/敘述顏色規劃.xlsx'
HOLD = {'HIK'}       # 使用者要先看模擬再決定的色碼：含這些色碼的列先不動
SKIP_ROWS = {119}    # 茅山法術的符紙：第二組（158-160 列，含輔色）取代第一組的整句 CYN


def load_plan():
    ws = openpyxl.load_workbook(PLAN).active
    rows, art = [], None
    for r in range(2, ws.max_row + 1):
        a, bb, c = ws.cell(r, 1).value, ws.cell(r, 2).value, ws.cell(r, 3).value
        if c and not a:
            art = c; continue
        if c and a:
            rows.append(dict(row=r, art=art, main=a, acc=bb, text=c.strip()))
    return rows


def art_matches(plan_art, art_name):
    a, n = plan_art.replace('【', '').replace('】', ''), art_name.replace('【', '').replace('】', '')
    return a in n or n in a or a[:3] == n[:3]


def collect():
    """每個技能檔的敘述：(範例純文字, 檔案, 內容, 符號串)。"""
    out = []
    for a in b.pick_arts():
        if not a['file'].endswith('.c'):
            continue
        src = (b.SKILL / a['file']).read_text(encoding='utf-8')
        toks, defines = b.tokenize(src)
        toks = b.expand(toks, defines)
        weapon = b.WEAPON.get(a['cat'], '')
        for c in b.extract(toks):
            label = b.label_for(c)
            plain = b.plain_text(b.render_items(c['items'], weapon, False, label == '招式'))
            out.append(dict(art=a['name'], file=a['file'], text=plain.strip(), ctx=c, toks=toks, label=label))
    return out


def set_main(path, src, toks, rs, re_, color):
    """傳回改完的原始碼：這句的第一個色碼換成 color（沒有就補上），句尾補 NOR。"""
    first, last = toks[rs], toks[re_ - 1]
    if first.pos < 0 or last.end < 0:
        return None
    edits = []
    if first.kind == 'color':
        if first.val != color:
            edits.append((first.pos, first.end, color))
    elif first.kind == 'str':
        edits.append((first.pos, first.pos, color + ' '))
    else:
        edits.append((first.pos, first.pos, color + ' + '))
    if not (last.kind == 'color' and last.val == 'NOR'):
        edits.append((last.end, last.end, ' NOR' if last.kind in ('str', 'color') else ' + NOR'))
    for s0, e0, t in sorted(edits, reverse=True):
        src = src[:s0] + t + src[e0:]
    return src


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--apply', action='store_true')
    a = ap.parse_args()
    plan = load_plan()
    cand = collect()
    by_text = {}
    for c in cand:
        by_text.setdefault(c['text'], []).append(c)
    todo, skipped, missing = {}, [], []
    # 先讓「武功名稱對得上」的列認領敘述；名稱對不上的列只能撿剩下的（例如遁甲書那一段裡其實有幻術的句子）
    used_by_art = set()
    for p in plan:
        for c in by_text.get(p['text'], []):
            if art_matches(p['art'], c['art']):
                used_by_art.add(id(c['ctx']))
    for p in plan:
        if p['acc'] or p['main'] == 'NOR' or p['row'] in SKIP_ROWS:
            continue                     # 有輔色的列由引擎或人工處理；主色 NOR 不用動
        if p['main'] in HOLD:
            skipped.append((p['row'], p['art'], p['main'], '先看模擬再決定')); continue
        hits = [c for c in by_text.get(p['text'], []) if art_matches(p['art'], c['art'])]
        if not hits:
            hits = [c for c in by_text.get(p['text'], []) if id(c['ctx']) not in used_by_art]
        if len(hits) != 1:
            missing.append((p['row'], p['art'], p['main'], p['text'][:30], len(hits))); continue
        todo.setdefault(hits[0]['file'], []).append((p, hits[0]))
    print('可自動套用的列：', sum(len(v) for v in todo.values()), '（檔案', len(todo), '）')
    print('先不動（HIK）：', len(skipped), '；找不到或對不唯一：', len(missing))
    for m in missing: print('  需人工', m)
    if not a.apply:
        for f, items in todo.items():
            for p, c in items:
                print(f'  {f}:{c["ctx"]["line"]} 第{p["row"]}列 {p["art"]} -> {p["main"]}  {p["text"][:28]}')
        return
    for f, items in todo.items():
        path = b.SKILL / f
        src = path.read_text(encoding='utf-8')
        # 由後往前改，避免位置跑掉
        for p, c in sorted(items, key=lambda x: x[1]['toks'][x[1]['ctx']['rs']].pos, reverse=True):
            new = set_main(path, src, c['toks'], c['ctx']['rs'], c['ctx']['re'], p['main'])
            if new is not None:
                src = new
        path.write_text(src, encoding='utf-8')
    print('已套用')


if __name__ == '__main__':
    main()
