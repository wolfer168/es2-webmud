#include <command.h>

inherit F_CLEAN_UP;

private string remove_extension(string file)
{
    if( strlen(file) > 2 && file[<2..<1] == ".c" )
        return file[0..<3];

    return file;
}

private string room_source_file(object room)
{
    string file;
    int clone_mark;

    file = file_name(room);

    clone_mark = strsrch(file, "#");
    if( clone_mark >= 0 )
        file = file[0..clone_mark - 1];

    if( strlen(file) < 2 || file[<2..<1] != ".c" )
        file += ".c";

    return file;
}

private string backup_file(string file)
{
    if( strlen(file) > 2 && file[<2..<1] == ".c" )
        return file[0..<3] + ".adnpc.bak";

    return file + ".adnpc.bak";
}

/*
 * 將 NPC 加入房間的 objects 設定。
 * 若該 NPC 已存在，數量會累加。
 */
private string add_npc(string source, string npc_file, int amount)
{
    string marker, objects, *lines;
    string result, before, old_line;
    int start, end, i, old_amount, found, at;

    marker = "set(\"objects\", ([";
    start = strsrch(source, marker);

    /*
     * 房間原本沒有 objects 設定時，新增完整設定區塊。
     */
    if( start < 0 ) {
        at = strsrch(source, "setup();");

        if( at < 0 )
            return 0;

        return source[0..at - 1]
            + "set(\"objects\", ([\n"
            + "    \"" + npc_file + "\" : " + amount + ",\n"
            + "]));\n\n"
            + source[at..];
    }

    end = strsrch(source, "]));", start);

    if( end < 0 )
        return 0;

    objects = source[start..end];
    lines = explode(objects, "\n");

    /*
     * 已有相同 NPC 時，將原數量加上新數量。
     */
    for( i = 0; i < sizeof(lines); i++ ) {
        if( strsrch(lines[i], "\"" + npc_file + "\"") >= 0 ) {
            old_line = lines[i];

            if( sscanf(old_line, "%s : %d", before, old_amount) != 2 )
                return 0;

            lines[i] = "    \"" + npc_file + "\" : "
                + (old_amount + amount) + ",";

            found = 1;
            break;
        }
    }

    /*
     * 房間尚未放置這個 NPC 時，在 objects 的第一行後加入。
     */
    if( !found ) {
        lines = lines[0..0]
            + ({ "    \"" + npc_file + "\" : " + amount + "," })
            + lines[1..];
    }

    result = implode(lines, "\n");

    return source[0..start - 1]
        + result
        + source[end + 1..];
}

/*
 * 重新載入房間。
 * 先暫時移出房間內玩家，成功載入後再送回新房間。
 */
private int reload_room(object me, object room, string file)
{
    object new_room, *inventory;
    string err;
    int i;

    inventory = all_inventory(room);

    for( i = 0; i < sizeof(inventory); i++ ) {
        if( userp(inventory[i]) ) {
            inventory[i]->set_temp("last_location", file);
            inventory[i]->move(VOID_OB, 1);
        } else {
            inventory[i] = 0;
        }
    }

    if( find_object(file) )
        destruct(room);

    write("重新編譯 " + file + " ...\n");

    err = catch(new_room = load_object(file));

    if( err || !objectp(new_room) ) {
        write("編譯失敗：" + err);
        return 0;
    }

    write("成功。\n");

    for( i = 0; i < sizeof(inventory); i++ ) {
        if( inventory[i] && userp(inventory[i]) )
            inventory[i]->move(new_room);
    }

    return 1;
}

