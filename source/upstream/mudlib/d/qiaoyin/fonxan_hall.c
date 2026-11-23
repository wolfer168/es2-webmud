// /d/qiaoyin/fonxan_hall.c — 喬陰縣（T8）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "正廳");
    set("long", @LONG
這是一座清幽宅院的正廳，據說是封山派在喬陰縣的落腳之處。廳中陳設簡樸，正面牆上掛著一幅山水，畫的正是封山的景色，兩旁擺著幾張太師椅，桌上的茶還冒著熱氣。東邊的門通往一處別院。
LONG
    );
    set("exits", ([
        "east" : __DIR__"fonxan_yard",
        "southwest" : __DIR__"east_street3",
    ]));
    set("objects", ([
        "/d/qiaoyin/npc/liuh_don_lu" : 1,
        __DIR__"npc/doo_yeng" : 1,
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
