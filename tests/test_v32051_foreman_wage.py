from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
FOREMAN = ROOT / "source/upstream/mudlib/d/snow/npc/foreman.c"
CRATE = ROOT / "source/upstream/mudlib/d/snow/obj/crate.c"


def text(path):
    return path.read_text(encoding="utf-8")


def test_crate_wage_is_25_coin():
    s = text(CRATE)
    assert 'set("wage", 25);' in s


def test_foreman_pays_fresh_wage_directly_to_player():
    s = text(FOREMAN)
    assert 'money->set_amount(amount);' in s
    assert 'money->move(me)' in s
    assert 'money->move(this_object())' not in s
    assert 'give coin to ' not in s


def test_wage_is_only_cleared_after_successful_payment():
    s = text(FOREMAN)
    move_pos = s.index('if( !money->move(me) )')
    delete_pos = s.index('me->delete_temp("wage_deserved");')
    assert move_pos < delete_pos
