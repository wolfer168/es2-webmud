"""說明檔的色碼前面一定要有 ESC 控制字元（2026-11-24）。

少了 ESC，`[1;33m` 會直接以文字顯示在遊戲與網頁上（撼山鎚法說明檔曾發生）。"""
from pathlib import Path
import re

HELP = Path(__file__).resolve().parents[1] / 'source/upstream/mudlib/docs/help'


def test_help_color_codes_have_escape():
    bad = []
    for f in sorted(HELP.glob('*.txt')):
        s = f.read_text(encoding='utf-8', errors='replace')
        for n, line in enumerate(s.splitlines(), 1):
            if re.search(r'(?<!\x1b)\[[0-9;]+m', line):
                bad.append(f'{f.name}:{n}')
    assert not bad, '色碼少了 ESC：' + '、'.join(bad)
