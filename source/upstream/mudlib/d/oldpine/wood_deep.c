// /d/oldpine/wood_deep.c — 迷霧森林（T22）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "樹林深處");
    set("long", @LONG
迷霧森林的最深處，幾棵需要數人合抱的古松挺立在霧中，樹幹上滿是樹洞，松果落了一地。松鼠們在枝頭間跳來跳去，一點也不怕人，偶爾還會抱著松果好奇地打量你。四周靜謐得出奇，彷彿與外面的世界完全隔絕。往北是唯一的出路。
LONG
    );
    set("exits", ([
        "north" : __DIR__"wood4",
    ]));
    set("objects", ([
        "/d/npc/squirrel" : 4,
    ]));
    set("map/area", "迷霧森林");
    setup();
    replace_program(ROOM);
}
