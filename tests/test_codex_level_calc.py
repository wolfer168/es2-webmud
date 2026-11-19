import importlib.util
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def _load():
    spec = importlib.util.spec_from_file_location('bpc', ROOT / 'tools/build_player_codex.py')
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


def test_level_calc_data_from_class_and_race_daemons():
    d = _load().level_calc_data()
    classes = {c['id']: c for c in d['classes']}
    assert list(classes) == ['fighter', 'taoist', 'alchemist', 'soldier', 'scholar', 'monk', 'thief', 'commoner']
    assert classes['fighter']['name'] == '武者'
    assert [i['name'] for i in classes['fighter']['items']] == ['實戰經驗', '武術造詣', '武學之道']
    assert [i['name'] for i in classes['commoner']['items']] == ['江湖歷練']
    races = {r['id']: r for r in d['races']}
    assert len(races) == 12 and d['races'][0]['id'] == 'human'
    assert races['yaksa']['base'] == 140 and races['yaksa']['caps']['scholar'] == -1
    assert races['human']['caps']['fighter'] == 50 and races['human']['caps']['commoner'] == 50


def test_template_has_level_calc():
    s = (ROOT / 'tools/codex_player_template.html').read_text(encoding='utf-8')
    assert "{ key: 'level', label: '升級經驗' }" in s
    assert 'if (cur === \'level\') return renderLevel();' in s
    assert '這個種族不能擔任這個職業' in s
