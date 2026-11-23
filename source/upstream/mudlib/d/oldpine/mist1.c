// /d/oldpine/mist1.c — 迷霧森林（P10）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "迷霧森林");
    set("long", @LONG
白茫茫的霧氣在樹林間緩緩流動，十步以外的景物便模糊不清，只剩下一團團灰色的樹影。腳下是濕滑的落葉和腐土，空氣中飄著草藥的苦香，路旁偶爾能看見採藥人遺落的竹簍和斷掉的藥鋤。森林雖然深不可測，往來的人倒也不算少。往西可以走出森林，往東霧氣更加濃重。
LONG
    );
    set("exits", ([
        "west" : __DIR__"mist_entrance",
        "east" : __DIR__"mist2",
    ]));
    set("objects", ([
        "/d/oldpine/npc/traveller" : 2,
    ]));
    set("map/area", "迷霧森林");
    setup();
    replace_program(ROOM);
}
