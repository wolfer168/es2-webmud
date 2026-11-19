from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
TPL = ROOT / 'tools/codex_player_template.html'
DEVOUR = ROOT / 'source/upstream/mudlib/daemon/race/yaksa/devour.c'


def test_calc_tab_and_note():
    # 圖鑑的計算機分頁，第一個計算機是吞魂（使用者指示，2026-11-19）。
    s = TPL.read_text(encoding='utf-8')
    assert "{ key: 'calc', label: '計算機' }" in s
    assert "const CALCS = [{ key: 'devour', label: '夜叉吞魂' }];" in s
    assert 'calc: renderCalc' in s
    assert '此數據為估算數值，每次吞魂皆有隨機性。' in s


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
    assert 'big = count < 10 || random(10 + rnd(count)) < 10;' in d
    assert 'for (let i = 0; i < n; i++) p += 10 / (10 + i);' in s
    assert 'if (yaksa_ghost) ghost_gin *= 2;' in d and 'const G = yaksa ? G0 * 2 : G0;' in s


if __name__ == '__main__':
    test_calc_tab_and_note()
    test_calc_rules_match_devour()
    print('ok')
