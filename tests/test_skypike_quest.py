"""穹槍訣任務（老王尋妻，2026-11-21）：檔案、記號與流程的結構檢查。"""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
MUD = ROOT / 'source' / 'upstream' / 'mudlib'


def read(p):
    return re.sub(r'\x1b\[[0-9;]*m', '', p.read_text(encoding='utf-8'))


def test_files_exist():
    for f in ('d/baihua/skypike_quest.h', 'd/baihua/obj/sister_letter.c', 'd/baihua/obj/ling_tzi.c',
              'd/wutang/npc/old_woman.c', 'd/oldpine/obj/meat.c', 'd/oldpine/obj/dragon_pill.c',
              'obj/dust.c', 'docs/help/sky_pike.txt', 'daemon/skill/sky_pike.c'):
        assert (MUD / f).exists(), f
    assert 'old_woman' in read(MUD / 'd/wutang/city_god_temple.c')
    assert '/d/oldpine/obj/meat' in read(MUD / 'd/oldpine/npc/wild_bear.c')


def test_npcs_use_quest_header_after_inherit():
    # 標頭宣告了變數，必須放在 inherit 之後（否則編譯失敗）
    for f in ('d/baihua/npc/old_wang.c', 'd/baihua/npc/kao_yeu.c', 'd/snow/npc/alchemist.c',
              'd/wutang/npc/old_woman.c'):
        s = read(MUD / f)
        assert s.index('inherit F_') < s.index('skypike_quest.h'), f
        assert 'accept_object' in s or 'relay_say' in s, f


def test_help_has_story_and_entry():
    s = read(MUD / 'docs/help/sky_pike.txt')
    assert s.startswith('\n【任務背景】')
    assert '◎ 穹槍訣（sky_pike）' in s
    assert '百花村' in s and '五堂鎮' in s
    assert not re.search(r'\bexert\b|\bperform\b', s)


def test_endgame_rewards():
    s = read(MUD / 'd/baihua/npc/kao_yeu.c')
    assert 'improve_skill_exact("sky_pike", 1)' in s
    assert 'SQ_PILL_FILE' in s and 'destruct(this_object())' in s
    assert SQ_PILL_OK(read(MUD / 'd/baihua/skypike_quest.h'))


def SQ_PILL_OK(h):
    return '/d/oldpine/obj/dragon_pill' in h and '/obj/dust' in h
