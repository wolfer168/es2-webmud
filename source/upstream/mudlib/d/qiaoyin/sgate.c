// /d/qiaoyin/sgate.c — 喬陰縣（L16）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "喬陰縣城南門");
    set("long", @LONG
喬陰縣城的南門，城牆上的磚石有些斑駁，看來已經許久沒有修繕。城門外是一片平坦的田野，阡陌縱橫，此刻城門卻已關上，幾名官兵守在門邊，不讓閒雜人等隨意出城。
LONG
    );
    set("exits", ([
        "north" : __DIR__"south_street2",
    ]));
    set("objects", ([
        "/d/npc/garrison" : 4,
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
