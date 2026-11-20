#!/usr/bin/env python3
"""產生「武功敘述總表」彩色網頁：docs/martial_arts/敘述總表.html（使用者指示，2026-11-19）。

把新版武功（daemon/skill 裡用新版武功引擎寫的武功，以及新寫的閃躲、內功）所有會出現在遊戲裡的敘述
整理成一頁：招式、招架、閃避、perform、機率觸發的特效、練成訊息等；依基礎技能分類。
顏色用 include/ansi.h 的色碼、斷行照 cjk_wrap()（寬度 70，色碼的字元也算寬度）與 message_vision 的
nowrap 設定，盡量與遊戲裡看到的一致。每句標出來源檔案與行號、用到的色碼，方便指定要改的顏色。

用法：python3 tools/build_narration_page.py
"""
from pathlib import Path
import html, json, re, sys

ROOT = Path(__file__).resolve().parents[1]
MUD = ROOT / 'source/upstream/mudlib'
SKILL = MUD / 'daemon/skill'
OUT = ROOT / 'docs/martial_arts/敘述總表.html'
SPELLS_JSON = ROOT / 'docs/martial_arts/法術敘述擷取.json'   # tools/capture_spell_narration.py 產生

# ---------------------------------------------------------------- 範圍與分類

# 基礎技能分類（顯示順序、中文名）。武功放在它主要 enable 的那一類，其他 enable 以標籤顯示。
CATEGORIES = [
    ('unarmed', '徒手'), ('sword', '劍術'), ('twohanded sword', '雙手劍'), ('secondhand sword', '副手劍'),
    ('blade', '刀法'), ('twohanded blade', '雙手刀'), ('staff', '杖法'), ('twohanded staff', '雙握杖法'),
    ('pike', '槍法'), ('twohanded pike', '雙手槍'), ('axe', '斧術'), ('twohanded axe', '雙手斧'),
    ('dagger', '錐法'), ('secondhand dagger', '副手錐法'), ('parry', '招架'), ('dodge', '閃躲'), ('force', '內功'),
    ('magic', '法術'), ('spells', '咒術'), ('cauterization', '灸術'),
]
CAT_NAME = dict(CATEGORIES)
WEAPON = {   # 範例武器名（取代 $w）
    'sword': '青鋼劍', 'twohanded sword': '玄鐵重劍', 'secondhand sword': '短劍', 'blade': '精鋼刀',
    'twohanded blade': '斬馬刀', 'staff': '長杖', 'twohanded staff': '九曲十彎', 'pike': '長槍',
    'twohanded pike': '丈八蛇矛', 'axe': '手斧', 'twohanded axe': '巨斧', 'dagger': '匕首',
    'secondhand dagger': '短匕', 'unarmed': '', 'parry': '兵刃', 'dodge': '', 'force': '',
}
GENERIC = {'axe', 'blade', 'blunt', 'dagger', 'needle', 'pike', 'staff', 'sword', 'whip', 'unarmed'}
SAMPLE = {'$N': '無聊的傢伙', '$n': '石假人', '$P': '他', '$p': '它', '$l': '右臂'}   # 施招的人與被打的練武假人（使用者指示，2026-11-19）

WRAP_WIDTH = 70

# ---------------------------------------------------------------- ansi.h

def load_ansi():
    colors = {}
    for line in (MUD / 'include/ansi.h').read_text(encoding='utf-8').splitlines():
        m = re.match(r'#define\s+([A-Z]+)\s+CSI\s+"([0-9;]+)m"', line)
        if m:
            colors[m.group(1)] = '\x1b[' + m.group(2) + 'm'
    return colors


ANSI = load_ansi()

# ---------------------------------------------------------------- LPC 斷詞與巨集

TOKEN = re.compile(r'''
    (?P<str>"(?:\\.|[^"\\])*")
  | (?P<num>\d+)
  | (?P<id>[A-Za-z_][A-Za-z_0-9]*)
  | (?P<op>->|[^\s])
''', re.X)


