// /d/wutang/river_bank.c — 五堂鎮（J22）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "羿水河邊");
    set("long", @LONG
羿水河邊的一片沙灘，河水在這裡轉了個彎，流速緩了下來，水面上不時有魚兒躍出。岸邊散落著幾塊大石頭，是釣客們最喜歡的位置。往西北可以回到鯉君渡口。
LONG
    );
    set("exits", ([
        "northwest" : __DIR__"ferry_dock",
    ]));
    set("map/area", "五堂鎮");
    set("fishing", 1);
    set("detail/河水", "羿水河邊的水流在這裡緩了下來，水色青綠，水面下不時有魚影一閃而過。岸邊的大石頭被釣客坐得光滑，在這兒垂釣 (fish) 想必有所收穫。");
    setup();
    replace_program(ROOM);
}
