from pathlib import Path
from placement import LibDir

MUD = Path(__file__).resolve().parents[1] / 'source' / 'upstream' / 'mudlib'
ARMOR = LibDir(MUD / 'custom' / 'armor')


def read(p):
    return p.read_text(encoding='utf-8')


def test_counts_and_slots():
    for d, slot, feat, n in [('neck', 'neck_eq', 'F_NECK_EQ', 13), ('feet', 'feet_eq', 'F_FEET_EQ', 25),
                             ('head', 'head_eq', 'F_HEAD_EQ', 27)]:
        files = sorted((ARMOR / d).glob('*.c'))
        assert len(files) >= n, d  # 之後的批次會再增加
        for f in files:
            s = read(f)
            assert f'inherit {feat};' in s and f'set("wear_as", "{slot}");' in s, f.name
            assert f'set("apply_armor/{slot}", ([' in s, f.name


def test_unique_and_restricted():
    for p in ['neck/tiger_necklace', 'feet/dragon_boots', 'feet/wonder_boots', 'head/lion_helmet']:
        assert 'inherit F_UNIQUE;' in read(ARMOR / f'{p}.c'), p
    for p, c in [('neck/dark_necklace', 'thief'), ('feet/dark_boots', 'thief'), ('head/royal_helmet', 'soldier')]:
        assert f'owner->query_class() != "{c}"' in read(ARMOR / f'{p}.c'), p


def test_names_and_reused_items():
    assert 'set_name("蛈蜇杳龍屐"' in read(ARMOR / 'feet' / 'dragon_boots.c')
    assert 'set_name("啖紅裐雲靴"' in read(ARMOR / 'feet' / 'red_boots.c')
    for p in ['d/npc/obj/clothboot.c', 'd/snow/obj/hairpin.c', 'd/npc/obj/steel_boots.c']:
        assert (MUD / p).exists(), p


def test_neck_values_capped():
    import re
    for f in (ARMOR / 'neck').glob('*.c'):
        v = int(re.search(r'set\("value", (\d+)\)', read(f)).group(1))
        assert v <= 30000, f.name
