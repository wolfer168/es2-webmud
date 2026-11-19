"""網頁斷線保留（docs/WEB_RESUME.md）：橋接程式與網頁兩邊要對得上。"""
from pathlib import Path
R = Path(__file__).parents[1]
srv = (R / 'server/index.js').read_text(encoding='utf-8')
app = (R / 'web/app.js').read_text(encoding='utf-8')
assert "RESUME_HOLD_MS??600000" in srv and "RESUME_MAX_LINES??500" in srv
assert "@@BRIDGE|TOKEN|" in srv and "@@BRIDGE|RESUMED|" in srv
assert "searchParams.get('resume')" in srv
assert "CLOSE_MANUAL=4000" in srv and "CLOSE_REPLACED=4001" in srv
assert "handleBridgeMessage(raw)" in app and "'?resume='+encodeURIComponent(token)" in app
assert "ws.close(4000,'manual')" in app
assert "sessionStorage" in app
assert (R / 'docs/WEB_RESUME.md').exists()
print('web resume checks passed')
