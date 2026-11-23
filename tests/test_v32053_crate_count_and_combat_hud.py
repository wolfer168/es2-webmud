from pathlib import Path

ROOT=Path(__file__).resolve().parents[1]
def read(rel): return (ROOT/rel).read_text(encoding="utf-8")

def test_strength_controls_how_many_40kg_crates_can_be_carried():
    crate=read("source/upstream/mudlib/d/snow/obj/crate.c")
    combat=read("source/upstream/mudlib/feature/char/combat.c")
    char=read("source/upstream/mudlib/std/char.c")
    assert "set_weight(40000)" in crate
    assert 'case "carriage"' in combat
    assert 'query_attr("str") * query_attr("str") * 200' in combat
    assert 'query_encumbrance() + ob->weight() > query_strength("carriage")' in char

def test_loaded_crates_are_counted_one_by_one():
    s=read("source/upstream/mudlib/d/snow/obj/wagon.c")
    assert 'ob->id("crate")' in s
    assert 'add_temp("wage_crates", 1)' in s

def test_foreman_pays_25_per_delivered_crate():
    s=read("source/upstream/mudlib/d/snow/npc/foreman.c")
    assert 'crates = me->query_temp("wage_crates")' in s
    assert 'crates * 25' in s
    assert 'delete_temp("wage_crates")' in s
    assert 'money->move(me)' in s
    assert 'command("give ' not in s

def test_combat_hud_has_10_blocks_and_no_exact_values():
    s=read("web/app.js")
    block=s[s.index("function combatStat"):s.index("function combatCard")]
    assert "const segments=10" in block
    assert 'const value=' not in block
    assert '<b>' not in block
    assert 'title="${escContext(value)}"' not in block