def strip_comments(src):
    out, i, n = [], 0, len(src)
    while i < n:
        c = src[i]
        if c == '"':
            j = i + 1
            while j < n and src[j] != '"':
                j += 2 if src[j] == '\\' else 1
            out.append(src[i:j + 1]); i = j + 1
        elif src.startswith('//', i):
            j = src.find('\n', i)
            j = n if j < 0 else j
            out.append(' ' * (j - i))        # 用空白補滿，保持字元位置不變
            i = j
        elif src.startswith('/*', i):
            j = src.find('*/', i + 2)
            j = n if j < 0 else j + 2
            out.append(''.join('\n' if ch == '\n' else ' ' for ch in src[i:j]))
            i = j
        elif src.startswith('@LONG', i) or src.startswith('@HELP', i):
            end = 'LONG' if src.startswith('@LONG', i) else 'HELP'
            j = src.find('\n' + end, i)
            body = src[i + 5:j] if j >= 0 else ''
            out.append('"' + body.strip('\n').replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\n') + '"' + '\n' * body.count('\n'))
            i = (j + 1 + len(end)) if j >= 0 else n
        else:
            out.append(c); i += 1
    return ''.join(out)


def unescape(lit):
    s = lit[1:-1]
    return re.sub(r'\\(.)', lambda m: {'n': '\n', 't': '\t', 'e': '\x1b'}.get(m.group(1), m.group(1)), s)


class Tok:
    __slots__ = ('kind', 'val', 'line', 'pos', 'end')

    def __init__(self, kind, val, line, pos=-1, end=-1):
        self.kind, self.val, self.line, self.pos, self.end = kind, val, line, pos, end

    def __repr__(self):
        return f'{self.kind}:{self.val!r}'


def tokenize(src):
    """傳回 (tokens, defines)。#define 先收集起來、之後在符號串裡展開。"""
    src = strip_comments(src)
    lines = src.split('\n')
    defines = {}
    body = []
    i = 0
    while i < len(lines):
        ln = lines[i]
        i0 = i
        m = re.match(r'\s*#\s*define\s+([A-Za-z_]\w*)(\(([^)]*)\))?\s*(.*)$', ln)
        if m:
            text = m.group(4)
            while text.endswith('\\') and i + 1 < len(lines):
                i += 1
                text = text[:-1] + ' ' + lines[i]
            params = [p.strip() for p in m.group(3).split(',')] if m.group(2) else None
            defines[m.group(1)] = (params, text)
            body.append(' ' * len(lines[i0]))
            for k in range(i0 + 1, i + 1):
                body.append(' ' * len(lines[k]))
        elif re.match(r'\s*#', ln):
            body.append(' ' * len(ln))
        else:
            body.append(ln)
        i += 1
    toks = []
    off = 0
    for ln_no, ln in enumerate(body, 1):
        for m in TOKEN.finditer(ln):
            k = m.lastgroup
            toks.append(Tok(k, m.group(k), ln_no, off + m.start(), off + m.end()))
        off += len(ln) + 1
    return toks, defines


def lex(text, line):
    return [Tok(m.lastgroup, m.group(m.lastgroup), line) for m in TOKEN.finditer(text)]


def expand(toks, defines, depth=0):
    out, i = [], 0
    while i < len(toks):
        t = toks[i]
        if t.kind == 'id' and t.val in ANSI and t.val not in defines:
            out.append(Tok('color', t.val, t.line, t.pos, t.end)); i += 1; continue
        if t.kind == 'id' and t.val in defines and depth < 8:
            params, text = defines[t.val]
            if params is None:
                out += expand(lex(text, t.line), defines, depth + 1); i += 1; continue
            if i + 1 < len(toks) and toks[i + 1].val == '(':
                j, d, args, cur = i + 2, 1, [], []
                while j < len(toks) and d:
                    v = toks[j].val
                    if v == '(' : d += 1
                    elif v == ')':
                        d -= 1
                        if d == 0: break
                    if v == ',' and d == 1:
                        args.append(cur); cur = []
                    else:
                        cur.append(toks[j])
                    j += 1
                args.append(cur)
                body = lex(text, t.line)
                sub = []
                for b in body:
                    if b.kind == 'id' and b.val in params:
                        sub += args[params.index(b.val)] if params.index(b.val) < len(args) else []
                    else:
                        sub.append(b)
                out += expand(sub, defines, depth + 1)
                i = j + 1
                continue
        out.append(t); i += 1
    return out


# ---------------------------------------------------------------- 取出敘述

KEYWORDS = {'if', 'else', 'while', 'for', 'foreach', 'switch', 'case', 'return', 'sizeof', 'catch', 'in', 'int', 'string', 'object', 'mapping', 'mixed', 'void', 'static', 'private', 'varargs', 'float'}


class Run:
    def __init__(self):
        self.items = []     # ('s', text) ('c', name) ('v', 變數名)
        self.line = 0
        self.start = 0
        self.end = 0

    def has_cjk(self):
        return any(k == 's' and re.search(r'[\u3000-\u9fff\uff00-\uffef﹐﹗]', v) for k, v in self.items)


def extract(toks):
    """走過整份符號，傳回敘述清單：dict(text_items, line, func, call, label, name, nowrap, var)。"""
    res = []
    n = len(toks)
    i = 0
    depth = 0
    func = ''
    pstack = []          # 括號堆疊：(前一個識別字, 開括號位置)
    assign = ''
    last_name = ''
    pending_func = None
    while i < n:
        t = toks[i]
        v = t.val
        # 招式表裡的 "name": "招名"：記下招名（招式敘述跟著它）
        if t.kind == 'str' and unescape(t.val) == 'name' and i + 2 < n and toks[i + 1].val == ':' and toks[i + 2].kind == 'str':
            last_name = unescape(toks[i + 2].val)
        if t.kind in ('str', 'color') or (t.kind == 'id' and t.val not in KEYWORDS and run_can_start(toks, i)):
            # 從 i 開始收一串連續敘述
            run = Run(); run.line = t.line; run.start = i
            j = i
            while j < n:
                u = toks[j]
                if u.kind == 'str':
                    run.items.append(('s', unescape(u.val))); j += 1
                elif u.kind == 'color':
                    run.items.append(('c', u.val)); j += 1
                elif u.val == '+' and j + 1 < n and (toks[j + 1].kind in ('str', 'color', 'id') or toks[j + 1].val == '(') and run.items:
                    j += 1
                elif u.kind == 'id' and u.val not in KEYWORDS and run.items and (toks[j - 1].val == '+' or toks[j - 1].kind in ('str', 'color')):
                    # 變數或函式呼叫當作占位
                    k = j + 1
                    name = u.val
                    while k < n and toks[k].val == '->' and k + 1 < n and toks[k + 1].kind == 'id':
                        name += '->' + toks[k + 1].val; k += 2
                    if k < n and toks[k].val == '(':
                        d = 1; k += 1
                        while k < n and d:
                            if toks[k].val == '(': d += 1
                            elif toks[k].val == ')': d -= 1
                            k += 1
                        name += '()'
                    if k < n and toks[k].val in ('[',):
                        d = 1; k += 1
                        while k < n and d:
                            if toks[k].val == '[': d += 1
                            elif toks[k].val == ']': d -= 1
                            k += 1
                        name += '[]'
                    run.items.append(('v', name)); j = k
                elif u.val == '(' and run.items and toks[j - 1].val == '+':
                    # 加號後面的括號運算式（三元運算、陣列選一句…）當作占位；全是字串時列出選項
                    k, d, strs, plain_only = j + 1, 1, [], True
                    while k < n and d:
                        w = toks[k]
                        if w.val == '(': d += 1
                        elif w.val == ')': d -= 1
                        if w.kind == 'str': strs.append(unescape(w.val))
                        elif w.kind == 'id' or w.val in ('?', ':'):
                            plain_only = plain_only and w.val in ('?', ':') or False
                        k += 1
                    while k < n and toks[k].val == '[':
                        d2 = 1; k += 1
                        while k < n and d2:
                            if toks[k].val == '[': d2 += 1
                            elif toks[k].val == ']': d2 -= 1
                            k += 1
                    has_q = any(toks[x].val == '?' for x in range(j + 1, k))
                    run.items.append(('v', 'wn' if has_q else ('／'.join(strs) if strs else '運算式'))); j = k
                else:
                    break
            run.end = j
            if run.has_cjk():
                ctx = dict(
                    items=run.items, line=run.line, func=func, assign=assign, last_name=last_name,
                    call='', nowrap=False, prev=[x.val for x in toks[max(0, i - 3):i]], rs=run.start, re=run.end,
                )
                # 最近的呼叫
                for ident, pos in reversed(pstack):
                    if ident and ident not in KEYWORDS:
                        ctx['call'] = ident
                        ctx['call_pos'] = pos
                        break
                if ctx['call'] == 'message_vision':
                    ctx['nowrap'] = call_nowrap(toks, ctx['call_pos'])
                res.append(ctx)
            i = max(j, i + 1)
            continue
        # 非敘述符號：維護狀態
        if v == '(':
            prev = toks[i - 1].val if i and toks[i - 1].kind == 'id' else ''
            pstack.append((prev, i))
        elif v == ')':
            if pstack: pstack.pop()
        elif v == '{':
            if depth == 0 and pending_func:
                func = pending_func
            depth += 1
        elif v == '}':
            depth -= 1
            if depth == 0:
                func = ''
        elif v == ';':
            assign = ''
        elif v == '=' and i and toks[i - 1].kind == 'id':
            assign = toks[i - 1].val
        elif t.kind == 'str' or True:
            pass
        # 函式定義：頂層 id ( ... ) {
        if depth == 0 and t.kind == 'id' and i + 1 < n and toks[i + 1].val == '(' and t.val not in KEYWORDS:
            d, k = 1, i + 2
            while k < n and d:
                if toks[k].val == '(': d += 1
                elif toks[k].val == ')': d -= 1
                k += 1
            if k < n and toks[k].val == '{':
                pending_func = t.val
        # moves 的招式名
        if t.kind == 'str' and unescape(t.val) == 'name' and i + 2 < n and toks[i + 1].val == ':' and toks[i + 2].kind == 'str':
            last_name = unescape(toks[i + 2].val)
        i += 1
    return res


def run_can_start(toks, i):
    """識別字只有在「＋ 變數」之後才算敘述的一部分，不能自己起頭。"""
    return False


def call_nowrap(toks, pos):
    """message_vision( msg, me, you, nowrap )：第四個參數不是 0 就是不斷行。"""
    d, j, args, cur = 1, pos + 1, [], []
    while j < len(toks) and d:
        v = toks[j].val
        if v in '([{': d += 1
        elif v in ')]}':
            d -= 1
            if d == 0: break
        if v == ',' and d == 1:
            args.append(cur); cur = []
        else:
            cur.append(toks[j])
        j += 1
    args.append(cur)
    return len(args) >= 4 and ''.join(t.val for t in args[3]).strip() not in ('', '0')


# ---------------------------------------------------------------- 武功清單

def art_info(path):
    src = path.read_text(encoding='utf-8')
    name = path.stem
    cname = re.search(r'art_name\s*=\s*"([^"]+)"', src)
    usage = re.search(r'art_usage\s*=\s*"([^"]+)"', src)
    ma = 'inherit "/std/martial_art"' in src
    enables = []
    m = re.search(r'valid_enable\s*\([^)]*\)\s*(\{.*?\n\}|[^;{]*;)', src, re.S)
    if m:
        enables = [u for u in re.findall(r'"([a-z ]+)"', m.group(1)) if u in CAT_NAME]
    return dict(file=path.name, ma=ma, cname=cname.group(1) if cname else None,
                usage=usage.group(1) if usage else None, enables=enables, src=src)


def chinese_names():
    s = (MUD / 'data/chinese.o').read_text(encoding='utf-8', errors='replace')
    return dict(re.findall(r'"([^"]+)":"([^"]*)"', s))


NEEDLES = ('amazing-needle', 'wuto-needle', 'potency-needle', 'recovery-needle')   # 武陀灸堂針法（沒有 valid_enable，用 acupuncture 指令）


def pick_arts():
    cn = chinese_names()
    arts = []
    for p in sorted(SKILL.glob('*.c')):
        stem = p.stem
        if stem in GENERIC or stem.startswith(('twohanded_', 'secondhand_')):
            continue
        a = art_info(p)
        if stem in NEEDLES:
            a['enables'] = ['cauterization']
        cat = a['usage'] if a['ma'] else (a['enables'][0] if a['enables'] else None)
        if a['ma'] and a['usage'] and a['usage'] not in CAT_NAME:
            cat = a['usage']
        if cat not in CAT_NAME:
            continue
        if not a['ma'] and cat not in ('dodge', 'force', 'magic', 'spells', 'cauterization'):
            continue
        if stem.startswith('taoism-'):   # 天師四破的共用程式與四個外殼：施咒過程見「法術 cast」的實際畫面
            continue
        a['cat'] = cat
        a['name'] = a['cname'] or cn.get(stem.replace('_', ' ')) or cn.get(stem) or stem
        a['stem'] = stem
        arts.append(a)
    hdr = SKILL / 'wuto_needle.h'      # 針法共用的函式與敘述
    if hdr.exists():
        a = art_info(hdr)
        a.update(cat='cauterization', enables=['cauterization'], name='針法共用（施針的共通敘述）', stem='wuto needle', file=hdr.name)
        arts.append(a)
    return arts


# ---------------------------------------------------------------- 排版（照 cjk_wrap）

NO_LINE_START = set('﹗！？﹖，﹐。﹒、；﹔：﹕」』）】〉》…')


def cjk_wrap(s, width):
    if width < 1:
        return s
    out, ll, prev_w = [], 0, 0
    for ch in s:
        w = 2 if len(ch.encode('utf-8')) > 1 else 1
        if ch in '\n\r':
            out.append(ch); ll = 0
            continue
        prev_w = w
        if w > 1 or ch == ' ':
            if ll + w > width and ch not in NO_LINE_START:
                out.append('\n'); ll = 0
        if ch == ' ' and ll == 0:
            continue
        out.append(ch)
        ll += 8 - (ll % 8) if ch == '\t' else w
    return ''.join(out)


def plain_text(s):
    """給複製按鈕用的字串：拿掉色碼與結尾的換行；沒有加上任何排版用的斷行。"""
    return re.sub(r'\x1b\[[0-9;]*m', '', s).rstrip('\n')


def attr(s):
    return html.escape(s, quote=True).replace('\n', '&#10;')


def render_items(items, weapon, raw, dummy_hit=False):
    """把敘述項目組成帶真實 ESC 碼的字串；raw 為 True 時保留 $N 等變數。"""
    parts = []
    for k, v in items:
        if k == 's':
            parts.append(v)
        elif k == 'c':
            parts.append(ANSI[v])
        elif v in ('wn', 'hold', 'wname', 'weapon_name', 'weapon_name()', 'w->name()', 'weapon->name()') and not raw:
            parts.append(weapon or '兵刃')
        else:
            parts.append('〔' + v + '〕')
    s = ''.join(parts)
    if dummy_hit and not raw:
        # 對練武假人出招：戰鬥系統拿掉部位（combatd.c 的 training_dummy 處理）
        s = s.replace('$n的$l', '$n').replace('$n$l', '$n').replace('$l', '$n')
    if not raw:
        for a, b in SAMPLE.items():
            s = s.replace(a, b)
        s = s.replace('$w', weapon or '兵刃')
    return s


PALETTE = {
    '30': '#555555', '31': '#cc3333', '32': '#33aa33', '33': '#b58900', '34': '#3d5afe', '35': '#bb44bb',
    '36': '#22aaaa', '37': '#bbbbbb',
}
BRIGHT = {
    '30': '#888888', '31': '#ff5555', '32': '#55ff55', '33': '#ffff55', '34': '#6f8cff', '35': '#ff77ff',
    '36': '#55ffff', '37': '#ffffff',
}


def to_html(s):
    """把帶 ESC 碼的字串轉成 HTML；回傳 (html, 用到的色碼名稱)。"""
    out, cur, open_span = [], None, False
    names = []
    inv = {v: k for k, v in ANSI.items()}
    pos = 0
    for m in re.finditer(r'\x1b\[([0-9;]*)m', s):
        out.append(html.escape(s[pos:m.start()]))
        pos = m.end()
        code = m.group(1)
        if open_span:
            out.append('</span>'); open_span = False
        nm = inv.get('\x1b[' + code + 'm')
        if nm and nm not in names:
            names.append(nm)
        if code in ('0', ''):
            continue
        parts = code.split(';')
        bold = '1' in parts
        fg = [p for p in parts if p in PALETTE]
        if fg:
            color = (BRIGHT if bold else PALETTE)[fg[0]]
            out.append(f'<span style="color:{color}">'); open_span = True
        elif bold:
            out.append('<span style="font-weight:700">'); open_span = True
    out.append(html.escape(s[pos:]))
    if open_span:
        out.append('</span>')
    return ''.join(out), names


# ---------------------------------------------------------------- 標籤

FUNC_LABEL = {
    'parry_message': '招架敘述', 'dodge_using': '閃避敘述', 'parry_success': '招架成功特效',
    'attack_using': '出招特效', 'after_strike': '出招後特效', 'perform_action': 'perform',
    'skill_completed': '練成訊息', 'skill_advanced': '升級訊息', 'exert_function': '內功指令',
    'valid_learn': '學習條件提示', 'do_exercise': '修習', 'do_refresh': 'refresh', 'do_recover': 'recover',
    'do_armor': 'armor', 'do_powerup': 'powerup', 'remove_armor': '效果結束', 'remove_powerup': '效果結束',
}
EXTRA_LABEL = {   # 個別武功檔裡的函式名稱 → 說明（找不到的直接標函式名稱）
    'do_reflect': '反震', 'do_crazy': 'perform crazy（殘蟻瘋魔杖）', 'do_stun': 'perform stun（哭笑不得也）',
    'do_hide': 'perform hide（殘蟻逐食杖）', 'hide_burst': 'perform hide 的爆發',
}
ASSIGN_LABEL = {'dodge_actions': '閃避敘述', 'art_entry_msg': '練成訊息', 'level_msgs': '升級訊息', 'mm_first_msg': '武學之道訊息'}


def label_for(c):
    prev = c['prev']
    if len(prev) >= 2 and prev[-1] == ':' and prev[-2] == '"action"':
        return '招式'
    if c['assign'] in ASSIGN_LABEL:
        return ASSIGN_LABEL[c['assign']]
    if c['func'] in FUNC_LABEL:
        return FUNC_LABEL[c['func']]
    if c['call'] == 'notify_fail':
        return '提示'
    f = c['func']
    if f in EXTRA_LABEL:
        return EXTRA_LABEL[f]
    return ('特效・' + f) if f else (c['assign'] or '訊息')


def channel_for(c, label):
    if label in ('招式', '招架敘述', '閃避敘述'):
        return '戰鬥訊息：整句一行（接在戰鬥敘述裡，不斷行）'
    if c['call'] == 'message_vision':
        return '一行不斷行（nowrap）' if c['nowrap'] else '依寬度 70 斷行（cjk_wrap）'
    if c['call'] in ('tell_object', 'write', 'notify_fail', 'message'):
        return {'tell_object': '只給當事人看（不自動斷行）', 'write': '只給當事人看（不自動斷行）',
                'notify_fail': '提示（不自動斷行）'}.get(c['call'], '不自動斷行')
    return '不自動斷行'


# ---------------------------------------------------------------- 主程式

def engine_colorize(a, name, text, raw=False):
    """照 std/martial_art.c 的 colorize_action()：整句主色、招名輔色（緊貼的括號一起上色），句尾補 NOR。"""
    m_main = re.search(r'art_main_color\s*=\s*([A-Z]+)\s*;', a['src'])
    m_name = re.search(r'art_name_color\s*=\s*([A-Z]+)\s*;', a['src'])
    if not (m_main or m_name):
        return text
    main = ANSI[m_main.group(1)] if m_main else ''
    restore = ANSI['NOR'] + main
    if m_name and name:
        target = None
        for l, r in (('「', '」'), ('『', '』'), ('【', '】')):
            if l + name + r in text:
                target = l + name + r; break
        if target is None and name in text:
            target = name
        if target:
            text = text.replace(target, ANSI[m_name.group(1)] + target + restore)
    return main + text + ANSI['NOR']


def build():
    arts = pick_arts()
    data = {}   # cat -> list of arts
    for a in arts:
        toks, defines = tokenize(a['src'])
        toks = expand(toks, defines)
        found = extract(toks)
        weapon = WEAPON.get(a['cat'], '')
        entries = []
        seen = set()
        for c in found:
            items = c['items']
            label = label_for(c)
            raw = render_items(items, weapon, True)
            plain = ''.join(v for k, v in items if k == 's')
            has_color = any(k == 'c' for k, v in items)
            # 招式名、傷害類型、簡介、perform 名稱這類資料字串不是敘述
            if label == 'create' or c['func'] == 'create' and label != '招式' and c['assign'] not in ASSIGN_LABEL:
                continue
            if len(plain) <= 6 and not re.search(r'[﹐。！？﹗「」$]', plain) and not has_color:
                continue
            if label in ('學習條件提示', '提示') and not re.search(r'[\u4e00-\u9fff]', raw):
                continue
            key = (raw, label)
            if key in seen:
                continue
            seen.add(key)
            sample = render_items(items, weapon, False, label == '招式')
            raw_s = raw
            if label == '招式':
                sample = engine_colorize(a, c['last_name'], sample)
                raw_s = engine_colorize(a, c['last_name'], raw, raw=True)
            channel = channel_for(c, label)
            nowrap = channel.startswith(('戰鬥訊息', '一行', '只給', '提示', '不自動'))
            wrapped = sample if nowrap else cjk_wrap(sample, WRAP_WIDTH)
            raw_wrapped = raw_s if nowrap else cjk_wrap(raw_s, WRAP_WIDTH)
            h_sample, names = to_html(wrapped)
            h_raw, _ = to_html(raw_wrapped)
            entries.append(dict(label=label, name=c['last_name'] if label == '招式' else '', line=c['line'],
                                sample=h_sample, raw=h_raw, colors=names, channel=channel,
                                copy_s=plain_text(sample), copy_r=plain_text(raw_s)))
        a['entries'] = entries
        data.setdefault(a['cat'], []).append(a)
    return data


# ---------------------------------------------------------------- 職業、門派

CLASS_ORDER = [('fighter', '武者'), ('taoist', '道士'), ('scholar', '書生'), ('alchemist', '方士'),
               ('soldier', '軍人'), ('thief', '盜賊'), ('monk', '和尚')]
CLASS_OF_PREFIX = {'fighter': 'fighter', 'taoist': 'taoist', 'mao-shan': 'taoist', 'scholar': 'scholar',
                   'alchemist': 'alchemist', 'soldier': 'soldier', 'thief': 'thief', 'monk': 'monk'}


def norm(x):
    return re.sub(r'[\s_\-]+', ' ', x.lower()).strip()


def load_factions():
    """依門派武功對照表與 npc_skill.c：傳回 (門派清單[(職業, 門派)], 技能代碼 -> (職業, 門派))。"""
    doc = (ROOT / 'docs/martial_arts/門派武功對照表.md').read_text(encoding='utf-8')
    order, code_of = [], {}
    sect = doc.split('## 武功一覽')[0]
    for m in re.finditer(r'^\| ([^|]+?) \| `([a-z0-9\-]+)\.[a-z0-9\-]+` \|', sect, re.M):
        name, pre = m.group(1).strip(), m.group(0)
        prefix = re.search(r'`([a-z0-9\-]+)\.', pre).group(1)
        cls = CLASS_OF_PREFIX.get(prefix)
        if cls:
            order.append((cls, name)); code_of[name] = cls
    skill_of = {}
    for m in re.finditer(r'^\| ([^|]+?) \| ([^|]+?) \| `([^`]+)` \|', doc.split('## 武功一覽')[1], re.M):
        owner, code = m.group(1).strip(), m.group(3).strip()
        if owner in code_of:
            skill_of.setdefault(norm(code), (code_of[owner], owner))
    # npc_skill.c 的門派表補上對照表沒寫到的
    src = (MUD / 'daemon/misc/npc_skill.c').read_text(encoding='utf-8')
    for fm in re.finditer(r'"([a-z\-]+)\.([a-z0-9\-]+)": \(\[(.*?)\n    \]\),', src, re.S):
        cls = CLASS_OF_PREFIX.get(fm.group(1))
        nm = re.search(r'"name":\s*"([^"]+)"', fm.group(3))
        if not cls or not nm:
            continue
        key = (cls, nm.group(1))
        if key not in order:
            order.append(key)
        for sk in re.findall(r'"(?:skill|force)":\s*"([^"]+)"', fm.group(3)):
            skill_of.setdefault(norm(sk), key)
    # 設計文件指定、但對照表沒列到的門派武功（docs/martial_arts/瑯夷派_蝶影幻步.md、龍圖丹派_竹上經心法.md）
    for sk, key in (('butterfly steps', ('thief', '瑯夷派')), ('zushang', ('alchemist', '龍圖丹派')), ('wuto needle', ('alchemist', '武陀灸堂'))):
        skill_of.setdefault(sk, key)
    return order, skill_of


def art_ids(a):
    ids = {norm(a['stem'])}
    for pat in (r'art_id\s*=\s*"([^"]+)"', r'register_skill_daemon\("([^"]+)"\)'):
        for x in re.findall(pat, a['src']):
            ids.add(norm(x))
    return ids


def art_section(a, cat_note=True):
    extra = [CAT_NAME[e] for e in a['enables'] if e != a['cat'] and e in CAT_NAME]
    sub = (f'<small>{html.escape(CAT_NAME.get(a["cat"], ""))} · {html.escape(a["stem"])} · {html.escape(a["file"])}'
           + (f' · 也可 enable：{html.escape("、".join(extra))}' if extra else '') + '</small>')
    body = [f'<details class="art" open><summary><span class="t">{html.escape(a["name"])}</span>{sub}</summary>']
    if not a['entries']:
        body.append('<p class="empty">（沒有可顯示的敘述）</p>')
    last_label = None
    for e in a['entries']:
        if e['label'] != last_label:
            body.append(f'<h4>{html.escape(e["label"])}</h4>')
            last_label = e['label']
        tag = f'<span class="meta">{html.escape(e["channel"])} · {html.escape(a["file"])}:{e["line"]}'
        if e['colors']:
            tag += ' · 色碼 ' + ' '.join(html.escape(x) for x in e['colors'])
        tag += '</span>'
        nm = f'<span class="mv">{html.escape(e["name"])}</span>' if e['name'] else ''
        btn = f'<button class="cp" type="button" title="複製這句敘述" data-s="{attr(e["copy_s"])}" data-r="{attr(e["copy_r"])}">複製</button>'
        body.append(f'<div class="ent">{btn}<div class="bd">{nm}<pre class="s">{e["sample"]}</pre><pre class="r">{e["raw"]}</pre>{tag}</div></div>')
    body.append('</details>')
    return ''.join(body)


def spell_sections():
    """法術 cast：技能代碼 -> [(標題, html)]；每道法術一個格子，照遊戲實際顯示（含前後空行、色碼、斷行）。"""
    if not SPELLS_JSON.exists():
        return {}
    items = json.loads(SPELLS_JSON.read_text(encoding='utf-8'))
    res = {}
    for it in items:
        h, names = to_html(it['text'])
        lines = h.split('\n')
        body = ''.join(f'<div class="ln">{ln if ln else "&nbsp;"}</div>' for ln in lines)
        plain = plain_text(it['text'])
        btn = f'<button class="cp" type="button" title="複製這個指令的完整畫面" data-s="{attr(plain)}" data-r="{attr(plain)}">複製</button>'
        box = (f'<div class="ent spell">{btn}<div class="bd"><span class="mv">{html.escape(it["spell_cname"])}</span>'
               f'<div class="cmd">&gt; {html.escape(it["command"])}</div><div class="box">{body}</div>'
               f'<span class="meta">{"色碼 " + " ".join(names) if names else "無色碼"} · 畫面共 {len(lines)} 行（含前後空行）</span></div></div>')
        res.setdefault((it['school'], it['school_cname']), []).append(box)
    return res


def details(cls_name, title, inner, level, did, count):
    return (f'<details class="{cls_name}" id="{did}" open><summary><span class="t">{html.escape(title)}</span>'
            f'<span class="c">{count}</span></summary>{inner}</details>')


def page(data):
    order, skill_of = load_factions()
    arts = [a for v in data.values() for a in v]
    spells = spell_sections()
    tree = {}      # (職業, 門派) -> [html...]
    generic = []   # 通用：(類別, art)
    counts = {}
    for a in arts:
        key = None
        for i in sorted(art_ids(a)):
            if i in skill_of:
                key = skill_of[i]; break
        if key is None:
            generic.append(a); continue
        tree.setdefault(key, []).append(a)
    spell_tree, spell_generic = {}, []
    for (sid, scname), boxes in spells.items():
        key = skill_of.get(norm(sid))
        (spell_tree.setdefault(key, []) if key else spell_generic).append((scname, sid, boxes))
    nav, body = [], []
    total = sum(len(a['entries']) for a in arts)

    def spell_block(lst):
        out = []
        for scname, sid, boxes in lst:
            out.append(f'<details class="art" open><summary><span class="t">{html.escape(scname)}</span><small>實際畫面 · {html.escape(sid)}</small></summary>{"".join(boxes)}</details>')
        return ''.join(out)

    for cls, cname in CLASS_ORDER:
        facs = [f for (c, f) in order if c == cls and ((c, f) in tree or (c, f) in spell_tree)]
        if not facs:
            continue
        inner, ncls = [], 0
        for f in facs:
            fa = tree.get((cls, f), [])
            fa = sorted(fa, key=lambda a: [c for c, _ in CATEGORIES].index(a['cat']) if a['cat'] in CAT_NAME else 99)
            html_f = ''.join(art_section(a) for a in fa) + spell_block(spell_tree.get((cls, f), []))
            n = sum(len(a['entries']) for a in fa) + sum(len(b) for _, _, b in spell_tree.get((cls, f), []))
            ncls += n
            inner.append(details('fac', f, html_f, 2, f'fac-{cls}-{facs.index(f)}', f'{len(fa)} 套武功' + (f'、{sum(len(x[2]) for x in spell_tree.get((cls, f), []))} 道法術' if spell_tree.get((cls, f)) else '')))
        did = f'cls-{cls}'
        nav.append(f'<a href="#{did}">{html.escape(cname)}</a>')
        body.append(details('cls', cname, ''.join(inner), 1, did, f'{len(facs)} 個門派'))
    # 沒有對應到門派的法術也放通用
    inner = []
    for cat, cn in CATEGORIES:
        ga = [a for a in generic if a['cat'] == cat]
        if ga:
            inner.append(details('fac', cn, ''.join(art_section(a) for a in ga), 2, f'gen-{re.sub(r"[^a-z]+", "-", cat)}', f'{len(ga)} 套武功'))
    if spell_generic:
        inner.append(details('fac', '法術', spell_block(spell_generic), 2, 'gen-spells', f'{len(spell_generic)} 系'))
    if inner:
        nav.append('<a href="#cls-generic">通用</a>')
        body.append(details('cls', '通用', ''.join(inner), 1, 'cls-generic', f'{len(generic)} 套武功'))
    palette = ''.join(
        f'<span class="sw"><i style="background:{(BRIGHT if k.startswith("HI") else PALETTE)[ANSI[k].split("[")[1].rstrip("m").split(";")[-1]]}"></i>{k}</span>'
        for k in ['BLK', 'RED', 'GRN', 'YEL', 'BLU', 'MAG', 'CYN', 'WHT', 'HIK', 'HIR', 'HIG', 'HIY', 'HIB', 'HIM', 'HIC', 'HIW'])
    return PAGE.format(total=total, palette=palette, nav=''.join(nav), body=''.join(body))


PAGE = '''<!doctype html><html lang="zh-Hant"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>武功敘述總表</title>
<style>
:root{{color-scheme:dark;--bg:#0d1012;--panel:#15191c;--line:#2a3035;--ink:#d6d9dc;--muted:#8a939b;--term:#000;--t:#c9c9c9}}
body{{margin:0;background:var(--bg);color:var(--ink);font:15px/1.6 "Noto Sans TC","PingFang TC","Microsoft JhengHei",system-ui,sans-serif;padding:16px 16px 60px}}
.wrap{{max-width:1000px;margin:0 auto}}
h1{{font-size:1.4rem;margin:0 0 6px}}p.n{{color:var(--muted);font-size:.88rem;margin:4px 0}}
.top{{position:sticky;top:0;z-index:5;background:var(--bg);padding:6px 0 0;margin-top:8px}}
.pal{{line-height:1.9}}
nav{{display:flex;flex-wrap:wrap;gap:6px 14px;margin:6px 0 0;padding:6px 0 8px;border-bottom:1px solid var(--line)}}
nav a{{color:#8fb4ff;text-decoration:none;font-size:.9rem}}
.bar{{display:flex;gap:14px;flex-wrap:wrap;align-items:center;margin:2px 0 4px;font-size:.88rem}}
.bar button{{background:#1d2328;color:var(--ink);border:1px solid #38424a;border-radius:4px;padding:3px 10px;font:inherit;cursor:pointer}}
.bar button:hover{{background:#26303a}}
.sw{{display:inline-flex;align-items:center;gap:4px;margin-right:10px;font-family:monospace;font-size:.8rem}}.sw i{{width:12px;height:12px;display:inline-block;border:1px solid #444}}
details{{scroll-margin-top:150px}}
details.cls{{margin:18px 0 8px;border:1px solid var(--line);border-radius:8px;padding:0 10px 8px;background:#10151a}}
details.cls>summary{{font-size:1.15rem;font-weight:700;padding:8px 2px}}
details.art{{background:var(--panel);border:1px solid var(--line);border-radius:6px;padding:0 14px 12px;margin:10px 0}}
details.art:not([open]){{padding-bottom:0}}
details.art>summary{{font-size:1rem;font-weight:600;padding:8px 0}}
details.art>summary small{{color:var(--muted);font-weight:400;font-size:.75rem;margin-left:10px}}
details.fac{{margin:10px 0 4px;border-left:3px solid #3a4650;padding:0 0 0 10px}}
details.fac>summary{{font-size:1.02rem;font-weight:600;padding:5px 2px;color:#c9d6e2}}
summary{{cursor:pointer;list-style:none}}summary::-webkit-details-marker{{display:none}}
summary::before{{content:"\\25BE";display:inline-block;width:1.1em;color:#8fb4ff}}details:not([open])>summary::before{{content:"\\25B8"}}
summary .c{{color:var(--muted);font-weight:400;font-size:.78rem;margin-left:10px}}
h3{{font-size:1rem;margin:16px 0 4px}}h3 small{{color:var(--muted);font-weight:400;font-size:.75rem;margin-left:10px}}h4{{font-size:.85rem;color:#c79a5a;margin:12px 0 4px}}
.ent{{margin:6px 0;display:flex;gap:8px;align-items:flex-start}}.ent .bd{{flex:1;min-width:0}}.cp{{flex:none;min-width:58px;text-align:center;margin-top:4px;background:#1d2328;color:#9fc0ff;border:1px solid #38424a;border-radius:4px;padding:2px 8px;font:12px inherit;cursor:pointer}}.cp:hover{{background:#26303a}}.cp.ok{{color:#6ee77a;border-color:#2f7a3a}}.meta{{display:block;font-size:.72rem;color:#6d767e;margin:0 0 6px 4px}}.mv{{display:inline-block;font-size:.72rem;color:#c79a5a;margin-left:4px}}
pre{{margin:0;padding:6px 10px;background:var(--term);color:var(--t);font:14px/1.5 "Noto Sans Mono","Noto Sans TC","PingFang TC",monospace;white-space:pre;overflow-x:auto;border-radius:3px}}
.r{{display:none}}body.raw .r{{display:block}}body.raw .s{{display:none}}
.empty{{color:var(--muted);font-size:.85rem}}label{{cursor:pointer}}
.spell .box{{background:var(--term);border-radius:3px;padding:6px 10px;border:1px solid #222}}.ln{{white-space:pre;font:14px/1.5 "Noto Sans Mono","Noto Sans TC",monospace;color:var(--t);min-height:1.5em;overflow-x:auto}}.cmd{{font:13px monospace;color:#c79a5a;margin:2px 4px}}
</style></head><body><div class="wrap">
<h1>武功敘述總表</h1>
<p class="n">新版武功（含新寫的閃躲、內功）與法術 cast 會出現在遊戲裡的敘述；依職業、門派排列，最後是通用；共 {total} 句。顏色是 include/ansi.h 的色碼，斷行照遊戲的 cjk_wrap（寬度 70，色碼的字元也算寬度）與 message_vision 的 nowrap 設定。</p>
<p class="n">每句最前面的「複製」按鈕會把那句敘述的字串（不含色碼、沒有排版用的斷行）放進剪貼簿；勾選「顯示程式原文」時複製的是帶 $N、$n、$w 的原文。法術格子複製的是整個指令的完整畫面。</p>
<p class="n">範例名稱：$N＝無聊的傢伙、$n＝石假人（練武假人）、$l＝右臂、$w＝該類武器；對假人出招時戰鬥系統會拿掉部位，招式敘述也照這樣呈現；程式裡的變數用〔 〕標出。招式與招架、閃避是接在戰鬥敘述裡的片段（命中、傷害的字句由戰鬥系統接在後面）。法術 cast 是實際施展時遊戲送出的完整畫面，前後空行也保留。實際色彩依 zMUD 設定而定，下面色票只是參考。</p>
<div class="top">
<div class="bar"><label><input type="checkbox" id="raw"> 顯示程式原文（$N、$n、$w 不替換）</label>
<button data-act="open-all">全部展開</button><button data-act="close-art">收合所有武功</button><button data-act="close-fac">收合所有門派</button><button data-act="close-all">收合所有職業</button></div>
<div class="pal">{palette}</div>
<nav>{nav}</nav>
</div>
{body}
</div><script>
document.addEventListener('click',e=>{{
  const b=e.target.closest('.cp'); if(!b) return;
  const text=document.body.classList.contains('raw')?b.dataset.r:b.dataset.s;
  const done=()=>{{b.classList.add('ok');const o=b.textContent;b.textContent='已複製';setTimeout(()=>{{b.classList.remove('ok');b.textContent=o;}},1200);}};
  if(navigator.clipboard&&window.isSecureContext) navigator.clipboard.writeText(text).then(done,()=>fallback(text,done));
  else fallback(text,done);
}});
function fallback(text,done){{const t=document.createElement('textarea');t.value=text;t.style.position='fixed';t.style.opacity='0';document.body.appendChild(t);t.select();try{{document.execCommand('copy');done();}}catch(_){{}}document.body.removeChild(t);}}
document.getElementById('raw').addEventListener('change',e=>document.body.classList.toggle('raw',e.target.checked));
document.querySelectorAll('.bar button').forEach(b=>b.addEventListener('click',()=>{{
  const a=b.dataset.act, all=document.querySelectorAll('details');
  if(a==='open-all') all.forEach(d=>d.open=true);
  if(a==='close-art') {{document.querySelectorAll('details.cls,details.fac').forEach(d=>d.open=true);document.querySelectorAll('details.art').forEach(d=>d.open=false);}}
  if(a==='close-fac') {{document.querySelectorAll('details.cls').forEach(d=>d.open=true);document.querySelectorAll('details.fac').forEach(d=>d.open=false);}}
  if(a==='close-all') document.querySelectorAll('details.cls').forEach(d=>d.open=false);
}}));
document.querySelectorAll('nav a').forEach(a=>a.addEventListener('click',()=>{{
  const t=document.querySelector(a.getAttribute('href')); if(t) t.open=true;
}}));
</script></body></html>'''


def main():
    data = build()
    OUT.write_text(page(data), encoding='utf-8')
    total = sum(len(a['entries']) for v in data.values() for a in v)
    print(f'已產生 {OUT.relative_to(ROOT)}：{sum(len(v) for v in data.values())} 套武功、{total} 句敘述')
    for cat, cname in CATEGORIES:
        for a in data.get(cat, []):
            print(f'  {cname:6} {a["name"]:10} {len(a["entries"]):3}')


if __name__ == '__main__':
    main()
