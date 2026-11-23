"""NPC 與道具歸位後，測試找檔案用的小工具（docs/NPC_ITEM_PLACEMENT.md）。

搬家對照表是 source/upstream/mudlib/adm/etc/moved_paths（遊戲裡的 moved_pathd 也讀同一張表）。
自訂裝備庫（custom/armor、custom/weapon）裡被區域 NPC 用到的裝備已經搬到各區域的 obj
資料夾或 /d/obj；原本以「裝備庫資料夾」為單位的檢查改用 LibDir，仍然檢查同一批裝備。
"""
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MUD = ROOT / 'source' / 'upstream' / 'mudlib'


def _load():
    moved = {}
    for line in (MUD / 'adm' / 'etc' / 'moved_paths').read_text(encoding='utf-8').splitlines():
        if not line.strip() or line.startswith('#'):
            continue
        old, new = line.split()
        moved[old] = new
    return moved


MOVED = _load()


def resolve(path):
    """舊路徑（'/custom/armor/cloth/x'、'custom/armor/cloth/x.c' 都可以）→ 現在的檔案 Path。"""
    p = '/' + str(path).lstrip('/')
    if p.endswith('.c'):
        p = p[:-2]
    for _ in range(10):
        if p not in MOVED:
            break
        p = MOVED[p]
    return MUD / (p.lstrip('/') + '.c')


class LibDir:
    """原本的裝備庫資料夾：`/` 找得到搬走的檔案，glob 也會列出搬走的檔案。"""

    def __init__(self, path):
        self.path = Path(path)
        self.rel = '/' + self.path.relative_to(MUD).as_posix()

    def __truediv__(self, name):
        name = str(name)
        if not name.endswith('.c') and (self.path / name).is_dir():
            return LibDir(self.path / name)
        return resolve(f'{self.rel}/{name}')

    def glob(self, pattern):
        here = list(self.path.glob(pattern))
        prefix = self.rel + '/'
        moved = [resolve(old) for old in MOVED
                 if old.startswith(prefix) and '/' not in old[len(prefix):]
                 and Path(old[len(prefix):] + '.c').match(pattern)]
        return sorted(set(here + moved))

    def __str__(self):
        return str(self.path)


def current(p):
    """檔案還在原地就照用；搬走了就照對照表找到現在的位置（p 是 MUD 底下的完整 Path）。"""
    p = Path(p)
    if p.exists():
        return p
    return resolve(p.relative_to(MUD).as_posix())
