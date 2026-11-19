#!/usr/bin/env python3
"""擷取法術施展（cast）時遊戲實際顯示的敘述，存成 docs/martial_arts/法術敘述擷取.json（使用者指示，2026-11-19）。

開一個本機遊戲伺服器，用臨時的巫師角色 citest 逐道施展法術，把每個指令顯示的全部畫面
（含色碼、前後空行）記下來；build_narration_page.py 會讀這份檔案放進「武功敘述總表」。

只在用完即丟的環境跑：會在 mudlib 底下建立 log、data 與測試角色 citest，並暫時寫入 adm/etc/wizlist
（這些檔案都在 .gitignore 裡）。需要先編好遊戲伺服器：
    cd source/upstream/neolith && cmake --preset linux && cmake --build --preset pr-linux --target neolith
用法：python3 tools/capture_spell_narration.py [--neolith 路徑]
"""
from pathlib import Path
import argparse, json, re, subprocess, sys, time

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import ci_boot_login as c   # 重用開機與登入的輔助函式

OUT = ROOT / 'docs/martial_arts/法術敘述擷取.json'
WIZLIST = c.MUD / 'adm/etc/wizlist'
DEFAULT_NEOLITH = ROOT / 'source/upstream/neolith/out/build/linux/src/RelWithDebInfo/neolith'

# 從客棧大堂走到亂葬崗的石亭（不是禁止戰鬥的房間）
PATH = ['open east', 'east', 'south', 'west', 'west', 'west', 'west', 'northwest', 'west', 'northwest', 'west',
        'southwest', 'south']

# 學派：(技能代碼, 中文名, 指令, 咒文清單, 需要的符, 目標)
# 咒文清單：(咒文代碼, 中文名)
SCHOOLS = [
    ('taoism-fire', '天師道法【火術】', 'cast', [('magic_fire', '咒火'), ('earth_fire', '地火'), ('inferno_fire', '大業火'), ('pure_fire', '三昧真火')], None, 'stake'),
    ('taoism-freeze', '天師道法【冰咒】', 'cast', [('chill_freeze', '寒冰'), ('ominous_freeze', '兆冰'), ('shadow_freeze', '無相冰'), ('polar_freeze', '七重玄冰')], None, 'stake'),
    ('taoism-storm', '天師道法【風符】', 'cast', [('quick_storm', '疾風'), ('crazy_storm', '暴風'), ('killer_storm', '飛戮風'), ('whirl_storm', '轉輪大風')], None, 'stake'),
    ('taoism-thunder', '天師道法【雷法】', 'cast', [('swamp_thunder', '澤雷'), ('blaster_thunder', '爆雷'), ('divine_thunder', '神光雷'), ('hexagram_thunder', '六卦熒雷')], None, 'stake'),
    ('taoism of darkness', '茅山奇術', 'cast', [('ghost_fire', '鬼火術'), ('smoke', '鬼煙術'), ('hell_fire', '幽冥之火')], '/custom/item/scroll/yin', 'stake'),
    ('taoism of nature', '茅山幻術', 'cast', [('monkey', '猴'), ('hydra', '巨蟒'), ('rain', '祈雨'), ('dog', '狗')], '/custom/item/scroll/nature', 'stake'),
]


def clean(raw):
    t = c.TELNET.sub(b'', raw).decode('utf-8', 'replace').replace('\r', '')
    t = re.sub(r'(?m)^(?:\x1b\[[0-9;]*m)*> ?', '', t)       # 提示符號
    return t


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--neolith', default=str(DEFAULT_NEOLITH))
    a = ap.parse_args()
    WIZLIST.write_text('citest (admin)\n', encoding='utf-8')
    c.prepare_dirs()
    proc = subprocess.Popen([a.neolith, '-f', 'neolith.conf'], cwd=c.UPSTREAM, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    results = []
    try:
        c.wait_for_port(proc)
        s = c.Session()

        def drain(t=0.5):
            end = time.time() + t
            while time.time() < end:
                try:
                    d = s.sock.recv(65536)
                    if d: s.raw += d
                except Exception:
                    pass

        def run(cmd, wait=1.0):
            drain(0.3)
            mark = len(s.raw)
            s.send(cmd)
            time.sleep(wait)
            drain(0.5)
            return clean(s.raw[mark:])

        # 登入（沒有角色就先建立）
        s.expect('您的使用者代號', step='連線')
        s.send(c.USER_ID)
        first = s.sock.recv(4096) if False else b''
        time.sleep(1); drain(0.5)
        if '請輸入密碼' not in s.text():
            raise SystemExit('找不到測試角色 citest；請先跑一次 tools/ci_boot_login.py 建立。')
        s.send(c.PASSWORD)
        s.expect('目前權限', '> ', step='登入')
        for cmd in PATH:
            run(cmd, 1.2)
        # 準備：精氣神、目標
        for st in ('gin', 'kee', 'sen'):
            for f in ('set_stat_maximum', 'set_stat_effective', 'set_stat_current'):
                run('call me->%s("%s",9000)' % (f, st), 0.4)
        run('clone /d/qiaoyin_east/npc/stone_stake', 1.5)
        run('clone /custom/legacy_npc/barbarian_chief', 1.5)

        for skill, cname, cmd, spells, scroll, target in SCHOOLS:
            run('call me->set_skill("%s",200)' % skill, 0.4)
            run('enable spells with %s' % skill, 0.6)
            if scroll:
                run('clone 60 %s' % scroll, 1.0)
            for sid, scname in spells:
                tgt = target
                if sid == 'hydra':
                    tgt = 'chief'
                    run('kill chief', 1.5)
                else:
                    run('call me->start_busy(0)', 0.3)
                    run('call me->remove_all_enemy()', 0.3)
                    run('call stake->remove_all_enemy()', 0.3)
                # 只取施法當下的畫面（約 1.4 秒）：之後自動開打的戰鬥訊息不是法術的敘述
                text = run('%s %s on %s' % (cmd, sid, tgt), 1.4)
                time.sleep(2.0)
                results.append(dict(school=skill, school_cname=cname, spell=sid, spell_cname=scname,
                                    command='%s %s on %s' % (cmd, sid, tgt), text=text))
                print(f'{cname} {sid}: {len(text)} 字元')
                if sid == 'hydra':
                    run('call chief->heal_up()', 0.3)
        s.send('quit')
    finally:
        proc.terminate()
        try: proc.communicate(timeout=10)
        except Exception: proc.kill()
        if WIZLIST.exists(): WIZLIST.unlink()
    OUT.write_text(json.dumps(results, ensure_ascii=False, indent=1), encoding='utf-8')
    print(f'已寫入 {OUT.relative_to(ROOT)}：{len(results)} 道法術')


if __name__ == '__main__':
    main()
