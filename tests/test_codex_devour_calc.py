from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
TPL = ROOT / 'tools/codex_player_template.html'
DEVOUR = ROOT / 'source/upstream/mudlib/daemon/race/yaksa/devour.c'


def test_calc_tab_and_note():
    # 圖鑑的計算機分頁，第一個計算機是吞魂（使用者指示，2026-11-19）。
    s = TPL.read_text(encoding='utf-8')
    assert "{ key: 'calc', label: '計算機' }" in s
    assert "const CALCS = [{ key: 'devour', label: '夜叉吞魂' }];" in s
    assert 'calc: renderCalc' in s
    assert '<li>此數據為估算數值，每次吞魂皆有隨機性。</li>' in s
    assert '<li>吞食魂魄自第 11 隻起，不再保證大幅增加。</li>' in s


def test_calc_rules_match_devour():
    # 計算機的門檻、加成公式要跟 devour.c 一致。
    s = TPL.read_text(encoding='utf-8')
    d = DEVOUR.read_text(encoding='utf-8')
    assert 'return yaksa_ghost ? 250 + 25 * extra : 500 + 50 * extra;' in d
    assert 'const need = yaksa ? 250 + 25 * extra : 500 + 50 * extra;' in s
    assert 'int extra = count >= 10 ? count - 9 : 0;' in d
    assert 'const extra = n >= 10 ? n - 9 : 0;' in s
    assert 'gin = 1 + ghost_gin / 40;' in d and 'sen = 1 + rnd(ghost_gin / 80);' in d
    assert 'const g40 = Math.floor(G / 40), g80 = Math.floor(G / 80);' in s
    assert 'big = random(1000) < big_chance(count + 1);' in d
    table = [851, 725, 617, 525, 447, 381, 324, 276, 235, 200, 174, 152, 132, 115, 100, 87, 76, 66, 57, 50]
    assert 'const BIG_CHANCE = [' + ', '.join(map(str, table)) + '];' in s
    block = d[d.index('#define BIG_CHANCE'):d.index('})', d.index('#define BIG_CHANCE'))]
    assert [int(x) for x in re.findall(r'\d+', block)] == table
    # 第 20 次 20%、第 30 次 5%，且逐次遞減（使用者指示，2026-11-19）。
    assert table[9] == 200 and table[19] == 50 and table == sorted(table, reverse=True)
    assert 'if (nth <= 10) return 1000;' in d and 'if (nth > 30) return 50;' in d
    assert "const p = (nth <= 10 ? 1000 : nth > 30 ? 50 : BIG_CHANCE[nth - 11]) / 1000;" in s
    assert 'if (yaksa_ghost) ghost_gin *= 2;' in d and 'const G = yaksa ? G0 * 2 : G0;' in s


if __name__ == '__main__':
    test_calc_tab_and_note()
    test_calc_rules_match_devour()
    print('ok')
