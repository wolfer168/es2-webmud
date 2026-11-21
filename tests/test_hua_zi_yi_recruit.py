from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MUD = ROOT / 'source' / 'upstream' / 'mudlib'


def read(p):
    return p.read_text(encoding='utf-8')


def test_hua_zi_yi_recruits_commoner_with_wisdom():
    s = read(MUD / 'd/fengcheng/npc/hua_zi_yi.c')
    assert '#define FACTION "taoist.thunder"' in s and 'set("custom_faction", FACTION);' in s
    assert 'me->query_class() != "commoner"' in s                      # 只收平民，已有師承的不收
    assert 'me->query_attr("wis", 1) < 16' in s                         # 慧根至少 16
    assert 'me->set("title", "紫衣派弟子");' in s and 'me->set_class("taoist");' in s


def test_hua_zi_yi_teaches_only_disciples():
    s = read(MUD / 'd/fengcheng/npc/hua_zi_yi.c')
    assert 'if( me->query("custom_faction") != FACTION ) return 0;' in s
    for sk in ('taoism-thunder', 'reflecting star sword', 'magic steps', 'nine-dragon force'):
        assert 'case "%s":' % sk in s
    assert 'me->query_level() < 10' in s                                # 九龍神功與內功要等級 10
    npc_skill = read(MUD / 'daemon/misc/npc_skill.c')
    assert '"taoist.thunder"' in npc_skill and '"force":       "nine-dragon force"' in npc_skill


def test_nine_dragon_force_is_taught_without_file_size_check():
    # 曾經用 file_size("/daemon/skill/...") 檢查技能檔存在，但 NPC 的 euid（Domain）沒有讀取 /daemon 的權限，
    # file_size 一律傳回 -1，導致九龍神功永遠教不了（2026-11-19 修正）。技能檔已存在，不需要再檢查。
    s = read(MUD / 'd/fengcheng/npc/hua_zi_yi.c')
    assert 'file_size' not in s
    assert 'case "nine-dragon force":' in s and 'me->query_level() < 10' in s
    assert (MUD / 'daemon/skill/nine-dragon_force.c').exists()


def test_faction_help_exists():
    h = read(MUD / 'docs/help/taoist.thunder.txt')
    assert h.startswith('○ 紫衣派資料') and '青雲觀主 華子儀(Hua zi yi)' in h
    for sk in ('taoism-thunder', 'reflecting star sword', 'magic steps'):
        assert '（%s）' % sk in h


def test_help_topics_list_new_help_files():
    # 玄天派、紫衣派、強化之術的說明檔都放進 help 的主題列表（docs/help/topics.txt）。
    topics = read(MUD / 'docs/help/topics.txt')
    for tid, name in (('scholar.sky', '玄天派'), ('taoist.thunder', '紫衣派'), ('taoist.freeze', '素衣派'),
                      ('enchance', '強化之術')):
        assert tid in topics and name in topics, tid
        assert (MUD / 'docs/help' / (tid + '.txt')).exists(), tid
