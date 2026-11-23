// /d/oldpine/mist2.c — 迷霧森林（R10）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "迷霧森林");
    set("long", @LONG
霧氣濃得像化不開的牛乳，衣服沒多久就被沾得濕漉漉的。林間有一塊稍微乾燥的高地，被往來的人當成了歇腳處，地上留著熄滅的火堆和一些吃剩的乾糧碎屑。不時有人影從霧中出現又消失，分不清是旅人還是商販。往西可以回去，往南有一條被人踩出來的小徑。
LONG
    );
    set("exits", ([
        "west" : __DIR__"mist1",
        "south" : __DIR__"mist3",
    ]));
    set("objects", ([
        __DIR__"npc/seller" : 1,
        "/d/npc/man" : 1,
    ]));
    set("map/area", "迷霧森林");
    setup();
    replace_program(ROOM);
}
