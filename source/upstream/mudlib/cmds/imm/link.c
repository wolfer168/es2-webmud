#include <command.h>

inherit F_CLEAN_UP;

private mapping opposite = ([
    "north"     : "south",
    "northup"   : "southdown",
    "northdown" : "southup",
    "south"     : "north",
    "southup"   : "northdown",
    "southdown" : "northup",
    "east"      : "west",
    "eastup"    : "westdown",
    "eastdown"  : "westup",
    "west"      : "east",
    "westdown"  : "eastup",
    "westup"    : "eastdown",
    "up"        : "down",
    "down"      : "up",
    "northeast" : "southwest",
    "northwest" : "southeast",
    "southeast" : "northwest",
    "southwest" : "northeast",
]);

/* 回傳值：1 = 出口已存在，0 = 出口不存在，-1 = exits 格式無法辨識。 */
private int has_exit(string source, string direction)
{
    string marker, exits;
    int start, end;

    marker = "set(\"exits\", ([";
    start = strsrch(source, marker);

    if( start < 0 ) return 0;

    end = strsrch(source, "]));", start);
    if( end < 0 ) return -1;

    exits = source[start..end];

    if( strsrch(exits, "\"" + direction + "\"") >= 0 )
        return 1;

    return 0;
}

/* 在房間原始碼中加入一個出口。 */
private string add_exit(string source, string direction, string target)
{
    string marker, insert;
    int start, at;

    marker = "set(\"exits\", ([";
    insert = "\n        \"" + direction + "\" : \"" + target + "\",";

    start = strsrch(source, marker);

    /* 原本沒有 exits 時，在 setup() 前新增一整段設定。 */
    if( start < 0 ) {
        at = strsrch(source, "setup();");

        if( at < 0 ) return 0;

        return source[0..at - 1]
            + "set(\"exits\", ([\n"
            + "        \"" + direction + "\" : \"" + target + "\",\n"
            + "    ]));\n\n    "
            + source[at..];
    }

    at = start + strlen(marker);

    return source[0..at - 1] + insert + source[at..];
}

private string remove_extension(string file)
{
    if( strlen(file) > 2 && file[<2..<1] == ".c" )
        return file[0..<3];

    return file;
}

int main(object me, string arg)
{
    string room_a, room_b, direction, reverse;
    string file_a, file_b, source_a, source_b;
    string new_a, new_b;
    int exit_a, exit_b;

    SECURED_WIZARD_COMMAND;

    if( wiz_level(me) < wiz_level("(imm)") )
        return notify_fail("只有 imm 以上的巫師可以使用 link。\n");

    if( !arg || sscanf(arg, "%s %s %s", room_a, room_b, direction) != 3 )
        return notify_fail(
            "指令格式：link <房間甲> <房間乙> <方向>\n"
            "例如：link /d/snow/area/room1 /d/snow/area/room2 east\n"
        );

    direction = lower_case(direction);

    if( undefinedp(opposite[direction]) )
        return notify_fail("不支援的方向。\n");

    reverse = opposite[direction];

    room_a = remove_extension(resolve_path(me->query("cwd"), room_a));
    room_b = remove_extension(resolve_path(me->query("cwd"), room_b));

    if( room_a == room_b )
        return notify_fail("不能將房間連接到自己。\n");

    file_a = room_a + ".c";
    file_b = room_b + ".c";

    seteuid(geteuid(me));

    if( file_size(file_a) < 0 )
        return notify_fail("找不到房間檔案：" + file_a + "\n");

    if( file_size(file_b) < 0 )
        return notify_fail("找不到房間檔案：" + file_b + "\n");

    source_a = read_file(file_a);
    source_b = read_file(file_b);

    if( !stringp(source_a) || !stringp(source_b) )
        return notify_fail("無法讀取其中一個房間檔案。\n");

    /* room_a 的指定方向不可覆蓋。 */
    exit_a = has_exit(source_a, direction);

    if( exit_a < 0 )
        return notify_fail(room_a + " 的 exits 設定格式無法辨識。\n");

    if( exit_a )
        return notify_fail(room_a + " 的 " + direction + " 出口已存在。\n");

    new_a = add_exit(source_a, direction, room_b);

    if( !stringp(new_a) )
        return notify_fail("無法在 " + room_a + " 建立出口。\n");

    /*
     * room_b 的反向出口若已存在，保留原本出口。
     * 此時只建立 room_a 前往 room_b 的單向出口。
     */
    exit_b = has_exit(source_b, reverse);

    if( exit_b < 0 )
        return notify_fail(room_b + " 的 exits 設定格式無法辨識。\n");

    if( !exit_b ) {
        new_b = add_exit(source_b, reverse, room_a);

        if( !stringp(new_b) )
            return notify_fail("無法在 " + room_b + " 建立反向出口。\n");
    }

    /* 先建立備份。 */
    write_file(file_a + ".link.bak", source_a, 1);

    if( !exit_b )
        write_file(file_b + ".link.bak", source_b, 1);

    /* 寫入 room_a 的出口。 */
    if( !write_file(file_a, new_a, 1) )
        return notify_fail("無法寫入：" + file_a + "\n");

    /* 僅在 room_b 沒有反向出口時，才寫入 room_b。 */
    if( !exit_b && !write_file(file_b, new_b, 1) ) {
        write_file(file_a, source_a, 1);
        return notify_fail("無法寫入：" + file_b + "，已還原第一個房間。\n");
    }

    write("已建立出口：\n");
    write(room_a + " 的 " + direction + " → " + room_b + "\n");

    if( exit_b ) {
        write(room_b + " 的 " + reverse + " 出口原本已存在。\n");
        write("已建立單向出口，room_b 不會新增反向道路。\n");
    } else {
        write(room_b + " 的 " + reverse + " → " + room_a + "\n");
        write("已建立雙向出口。\n");
    }

    command("update " + file_a);

    if( !exit_b )
        command("update " + file_b);

    return 1;
}

int help(object me)
{
    write(@HELP
指令格式：link <房間甲> <房間乙> <方向>

範例：
link /d/snow/area/room1 /d/snow/area/room2 east

若 room2 的 west 出口不存在：
room1 east → room2
room2 west → room1

若 room2 的 west 出口已存在：
room1 east → room2
room2 保留原本 west 出口，形成單向道路。

支援方向：
north south east west up down
northeast northwest southeast southwest
HELP
    );

    return 1;
}