// /d/qiaoyin/inn2.c — 喬陰縣（J16）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "金水客棧二樓");
    set("long", @LONG
這裡是金水客棧的二樓，或者應該說是一樓和二樓之間的閣樓，這有座木梯通往樓下，靠窗一面是二樓的雅座，往北則通往客房。
LONG
    );
    set("exits", ([
        "down" : __DIR__"inn",
    ]));
    set("objects", ([
        __DIR__"npc/cao_xuanzhi" : 1,
        "/d/qiaoyin/npc/yin_euyen" : 1,
    ]));
    set("map/layer", "二樓");
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
