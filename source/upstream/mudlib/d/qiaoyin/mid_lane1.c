// /d/qiaoyin/mid_lane1.c — 喬陰縣（H6）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "街道");
    set("long", @LONG
一條不太寬的街道，兩旁的店面大多關著門，東邊是和豐當鋪的大門，門口掛著一塊褪了色的招牌。路邊的牆角堆著一些破竹簍，常有野狗在這裡翻找吃食，弄得滿地狼藉。
LONG
    );
    set("exits", ([
        "east" : __DIR__"pawnshop",
        "south" : __DIR__"mid_lane2",
    ]));
    set("objects", ([
        "/d/npc/wild_dog" : 1,
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
