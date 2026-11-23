// /d/qiaoyin/north_street1.c — 喬陰縣（L4）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "北大街");
    set("long", @LONG
北大街的北段，離北門已經不遠，西邊開著一間雜貨舖。由於北門外不太平靜，這一帶的行人比往年少了許多，偶爾才有幾個挑著擔子的鄉民匆匆走過，連路邊的攤販也早早收了攤。
LONG
    );
    set("exits", ([
        "north" : __DIR__"ngate",
        "west" : __DIR__"grocery",
        "south" : __DIR__"north_street2",
    ]));
    set("objects", ([
        "/d/npc/man" : 1,
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
