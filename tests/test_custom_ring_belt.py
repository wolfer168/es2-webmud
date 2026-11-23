from pathlib import Path
from placement import LibDir, current
import re

MUD = Path(__file__).resolve().parents[1] / 'source' / 'upstream' / 'mudlib'
RING = LibDir(MUD / 'custom' / 'armor' / 'finger')
BELT = LibDir(MUD / 'custom' / 'armor' / 'waist')


def read(p):
    return current(p).read_text(encoding='utf-8')   # 搬走的檔案照 adm/etc/moved_paths 找（docs/NPC_ITEM_PLACEMENT.md）


def test_rings_and_belts():
    rings, belts = sorted(RING.glob('*.c')), sorted(BELT.glob('*.c'))
    assert len(rings) >= 39 and len(belts) >= 20  # 之後的批次會再增加
    for files, slot, feat in [(rings, 'finger_eq', 'F_FINGER_EQ'), (belts, 'waist_eq', 'F_WAIST_EQ')]:
        for f in files:
            s = read(f)
            assert f'inherit {feat};' in s, f.name
            assert f'set("wear_as", "{slot}");' in s, f.name
            assert f'set("apply_armor/{slot}", ([' in s, f.name
    for f in rings:
        s = read(f)
        assert re.search(r'set_name\("[^"]*", \(\{ "[^"]+", "ring" \}\)\);', s), f.name


def test_unique_items():
    for p in [RING / 'tiger_ring.c', BELT / 'white_girth.c', BELT / 'voliet_jade.c']:
        assert 'inherit F_UNIQUE;' in read(p), p.name


def test_wear_restrictions():
    for p, cond in [(RING / 'ring_of_mighty_lord.c', 'query_class() != "soldier"'),
                    (BELT / 'girdle_of_mighty_lord.c', 'query_class() != "soldier"'),
                    (RING / 'ring_of_mighty_dragon.c', 'query_class() != "fighter"'),
                    (RING / 'magicians_ring.c', 'query_class() != "taoist"'),
                    (BELT / 'girdle_of_headless.c', 'query_race() != "headless"')]:
        s = read(p)
        assert cond in s and 'return ::wear(on_part);' in s, p.name


def test_renamed_rings():
    assert 'set_name("\\x1b[1;34m青金指環\\x1b[m", ({ "lapis ring", "ring" }));' in read(RING / 'lapis_ring.c')
    assert 'set_name("太乙七絕　戒"' in read(RING / 'yimo_ring.c')


def test_freeze_ring_clutch():
    assert 'add_action("do_clutch", "clutch");' in read(RING / 'freeze_ring.c')
    s = read(MUD / 'daemon' / 'condition' / 'rain_blessing.c')
    for x in ['#define COOLDOWN_TICKS   60', 'wis = me->query_attr("wis");',
              'amount = wis + random(me->query_skill("spells") / 20);',
              '"until":    time() + wis * TICK_SECONDS,',
              '你受到雨神祝福，感覺體內靈力暴增。', '雨神的祝福依然庇蔭著你。',
              '你心神一怔，似乎有些神力消散了。', '你持續喃喃祝禱，但似乎沒有任何感應。']:
        assert x in s, x


def test_crystal_ring_follows_source_data():
    s = read(MUD / 'd' / 'lee' / 'obj' / 'crystal_ring.c')
    assert '"armor": 1,' in s and '"spi": 1,' in s and '"con": 1,' in s
