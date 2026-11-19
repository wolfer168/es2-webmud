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


# 其他法術（conjure）與針灸（acupuncture）：(技能代碼, enable 的基本技能, 中文名, 先做的準備指令, [(指令, 中文名)], 技能要先設的其他技能)
OTHERS = [
    ('mao-shan magic', 'magic', '茅山法術', ['clone 40 /custom/item/scroll/blank'],
     [('conjure blank', '空白符'), ('conjure yin', '少陰符'), ('conjure yang', '太陽符'), ('conjure nature', '先天符'),
      ('conjure remedy', '療傷'), ('conjure vision', '陰陽眼')], []),
    ('mao-shan mysticism', 'magic', '茅山道法【奇門術】', ['clone 40 /custom/item/scroll/yin'],
     [('conjure memory', '記憶'), ('north', ''), ('conjure recall', '招魂'), ('clone /d/graveyard/npc/barbarian', ''),
      ('call barbarian->die()', ''), ('conjure collect on corpse', '收魂'), ('clone /d/graveyard/npc/barbarian', ''),
      ('call barbarian->die()', ''), ('conjure slave on corpse', '役使'), ('conjure devour', '吞噬')], ['taoism of darkness']),
    ('taoism of dunja', 'magic', '茅山奇術【遁甲書】', ['clone /custom/legacy_npc/barbarian_chief'],
     [('conjure fate', '天命'), ('conjure experience on chief', '經驗'), ('call chief->die()', '')], []),
    ('chivi sutra', 'magic', '天師道法【紫薇心經】', [],
     [('conjure fire_defence', '火防'), ('conjure storm_defence', '風防'), ('conjure freeze_defence', '冰防'),
      ('conjure thunder_defence', '雷防'), ('conjure dispel', '解除')], []),
    ('enchance', 'magic', '強化之術', ['clone /custom/weapon/sword/black_shortsword', 'wield sword', 'clone 20 /obj/money/gold'],
     [('conjure silver_mark on sword', '銀咒'), ('conjure gold_mark on sword', '金咒')], []),
    ('alchemy-wealth', 'magic', '丹道【黃白之術】', ['unwield sword', 'clone /custom/weapon/staff/god_cane', 'clone /custom/weapon/sword/black_shortsword'],
     [('conjure silver_seal on god', '銀咒'), ('conjure gold_seal on sword', '金咒')], []),
    ('alchemy-medication', 'magic', '丹道【神農之術】', ['clone /obj/alchemist/heat_reactor'],
     [('conjure red_seal on reactor', '赤印封'), ('conjure red_dispel on reactor', '赤印解')], []),
    ('amazing-needle', 'cauterization', '武陀灸術【驚異二針】', ['unwield sword', 'clone /custom/weapon/needle/iron_needle', 'wield needle'],
     [('acupuncture amazing_armor to stake', '驚異霸甲針'), ('acupuncture amazing_power to stake', '驚異霸氣針'),
      ('acupuncture self_test', '自測')], []),
    ('wuto-needle', 'cauterization', '武陀灸術【五敗針法】', [],
     [('acupuncture fear to stake', '敗膽一針'), ('acupuncture foul to stake', '敗骨二針'), ('acupuncture fail to stake', '敗膂三針'),
      ('acupuncture fling to stake', '敗韌四針'), ('acupuncture fumble to stake', '敗敏五針')], []),
    ('potency-needle', 'cauterization', '武陀灸術【引源針法】', [],
     [('acupuncture fatigue to stake', '消疲'), ('acupuncture awareness to stake', '警覺'),
      ('acupuncture move to stake', '移動'), ('acupuncture element to stake', '元素')], []),
    ('recovery-needle', 'cauterization', '武陀灸術【三自回針法】', [],
     [('acupuncture gin-up', '回精針'), ('acupuncture kee-up', '回氣針'), ('acupuncture sen-up', '回神針')], []),
]


def clean(raw):
    t = c.TELNET.sub(b'', raw).decode('utf-8', 'replace').replace('\r', '')
    t = re.sub(r'(?m)^(?:\x1b\[[0-9;]*m)*> ?', '', t)       # 提示符號
    # 路過的 NPC 與先前法術的延遲訊息不是這個指令的畫面
    t = re.sub(r'(?m)^(?:劉乙忘玄|老和尚|小和尚)(?:走了過來|往.{1,2}離開)。\n', '', t)
    t = re.sub(r'(?m)^你眼前那層幽光漸漸淡去。\n', '', t)
    return t


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--neolith', default=str(DEFAULT_NEOLITH))
    ap.add_argument('--only', default='', help='只擷取技能代碼或中文名含這段文字的學派，結果合併進既有的 json')
    a = ap.parse_args()
    keys = [k for k in a.only.split(',') if k]

    def want(skill, cname):
        return not keys or any(k in skill or k in cname for k in keys)

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
            if not want(skill, cname):
                continue
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
                    if sid == 'smoke':
                        run('kill stake', 1.0)      # 鬼煙術要在戰鬥中才能遁走
                # 只取施法當下的畫面（約 1.4 秒）：之後自動開打的戰鬥訊息不是法術的敘述
                text = run('%s %s on %s' % (cmd, sid, tgt), 1.4)
                time.sleep(2.0)
                results.append(dict(school=skill, school_cname=cname, spell=sid, spell_cname=scname,
                                    command='%s %s on %s' % (cmd, sid, tgt), text=text))
                print(f'{cname} {sid}: {len(text)} 字元')
                if sid == 'hydra':
                    run('call chief->heal_up()', 0.3)
        for skill, usage, cname, pre, cmds, deps in OTHERS:
            if not want(skill, cname):
                continue
            run('call me->set_skill("%s",200)' % skill, 0.4)
            for d in deps:
                run('call me->set_skill("%s",200)' % d, 0.4)
            run('enable %s with %s' % (usage, skill), 0.6)
            for pc in pre:
                out = run(pc, 1.2)
                print('  準備', pc, '->', out.strip().replace(chr(10), ' / ')[:80])
            for cmd, scname in cmds:
                if not scname:
                    run(cmd, 1.2)
                    continue
                run('call me->start_busy(0)', 0.3)
                run('call me->remove_all_enemy()', 0.3)
                run('call stake->remove_all_enemy()', 0.3)
                text = run(cmd, 1.4)
                time.sleep(1.5)
                results.append(dict(school=skill, school_cname=cname, spell=cmd.split()[1] if len(cmd.split()) > 1 else cmd,
                                    spell_cname=scname, command=cmd, text=text))
                print(f'{cname} {cmd}: {len(text)} 字元')
        s.send('quit')
    finally:
        proc.terminate()
        try: proc.communicate(timeout=10)
        except Exception: proc.kill()
        if WIZLIST.exists(): WIZLIST.unlink()
    if a.only and OUT.exists():
        old = json.loads(OUT.read_text(encoding='utf-8'))
        new = {r['school'] for r in results}
        results = [r for r in old if r['school'] not in new] + results
        # 依原本的學派順序排列
        order = [x[0] for x in SCHOOLS] + [x[0] for x in OTHERS]
        results.sort(key=lambda r: order.index(r['school']) if r['school'] in order else 99)
    OUT.write_text(json.dumps(results, ensure_ascii=False, indent=1), encoding='utf-8')
    print(f'已寫入 {OUT.relative_to(ROOT)}：{len(results)} 道法術')


if __name__ == '__main__':
    main()
