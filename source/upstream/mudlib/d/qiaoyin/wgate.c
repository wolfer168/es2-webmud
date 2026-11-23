// /d/qiaoyin/wgate.c — 喬陰縣（D4）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "喬陰縣城西門");
    set("long", @LONG
這裡是喬陰縣城的西門，西門的城樓是喬陰縣城四個城門中最完整的，城牆並不甚高，但是縱深極深，從城樓這端到另一端足足有二十多丈，兩重鐵柵門，四重護城門，當初建造這裡的城樓時正是北方大山裡青邪起兵侵擾最烈的時候，因此城樓建得格外堅固。往西出城門的大路可以通往五堂鎮。
LONG
    );
    set("exits", ([
        "west" : __DIR__"highway",
        "south" : __DIR__"west_lane1",
    ]));
    set("objects", ([
        "/d/qiaoyin/npc/han_wen_suei" : 1,
        "/d/npc/garrison" : 4,
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
