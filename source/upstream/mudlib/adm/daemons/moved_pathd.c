/*---
description: 搬家對照：NPC 與道具檔案搬到新資料夾後，把存檔裡記的舊路徑換成新路徑。
design: docs/NPC_ITEM_PLACEMENT.md（2026-11-23）
note: - 對照表在 /adm/etc/moved_paths，一行「舊路徑 新路徑」，# 開頭是註解。
      - 玩家私人儲物箱、自動載入的物品存的是物品檔的路徑；檔案搬走後舊路徑載不到，
        取出時先經過 resolve() 換成新路徑。
      - 搬過不只一次的會一路換到最後的位置。
---*/

#define TABLE_FILE "/adm/etc/moved_paths"

static mapping moved;

void load_table()
{
    string s, *line, from, to;
    int i;

    moved = ([]);
    if( !stringp(s = read_file(TABLE_FILE)) ) return;
    line = explode(s, "\n");
    for(i=0; i<sizeof(line); i++) {
        if( !sizeof(line[i]) || line[i][0] == '#' ) continue;
        if( sscanf(line[i], "%s %s", from, to) != 2 ) continue;
        moved[from] = to;
    }
}

void create()
{
    seteuid(getuid());
    load_table();
}

// 舊路徑（可帶或不帶 .c）換成現在的路徑；沒有搬過的照原樣傳回。
string resolve(string file)
{
    string key;
    int n;

    if( !stringp(file) ) return file;
    if( !mapp(moved) ) load_table();
    key = file;
    if( strlen(key) > 2 && key[<2..<1] == ".c" ) key = key[0..<3];
    // 一路換到最後的位置；最多換 10 次，避免對照表寫成循環時卡住。
    while( !undefinedp(moved[key]) && n++ < 10 ) key = moved[key];
    if( key == file || key + ".c" == file ) return file;
    return key;
}

mapping query_table() { return copy(moved); }
