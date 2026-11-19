from pathlib import Path

MUD = Path(__file__).resolve().parents[1] / 'source' / 'upstream' / 'mudlib'


def test_devoured_player_reincarnates_in_own_context():
    s = (MUD / 'daemon/race/yaksa/devour.c').read_text(encoding='utf-8')
    body = s[s.index('if (userp(victim)) {'):]
    body = body[:body.index('return;')]
    body = '\n'.join(l.split('//')[0] for l in body.splitlines())   # 只看程式碼，不看註解
    # 選種族畫面會綁在目前下指令的人身上，不能在夜叉的動作裡直接 make_mist()。
    assert 'make_mist' not in body and 'victim->die()' not in body
    assert 'victim->consume_stat("HP", victim->query_stat("HP") + 1, me);' in body
    h = (MUD / 'std/race/humanoid.c').read_text(encoding='utf-8')
    assert 'CHAR_D->make_mist(ob);' in h


def test_devour_is_sealed():
    # 封印開關：2026-11-04 重新開放（0）；封印檢查本身保留，要再封印改成 1。
    s = (MUD / 'daemon/race/yaksa/devour.c').read_text(encoding='utf-8')
    assert '#define DEVOUR_SEALED 0' in s
    main = s[s.index('int main(object me, string arg)'):]
    # 封印檢查要在開始吞食（設定 yaksa_devour）之前。
    assert main.index('if (DEVOUR_SEALED)') < main.index('me->set_temp("yaksa_devour"')
    seal = main[main.index('if (DEVOUR_SEALED)'):]
    seal = seal[:seal.index(';')]
    assert 'devour' not in seal.split('notify_fail', 1)[1]   # 給玩家看的話不提指令


def test_help_block_fits_driver_limit():
    # 驅動程式的 @ 文字區塊上限是 1024 位元組（neolith lib/lpc/lex.h MAXLINE），超過會編譯失敗。
    s = (MUD / 'daemon/race/yaksa/devour.c').read_text(encoding='utf-8')
    block = s[s.index('@HELP\n') + len('@HELP\n'):s.index('\nHELP);')]
    assert len(block.encode('utf-8')) < 1000


def test_threshold_rules():
    s = (MUD / 'daemon/race/yaksa/devour.c').read_text(encoding='utf-8')
    assert 'int extra = count >= 10 ? count - 9 : 0;' in s
    assert 'return yaksa_ghost ? 250 + 25 * extra : 500 + 50 * extra;' in s
    assert '#define COUNT_KEY "yaksa/devour_count"' in s
    body = s[s.index('private void reward_player'):s.index('private void finish')]
    # 未達門檻：不計數、不加成；達到門檻才 add 次數，且比完門檻才加倍。
    # 夜叉自己的精（最大值）也要達到同一個門檻。
    assert 'own_gin = me->query_stat_maximum("gin");' in body
    assert 'if (ghost_gin < need || own_gin < need) {' in body
    miss = body[body.index('if (ghost_gin < need || own_gin < need)'):body.index('} else {')]
    assert 'COUNT_KEY' not in miss and 'grow(' not in miss
    assert body.index('if (ghost_gin < need || own_gin < need)') < body.index('ghost_gin *= 2')
    assert 'write_record(me, rec);' in body
    # 未達門檻一樣魂飛魄散。
    fin = s[s.index('private void finish'):]
    fin = fin[fin.index('if (userp(victim)) {'):]
    fin = fin[:fin.index('return;')]
    assert 'reward_player(' in fin and 'consume_stat("HP"' in fin


def test_devour_log_path_is_writable_by_mudlib():
    s = (MUD / 'daemon/race/yaksa/devour.c').read_text(encoding='utf-8')
    assert '#define DEVOUR_LOG "/data/daemon/yaksa_devour.log"' in s
    sec = (MUD / 'adm/daemons/securityd.c').read_text(encoding='utf-8')
    assert '"/data/daemon":\t({ MUDLIB_UID }),' in sec


def test_first_bite_delayed_two_ticks():
    s = (MUD / 'daemon/race/yaksa/devour.c').read_text(encoding='utf-8')
    main = s[s.index('int main(object me, string arg)'):]
    assert 'call_out("devour_tick", TICK_SECONDS * 2, me, victim, serial);' in main
    assert 'devour_tick(me, victim, serial);' not in main


def test_small_temple_is_no_fight():
    s = (MUD / 'd/snow/small_temple.c').read_text(encoding='utf-8')
    assert 'set ("no_fight", 1);' in s


def test_ghost_gin_uses_victim_maximum():
    # 鬼魂的精以被吞角色的精最大值計算（使用者指示，2026-11-15）。
    s = (MUD / 'daemon/race/yaksa/devour.c').read_text(encoding='utf-8')
    main = s[s.index('int main(object me, string arg)'):]
    assert '"ghost_gin": victim->query_stat_maximum("gin")' in main