int main(object me, string arg)
{
    object room, npc;
    string room_arg, npc_arg, room_path, npc_path;
    string file, source, new_source, err;
    int amount;

    SECURED_WIZARD_COMMAND;

    /*
     * 必須先取得巫師的有效權限，
     * 才能載入房間與 NPC 原始檔。
     */
    seteuid(geteuid(me));

    if( !arg )
        return notify_fail(
            "指令格式：adnpc [房間路徑] <NPC 路徑> [數量]\n"
        );

    amount = 1;

    /*
     * adnpc <房間路徑> <NPC 路徑> <數量>
     */
    if( sscanf(arg, "%s %s %d", room_arg, npc_arg, amount) == 3 ) {
        room_path = remove_extension(
            resolve_path(me->query("cwd"), room_arg)
        );
    }

    /*
     * adnpc <NPC 路徑> <數量>
     */
    else if( sscanf(arg, "%s %d", npc_arg, amount) == 2 ) {
        room = environment(me);
    }

    /*
     * adnpc <房間路徑> <NPC 路徑>
     */
    else if( sscanf(arg, "%s %s", room_arg, npc_arg) == 2 ) {
        room_path = remove_extension(
            resolve_path(me->query("cwd"), room_arg)
        );
    }

    /*
     * adnpc <NPC 路徑>
     */
    else {
        npc_arg = arg;
        room = environment(me);
    }

    if( amount < 1 )
        return notify_fail("NPC 數量必須為 1 以上。\n");

    if( !objectp(room) ) {
        if( file_size(room_path + ".c") < 0 )
            return notify_fail(
                "找不到房間檔案：" + room_path + ".c\n"
            );

        err = catch(room = load_object(room_path));

        if( err || !objectp(room) )
            return notify_fail(
                "無法載入房間：" + room_path + "\n"
            );
    }

    if( !room->query("short") )
        return notify_fail("指定目標不是可編輯的房間。\n");

    npc_path = remove_extension(
        resolve_path(me->query("cwd"), npc_arg)
    );

    err = catch(npc = load_object(npc_path));

    if( err || !objectp(npc) )
        return notify_fail(
            "無法載入 NPC 原始檔：" + npc_path + "\n"
            "請確認 NPC 來源路徑後重新下指令。\n"
        );

    if( userp(npc)
     || !function_exists("is_character", npc)
     || !npc->is_character() )
        return notify_fail(
            "指定檔案不是 NPC：" + npc_path + "\n"
            "請確認植入 NPC 路徑是否正確。\n"
        );

    file = room_source_file(room);

    if( file_size(file) < 0 )
        return notify_fail("找不到房間原始檔：" + file + "\n");

    source = read_file(file);

    if( !stringp(source) )
        return notify_fail("無法讀取房間原始檔。\n");

    new_source = add_npc(source, npc_path, amount);

    if( !stringp(new_source) )
        return notify_fail(
            "房間 objects 設定格式無法辨識，未作任何變更。\n"
        );

    write_file(backup_file(file), source, 1);

    if( !write_file(file, new_source, 1) )
        return notify_fail("無法寫入房間原始檔：" + file + "\n");

    write("已將 NPC 植入房間：\n");
    write(npc->name() + " (" + npc_path + ")\n");
    write("數量：" + amount + "\n");
    write("房間：" + remove_extension(file) + "\n");
    write("備份檔：" + backup_file(file) + "\n");

    reload_room(me, room, file);

    return 1;
}

int help(object me)
{
    write("指令格式：adnpc [房間路徑] <NPC 路徑> [數量]\n");
    write("\n");
    write("未填房間路徑時，預設植入目前所在房間。\n");
    write("未填數量時，預設為 1。\n");
    write("\n");
    write("範例：\n");
    write("adnpc /d/snow/npc/waiter\n");
    write("adnpc /d/snow/npc/waiter 2\n");
    write("adnpc /custom/wizroom/w/dragon_inn /d/snow/npc/waiter\n");
    write("adnpc /custom/wizroom/w/dragon_inn /d/snow/npc/waiter 3\n");
    write("\n");
    write("指令只允許植入 NPC，物品與其他檔案會被拒絕。\n");
    write("每次修改前會建立 .adnpc.bak 備份。\n");

    return 1;
}