// /d/ziyan/ferry.c — 紫煙鎮（G4）。房間敘述依設計表需求撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "渡口");
    set("long", @LONG
紫煙鎮的渡口緊挨著羿水，幾根木樁歪歪斜斜地插在泥灘上，木樁邊繫著船夫的小船，隨著水波輕輕搖晃。河面寬闊，對岸的五堂鎮隱約可見，過河的多是挑擔的小販與行腳的旅人，船板踩上去吱呀作響。
LONG
    );
    set("exits", ([
        "south" : __DIR__"dirt_road",
    ]));
    // 兩岸各自產生一位船夫：小黃在這裡，老駱在對岸的五堂鎮河邊（使用者指示，2026-11-19）。
    set("objects", ([
        "/d/ziyan/npc/huang" : 1,
    ]));
    set("no_fight", 1);
    set("map/area", "水嵐縣");
    set("fishing", 1);
    set("detail/河水", "渡口的羿水在泥灘邊緩緩流動，木樁邊水色微黃，不時有魚吐出水泡，垂釣 (fish) 的人多半不會空手而回。");
    setup();
    replace_program(ROOM);
}
