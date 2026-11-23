// /d/qiaoyin/north_street3.c — 喬陰縣（L8）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "北大街");
    set("long", @LONG
北大街的南段，東邊傳來叮叮噹噹的打鐵聲，原來是一間鐵匠鋪，鋪子門口堆著一些剛打好的鋤頭與柴刀，幾個莊稼漢正蹲在一旁挑揀。街上不時有些遊手好閒的人晃來晃去，路人見了都繞道而行。
LONG
    );
    set("exits", ([
        "north" : __DIR__"north_street2",
        "east" : __DIR__"smithy",
        "south" : __DIR__"tree_tomb",
    ]));
    set("objects", ([
        "/d/qiaoyin/npc/vagabond" : 1,
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
