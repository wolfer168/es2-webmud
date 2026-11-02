# 練武假人：三具假人都繼承同一份底本（使用者指示，2026-11-02；設計文件 docs/TRAINING_DUMMY.md）。
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
MUD = ROOT / "source/upstream/mudlib"
BASE = MUD / "feature/npc/training_dummy.c"
DUMMIES = [
    MUD / "custom/zhenwu/npc/target_stake.c",
    MUD / "d/swaylan/lunmay/npc/stake.c",
    MUD / "d/baihua/npc/stone_lion.c",
]

def read(p): return p.read_text(encoding="utf-8")

def test_dummies_inherit_base():
    for p in DUMMIES:
        s = read(p)
        assert 'inherit "/feature/npc/training_dummy";' in s and "<npc.h>" not in s, p
        assert "setup();" in s, p

def test_base_dead_object():
    s = read(BASE)
    assert 'set("training_dummy", 1);' in s and "set_level(20);" in s
    assert "void fight_ob(object ob) { }" in s and "void kill_ob(object ob) { }" in s
    assert "int defend(int ability, int strength, object from) { return 0; }" in s
    assert "int absorb(int ability, int strength, object from) { return 0; }" in s
    b = s.split("varargs int receive_damage", 1)[1].split("}", 1)[0]
    assert "return damage;" in b
    assert "varargs int consume_stat(string type, int damage, object who) { return 0; }" in s
    assert "varargs int damage_stat(string type, int damage, object who) { return 0; }" in s
    assert "void die() { }" in s

def test_no_condition_or_poison():
    s = read(MUD / "feature/char/condition.c")
    head = s.split("set_condition(string cnd, mixed info)", 1)[1].split("conditions[cnd] = info;", 1)[0]
    assert 'query("training_dummy")' in head
    for p in ("custom/condition/weapon_poison.c", "daemon/condition/blue_venom.c"):
        b = read(MUD / p).split("void poison(object me, object from)", 1)[1].split("tell_object", 1)[0]
        assert 'query("training_dummy")' in b, p
    assert '!victim->query("training_dummy")' in read(MUD / "daemon/race/blackteeth/gnaw.c")

def test_steal_acupuncture_backstab():
    assert '"空空如也，你無從下手。\\n"' in read(MUD / "cmds/std/steal.c")
    assert '"沒有經脈穴道，你無從下手。\\n"' in read(MUD / "cmds/std/acupuncture.c")
    s = read(MUD / "cmds/std/backstab.c")
    assert "#define DUMMY_BACKSTAB_LIMIT    30" in s
    assert 'me->query_skill("backstab", 1) < DUMMY_BACKSTAB_LIMIT' in s
    assert "TARGET_STAKE" not in s
    assert s.count("!dummy && living(victim) && defend > ability") == 2
    assert 'if( !dummy ) me->gain_score("mortal sin", bonus);' in s

if __name__ == "__main__":
    for name, fn in list(globals().items()):
        if name.startswith("test_") and callable(fn):
            fn()
    print("ok")
