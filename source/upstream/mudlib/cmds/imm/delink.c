#include <command.h>

inherit F_CLEAN_UP;

private mapping valid_directions = ([
    "north"     : 1,
    "northup"   : 1,
    "northdown" : 1,
    "south"     : 1,
    "southup"   : 1,
    "southdown" : 1,
    "east"      : 1,
    "eastup"    : 1,
    "eastdown"  : 1,
    "west"      : 1,
    "westup"    : 1,
    "westdown"  : 1,
    "up"        : 1,
    "down"      : 1,
    "northeast" : 1,
    "northwest" : 1,
    "southeast" : 1,
    "southwest" : 1,
]);

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
        return file[0..<3] + ".delink.bak";

    return file + ".delink.bak";
}

/*
 * 從 exits 設定中移除指定方向。
 * 每個出口需各自占一行，例如：
 * "east" : "/d/snow/area/room2",
 */
private string remove_exit(string source, string direction)
{
    string marker, exits, *lines;
    string result;
    int start, end, i, found;

    marker = "set(\"exits\", ([";
    start = strsrch(source, marker);

    if( start < 0 ) return 0;

    end = strsrch(source, "]));", start);
    if( end < 0 ) return 0;

    exits = source[start..end];
    lines = explode(exits, "\n");

    for( i = 0; i < sizeof(lines); i++ ) {
        if( strsrch(lines[i], "\"" + direction + "\"") >= 0 ) {
            lines[i] = 0;
            found = 1;
            break;
        }
    }

    if( !found ) return 0;

    lines -= ({ 0 });
    result = implode(lines, "\n");

    return source[0..start - 1]
        + result
        + source[end + 1..];
}

int main(object me, string arg)
{
    object room;
    string direction, file, source, new_source;

    SECURED_WIZARD_COMMAND;

    if( !arg )
        return notify_fail("指令格式：delink <方向>\n");

    direction = lower_case(arg);

    if( undefinedp(valid_directions[direction]) )
        return notify_fail("不支援的方向。\n");

    room = environment(me);

    if( !objectp(room) || !room->query("short") )
        return notify_fail("你目前不在可編輯的房間內。\n");

    file = room_source_file(room);

    seteuid(geteuid(me));

    if( file_size(file) < 0 )
        return notify_fail("找不到目前房間的原始檔：" + file + "\n");

    source = read_file(file);

    if( !stringp(source) )
        return notify_fail("無法讀取房間原始檔。\n");

    new_source = remove_exit(source, direction);

    if( !stringp(new_source) )
        return notify_fail(
            "目前房間沒有 " + direction
            + " 出口，或 exits 設定格式無法辨識。\n"
        );

    write_file(backup_file(file), source, 1);

    if( !write_file(file, new_source, 1) )
        return notify_fail("無法寫入房間檔案。\n");

    write("已刪除目前房間的 " + direction + " 出口。\n");
    write("備份檔：" + backup_file(file) + "\n");

    call_other("/cmds/wiz/update", "main", me, file);

    return 1;
}

int help(object me)
{
    write(@HELP
指令格式：delink <方向>

範例：
delink east

此指令只會刪除目前房間指定方向的出口，
不會刪除目的房間的反向出口。

HELP
    );

    return 1;
}