def test_one_yaksa_at_a_time():
    # 同時間只能一隻夜叉吞同一個鬼魂；吞完到消散前誰都不能再吞（使用者指示，2026-11-15）。
    s = (MUD / 'daemon/race/yaksa/devour.c').read_text(encoding='utf-8')
    main = s[s.index('int main(object me, string arg)'):]
    assert main.index('if (holder_of(victim))') < main.index('me->set_temp("yaksa_devour"')
    assert main.index('if (victim->query_temp(DONE_KEY))') < main.index('me->set_temp("yaksa_devour"')
    assert 'victim->set_temp(HOLDER_KEY, me);' in main
    tick = s[s.index('void devour_tick'):s.index('int main(object me, string arg)')]
    assert 'victim->query_temp(DONE_KEY) || victim->query_temp(HOLDER_KEY) != me' in tick
    fin = s[s.index('private void finish'):s.index('void devour_tick')]
    assert fin.index('victim->set_temp(DONE_KEY, 1);') < fin.index('reward_player(')


def test_devour_record_fields():
    # 吞魂紀錄（使用者指示，2026-11-15）：只記玩家，每筆可用 devourlog 查詢。
    s = (MUD / 'daemon/race/yaksa/devour.c').read_text(encoding='utf-8')
    body = s[s.index('private void reward_player'):s.index('private void finish')]
    for key in ('"time"', '"soul_no"', '"valid_no"', '"victim"', '"same_victim"', '"gin"', '"kee"',
                '"sen"', '"big"', '"killer"', '"yaksa_ip"', '"victim_ip"', '"victim_age"',
                '"yaksa_class"', '"victim_class"', '"ghost_gin"', '"own_gin"', '"need"',
                '"max_gin"', '"max_kee"', '"max_sen"', '"room"'):
        assert key + ':' in body, key
    assert 'me->add(SOUL_KEY, 1);' in body
    assert '#define DEVOUR_DATA "/data/daemon/yaksa_devour.dat"' in s
    assert 'save_variable(rec)' in s
    # 鬼魂 NPC 不記錄：紀錄只在玩家的 reward_player 裡寫。
    fin = s[s.index('private void finish'):s.index('void devour_tick')]
    npc = fin[fin.index('stop_devour(me);\n\n'):]
    assert 'write_record' not in npc and 'reward_player' not in npc
    # 死因在死亡那一刻記下。
    c = (MUD / 'adm/daemons/chard.c').read_text(encoding='utf-8')
    corpse = c[c.index('varargs object make_corpse'):c.index('int make_mist')]
    assert 'victim->set ("last_death", ([' in corpse


def test_devourlog_command():
    s = (MUD / 'cmds/arch/devourlog.c').read_text(encoding='utf-8')
    assert not (MUD / 'cmds/wiz/devourlog.c').exists()
    # 只給 arch 以上使用、預設列出最近 100 筆（使用者指示，2026-11-15）。
    main = s[s.index('int main(object me, string arg)'):]
    assert main.index('SECURED_ARCH_COMMAND;') < main.index('load_all()')
    assert '#define LIST_MAX    100' in s
    assert '#define DEVOUR_DATA "/data/daemon/yaksa_devour.dat"' in s
    assert 'restore_variable(' in s
    for opt in ('"-d %d"', '"-v %s"', '"-p %s"'):
        assert opt in s
    block = s[s.index('@HELP\n') + len('@HELP\n'):s.index('\nHELP);')]
    assert len(block.encode('utf-8')) < 1000


def test_devour_without_target_shows_big_count():
    # 不加目標時顯示大幅增加的次數（使用者指示，2026-11-19），只在大幅時累加。
    s = (MUD / 'daemon/race/yaksa/devour.c').read_text(encoding='utf-8')
    main = s[s.index('int main(object me, string arg)'):]
    assert main.index('if (!arg || arg == "") return show_count(me);') < main.index('if (DEVOUR_SEALED)')
    body = s[s.index('private void reward_player'):s.index('private void finish')]
    big = body[body.index('if (big) {'):body.index('} else {', body.index('if (big) {'))]
    assert 'me->add(BIG_KEY, 1);' in big
    show = s[s.index('private int show_count'):s.index('int main(object me, string arg)')]
    assert 'devour' not in show.split('{', 1)[1]   # 給玩家看的話不提指令


if __name__ == '__main__':
    test_devoured_player_reincarnates_in_own_context()
    test_devour_is_sealed()
    test_help_block_fits_driver_limit()
    test_threshold_rules()
    test_devour_log_path_is_writable_by_mudlib()
    test_first_bite_delayed_two_ticks()
    test_small_temple_is_no_fight()
    test_ghost_gin_uses_victim_maximum()
    test_one_yaksa_at_a_time()
    test_devour_record_fields()
    test_devourlog_command()
    test_devour_without_target_shows_big_count()
    print('ok')
