// /d/qiaoyin/bank.c — 喬陰縣（H12）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit BANK;

void create()
{
    set("short", "景隆錢莊");
    set("long", @LONG
景隆錢莊在喬陰縣的分號，店面雖然不如五堂鎮的本號氣派，但櫃臺後的夥計一樣忙著撥算盤，門口與內堂都有護院武師把守。在這裡可以存款、提款，也可以兌換銀兩，城裡的商家大多在此往來。
LONG
    );
    set("exits", ([
        "north" : __DIR__"west_street3",
    ]));
    set("objects", ([
        "/d/npc/guard" : 2,
    ]));
    set("map/area", "喬陰縣");
    setup();
}
