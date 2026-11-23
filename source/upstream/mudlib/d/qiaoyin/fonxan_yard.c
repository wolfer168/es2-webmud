// /d/qiaoyin/fonxan_yard.c — 喬陰縣（V8）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "別院");
    set("long", @LONG
正廳東邊的一處別院，院子裡種著幾株老梅與修竹，牆角一口古井上覆著木蓋。一張石桌旁擺著幾個石凳，四周十分清靜，只聽得見風吹竹葉的沙沙聲，看來是封山派用來招待貴客的地方。
LONG
    );
    set("exits", ([
        "west" : __DIR__"fonxan_hall",
    ]));
    set("objects", ([
        "/d/qiaoyin/npc/wu_yu_nun" : 1,
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
