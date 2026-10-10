from pathlib import Path
import re

MUD = Path(__file__).resolve().parents[1] / 'source' / 'upstream' / 'mudlib'


def read(p):
    return (MUD / p).read_text(encoding='utf-8')


def test_hook_in_advance_skill():
    s = read('feature/char/skill.c')
    body = s[s.index('varargs void advance_skill(string skill, int amount)\n{'):]
    body = body[:body.index('\n}\n')]
    assert 'old_level = skills[skill];' in body
    assert 'roll_attr_growth(skill, old_level, skills[skill]);' in body


def test_growth_table_and_message():
    s = read('feature/char/skill.c')
    assert '#define ATTR_GROWTH_MAX 50' in s
    # 2026-10-11 使用者定案的基礎機率
    for line in ['if( value <= 10 ) return 100;', 'if( value <= 15 ) return 90;',
                 'if( value <= 20 ) return 80;', 'if( value <= 25 ) return 60;',
                 'if( value <= 30 ) return 40;', 'if( value <= 40 ) return 30;',
                 'if( value <= 45 ) return 15;', 'return 10;']:
        assert line in s
    assert 'attr_growth_base(value) * (100 + lv) * 3 / 5' in s
    assert '"attr_growth/" + skill' in s
    assert 'if( !userp(this_object()) ) return;' in s
    assert '"提高了！' in s


def test_growth_mapping():
    s = read('feature/char/skill.c')
    table = s[s.index('static mapping ATTR_GROWTH = (['):]
    table = table[:table.index(']);')]
    got = dict(re.findall(r'"([^"]+)":\s*"([a-z]+)"', table))
    assert got == {
        'unarmed': 'str', 'force': 'con', 'dodge': 'dex', 'parry': 'cps',
        'spells': 'spi', 'magic': 'spi', 'backstab': 'cor', 'killerhood': 'cor',
        'literate': 'int', 'archaic attainment': 'int',
    }
