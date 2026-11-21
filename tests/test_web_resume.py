"""網頁斷線保留（docs/WEB_RESUME.md）：橋接程式與網頁兩邊要對得上。"""
from pathlib import Path
R = Path(__file__).parents[1]
srv = (R / 'server/index.js').read_text(encoding='utf-8')
app = (R / 'web/app.js').read_text(encoding='utf-8')
assert "RESUME_HOLD_MS??600000" in srv and "RESUME_MAX_LINES??500" in srv
assert "@@BRIDGE|TOKEN|" in srv and "@@BRIDGE|RESUMED|" in srv
assert "searchParams.get('resume')" in srv
assert "CLOSE_MANUAL=4000" in srv and "CLOSE_REPLACED=4001" in srv
assert "handleBridgeMessage(raw)" in app and "'&resume='+encodeURIComponent(token)" in app
# 只有手機保留；電腦版不帶 hold=1，橋接程式就不發憑證、不保留。
assert "RESUME_ENABLED" in app and "'?hold=1'" in app and "searchParams.get('hold')==='1'" in srv
assert "if(!s.holdable)return;" in srv and "if(!s.holdable||" in srv
# 斷線時還在登入畫面，接回後不能自動送 webhud。
assert "if(resumeInGame)setTimeout(()=>pollHud(true,true),150);" in app
assert "ws.close(4000,'manual')" in app
assert "sessionStorage" in app
assert (R / 'docs/WEB_RESUME.md').exists()
print('web resume checks passed')
