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
        return file[0..<3] + ".denpc.bak";

    return file + ".denpc.bak";
}

/*
 * 將指定 NPC 的數量減少 amount。
 * 數量為 0 時，房間不再生成該 NPC。
 */
private string reduce_npc(string source, string npc_file, int amount)
{
    string marker, objects, *lines;
    string result, before, old_line;
    int start, end, i, old_amount, found;

    marker = "set(\"objects\", ([";
    start = strsrch(source, marker);

    if( start < 0 )
        return 0;

    end = strsrch(source, "]));", start);

    if( end < 0 )
        return 0;

    objects = source[start..end];
    lines = explode(objects, "\n");

    for( i = 0; i < sizeof(lines); i++ ) {
        if( strsrch(lines[i], "\"" + npc_file + "\"") >= 0 ) {
            old_line = lines[i];

            if( sscanf(old_line, "%s : %d", before, old_amount) != 2 )
                return 0;

            if( old_amount < amount )
                return 0;

            lines[i] = "    \"" + npc_file + "\" : "
                + (old_amount - amount) + ",";

            found = 1;
            break;
        }
    }

    if( !found )
        return 0;

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
    string room_arg, npc_id, room_path;
    string file, source, new_source, npc_file, err;
    int amount;

    SECURED_WIZARD_COMMAND;

    seteuid(geteuid(me));

    if( !arg )
        return notify_fail(
            "指令格式：denpc [房間路徑] <NPC ID> [數量]\n"
        );

    amount = 1;

    /*
     * denpc <房間路徑> <NPC ID> <數量>
     */
    if( sscanf(arg, "%s %s %d", room_arg, npc_id, amount) == 3 ) {
        room_path = remove_extension(
            resolve_path(me->query("cwd"), room_arg)
        );
    }

    /*
     * denpc <NPC ID> <數量>
     */
    else if( sscanf(arg, "%s %d", npc_id, amount) == 2 ) {
        room = environment(me);
    }

    /*
     * denpc <房間路徑> <NPC ID>
     */
    else if( sscanf(arg, "%s %s", room_arg, npc_id) == 2 ) {
        room_path = remove_extension(
            resolve_path(me->query("cwd"), room_arg)
        );
    }

    /*
     * denpc <NPC ID>
     */
    else {
        npc_id = arg;
        room = environment(me);
    }

    if( amount < 1 )
        return notify_fail("減少數量必須為 1 以上。\n");

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

    if( !objectp(room) || !room->query("short") )
        return notify_fail("指定目標不是可編輯的房間。\n");

    npc = present(npc_id, room);

    if( !objectp(npc) )
        return notify_fail("指定房間沒有這個 NPC。\n");

    if( userp(npc)
     || !function_exists("is_character", npc)
     || !npc->is_character() )
        return notify_fail(
            "denpc 只能減少 NPC，不能指定玩家、物品或其他檔案。\n"
        );

    npc_file = base_name(npc);
    file = room_source_file(room);

    if( file_size(file) < 0 )
        return notify_fail("找不到房間原始檔：" + file + "\n");

    source = read_file(file);

    if( !stringp(source) )
        return notify_fail("無法讀取房間原始檔。\n");

    new_source = reduce_npc(source, npc_file, amount);

    if( !stringp(new_source) )
        return notify_fail(
            "房間原始檔內找不到 " + npc_file
            + " 的 objects 設定，或目前 NPC 數量不足。\n"
        );

    write_file(backup_file(file), source, 1);

    if( !write_file(file, new_source, 1) )
        return notify_fail("無法寫入房間原始檔。\n");

    write("已減少 NPC："
        + npc->name() + " (" + npc_file + ")\n");

    write("減少數量：" + amount + "\n");
    write("房間：" + remove_extension(file) + "\n");
    write("備份檔：" + backup_file(file) + "\n");

    reload_room(me, room, file);

    return 1;
}

int help(object me)
{
    write("指令格式：denpc [房間路徑] <NPC ID> [數量]\n");
    write("\n");
    write("未指定房間時，預設使用目前所在房間。\n");
    write("未指定數量時，預設減少 1。\n");
    write("\n");
    write("範例：\n");
    write("denpc woman\n");
    write("denpc woman 3\n");
    write("denpc /custom/wizroom/w/dragon_inn woman\n");
    write("denpc /custom/wizroom/w/dragon_inn woman 3\n");
    write("\n");
    write("每次使用會減少指定 NPC 的數量。\n");
    write("數量減至 0 後，房間不再生成該 NPC。\n");
    write("每次修改前會建立 .denpc.bak 備份。\n");

    return 1;
}