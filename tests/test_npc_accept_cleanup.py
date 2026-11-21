from pathlib import Path

MUD = Path(__file__).resolve().parents[1] / 'source' / 'upstream' / 'mudlib'

# 收下東西後要刪掉、不留在身上的 NPC（使用者定案，2026-11-22）。
CLEANUP_NPCS = [
    'd/qiaoyin/npc/crone.c',
    'd/wutang/npc/yaesae.c',
    'd/wutang/npc/yung_tai.c',
    'd/snow/npc/gammer.c',
    'd/snow/npc/girl.c',
    'd/snow/npc/smith.c',
    'd/snow/npc/yu.c',
]


def _accept_body(s):
    body = s[s.index('int accept_object('):]
    return body[:body.index('\n}\n')]


def test_give_checks_npc_room_before_accept():
    s = (MUD / 'cmds/std/give.c').read_text(encoding='utf-8')
    body = s[s.index('if( !userp(who) ) {'):]
    # 先檢查放不放得下，再問 NPC 收不收。
    assert body.index('sizeof(all_inventory(who)) >= 20') < body.index('who->accept_object(me, item)')
    assert '身上已經放不下了' in body
    # 只有錢會被 give 銷毀（不改成連一般物品也銷毀）。
    assert 'if( item->value() ) {' in body


def test_npcs_drop_received_items():
    for f in CLEANUP_NPCS:
        s = (MUD / f).read_text(encoding='utf-8')
        assert 'call_out("drop_item", 1, ob);' in _accept_body(s), f
        assert 'void drop_item(object ob)' in s, f
        assert 'environment(ob) == this_object() ) destruct(ob);' in s, f


def test_jeweller_draws_only_after_pearl_received():
    s = (MUD / 'd/wutang/npc/jeweller.c').read_text(encoding='utf-8')
    assert 'call_out("do_draw", 1, who, ob);' in _accept_body(s)
    draw = s[s.index('void do_draw(object who, object pearl)\n{'):]
    draw = draw[:draw.index('\n}\n')]
    # 珠子不在商人身上就不抽；先銷毀珠子，玩家離開也不退回（選甲）。
    i_check = draw.index('environment(pearl) != this_object() ) return;')
    i_dest = draw.index('destruct(pearl);')
    i_who = draw.index('if( !who || environment(who) != environment() ) return;')
    assert i_check < i_dest < i_who


def test_jeweller_prize_message_uses_vision():
    s = (MUD / 'd/wutang/npc/jeweller.c').read_text(encoding='utf-8')
    assert 'replace_string(PRIZE_EMOTE[kind], "$N", who->name())' not in s
    assert 'message_vision(CYN + PRIZE_EMOTE[kind] + "\\n" NOR, who, this_object());' in s
    emotes = s[s.index('private string *PRIZE_EMOTE'):s.index('});', s.index('private string *PRIZE_EMOTE'))]
    for line in emotes.splitlines()[1:]:
        if line.strip().startswith('"'):
            assert line.strip().startswith('"$n') and '$N' in line
