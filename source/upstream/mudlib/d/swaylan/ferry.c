// /d/swaylan/ferry.c — 水嵐縣（U8）。房間敘述依設計表需求撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "渡口");
    set("long", @LONG
羿水流到這裡轉了一個大彎，河面寬闊，對岸五堂鎮的鯉君渡隱約可見。岸邊用粗木樁搭起一座棧橋，橋板被往來的腳步踩得發亮，繫船的麻繩一圈圈纏在樁上，河水拍著樁腳，嘩嘩作響。
LONG
    );
    set("exits", ([
        "south" : __DIR__"north_gate",
    ]));
    set("no_fight", 1);
    set("map/area", "水嵐縣");
    set("fishing", 1);
    set("detail/河水", "棧橋下的羿水拍著樁腳，打著旋兒流過，樁邊的暗影裡有魚群徘徊，在橋邊垂釣 (fish) 想必有魚上鉤。");
    setup();
    replace_program(ROOM);
}
