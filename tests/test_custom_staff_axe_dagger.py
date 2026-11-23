from pathlib import Path
from placement import LibDir

MUD = Path(__file__).resolve().parents[1] / 'source' / 'upstream' / 'mudlib'
W = LibDir(MUD / 'custom' / 'weapon')


def read(p):
    return p.read_text(encoding='utf-8')


def test_counts_and_features():
    for d, feat, n in [('staff', 'F_STAFF', 21), ('axe', 'F_AXE', 15), ('dagger', 'F_DAGGER', 22)]:
        files = sorted((W / d).glob('*.c'))
        assert len(files) >= n, d  # 之後的批次會再增加
        for f in files:
            s = read(f)
            assert f'inherit {feat};' in s and 'init_damage(' in s and 'set("wield_as"' in s, f.name


def test_unique_and_existing():
    for p in ['staff/serpent_cane', 'axe/axe_of_bloodmoon', 'dagger/bloody_dagger', 'dagger/wicked_dagger']:
        assert 'inherit F_UNIQUE;' in read(W / f'{p}.c'), p
    s = read(MUD / 'custom' / 'zhenwu' / 'obj' / 'great_axe_of_mighty.c')
    assert 'inherit F_UNIQUE;' in s and 'set("value", 200000);' in s
    assert (MUD / 'd' / 'snow' / 'npc' / 'obj' / 'syndicator.c').exists()


def test_serpent_cane_special():
    s = read(W / 'staff' / 'serpent_cane.c')
    assert 'void miss_ob(object me, object victim)' in s
    assert 'if( random(100) >= 10 ) return;' in s
    assert '(10 + (me->query_attr("cor") + me->query_attr("str")) / 3)' in s
    assert '* (10 + me->query("pk_record")) / 10;' in s
    assert 'victim->consume_stat("kee", damage, me);' in s
    assert 'weapon->miss_ob(me, victim);' in read(MUD / 'adm' / 'daemons' / 'combatd.c')


def test_single_side_traits():
    assert 'apply_weapon/secondhand dagger' in read(W / 'dagger' / 'chi_dagger.c')
    assert 'apply_weapon/dagger"' not in read(W / 'dagger' / 'chi_dagger.c')
    s = read(W / 'staff' / 'staff_of_wisdom.c')
    assert 'apply_weapon/staff"' in s and 'apply_weapon/twohanded staff' not in s and '"magic_ability": 20,' in s
    s = read(W / 'staff' / 'flame_staff.c')
    assert 'init_damage(3, 9, 60, 3, "twohanded staff");' in s and '"spell": 50,' in s


def test_weights_and_snow_dagger():
    assert 'set_weight(32000);' in read(W / 'axe' / 'grandaxe.c')
    assert 'set_weight(36000);' in read(W / 'staff' / 'rainlords_tooth_invoke.c')
    s = read(W / 'dagger' / 'snow_dagger.c')
    assert 'F_UNIQUE' not in s and '"con": 2,' in s and '"cor": 1,' in s and '"armor_vs_ice": 30,' in s and '"attack": 5,' in s


def test_mee_pei_steel_axe_fallback():
    # 精鋼戰斧：萬夫莫敵的替代武器（使用者指定，2026-11-23）
    s = read(MUD / 'custom' / 'zhenwu' / 'npc' / 'obj' / 'steel_axe.c')
    assert 'set_name("精鋼戰斧", ({ "steel axe", "axe" }));' in s
    assert 'set_weight(12000);' in s and 'set("value", 12000);' in s
    assert 'init_damage(4, 24, 146, 4, "twohanded axe");' in s   # 傷害 8～100，加成上限 140
    assert 'F_UNIQUE' not in s
    for k, v in (('cor', 1), ('str', 1), ('berserk', 10)):
        assert '"%s": %d,' % (k, v) in s
    m = read(MUD / 'custom' / 'zhenwu' / 'npc' / 'mee_pei.c')
    assert m.index('great_axe_of_mighty') < m.index('environment(axe) != this_object()') < m.index('npc/obj/steel_axe')
