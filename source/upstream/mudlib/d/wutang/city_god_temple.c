// /d/wutang/city_god_temple.c — 五堂鎮（X12）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "城隍廟");
    set("long", @LONG
五堂鎮的城隍廟，是地方上的信仰中心，香火終年不斷。正殿供奉著身穿紫紅官服的城隍爺神像，兩旁站著牛頭馬面，神情威嚴。香案上擺滿了鎮民供奉的鮮花素果，裊裊的香煙中透著一股肅穆的氣氛。
LONG
    );
    set("exits", ([
        "west" : __DIR__"east_street4",
    ]));
    set("objects", ([
        __DIR__"npc/town_god" : 1,
        __DIR__"npc/old_woman" : 1,
    ]));
    set("no_fight", 1);
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
