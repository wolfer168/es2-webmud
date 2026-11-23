// /d/qiaoyin/west_street2.c — 喬陰縣（F10）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "西大街");
    set("long", @LONG
西大街上人來人往，路邊擺著幾個賣菜賣果子的攤子，攤販們扯著嗓子招攬生意，偶爾還有官府的差役穿過人群。地上散落著菜葉和果皮，幾隻雞在攤子底下啄食，熱鬧中帶著幾分雜亂。
LONG
    );
    set("exits", ([
        "west" : __DIR__"west_street1",
        "east" : __DIR__"west_street3",
    ]));
    set("objects", ([
        "/d/qiaoyin/npc/chaxigol" : 1,
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
