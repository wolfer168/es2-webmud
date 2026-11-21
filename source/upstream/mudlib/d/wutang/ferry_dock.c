// /d/wutang/ferry_dock.c — 五堂鎮（H20）。房間敘述照設計表原文。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "鯉君渡口");
    set("long", @LONG
這裡是來往喬陰縣和水嵐縣的主要交通要衝，在喬陰縣和水嵐縣發展的越來越具規模之後，鯉君渡也變得越來越繁榮，相傳鯉君渡這渡口的由來是在寒於氏死後靈魂化身的十三精靈之一的川鬼「濁魚」因羿水這裡山靈水秀而在這裡安定下來，由於本身所具有對於山川河水的神祕能力，使的原本急湍旋流很多的羿水成為一條穩定的河川，後人為了緬懷祂們，尊稱祂們為鯉君，更在這裡設立一個鯉君渡，讓過往的旅客能受祂們的庇佑安全渡過羿水。
LONG
    );
    set("exits", ([
        "southup" : __DIR__"ferry",
        "southeast" : __DIR__"river_bank",
    ]));
    set("objects", ([
        __DIR__"npc/fisher" : 2,
    ]));
    set("no_fight", 1);
    set("map/area", "五堂鎮");
    set("fishing", 1);
    set("detail/河水", "渡口邊的羿水清澈而平穩，木樁旁的水面下有魚群游動，船夫們說這裡的魚肥，閒著的人拿根釣竿垂釣 (fish) 倒也不會落空。");
    setup();
    replace_program(ROOM);
}
