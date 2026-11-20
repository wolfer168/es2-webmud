// /d/lee/riverside_n1.c
// 李家村復原版。RECONSTRUCTED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "溪邊小路");
    set("long", @LONG
沿溪小路夾在村舍與水岸之間，北面還能隱約望見拱橋方向。南北兩端都順著溪流延伸。一名村婦蹲在溪邊，手裡捧著木盆，正仔細地搓洗衣物，木盆碰撞石塊發出輕微的聲響，與潺潺水聲交織在一起。
LONG
    );
    set("objects", ([
        "/d/lee/npc/woman" : 1
    ]));
    set("exits", ([
        "north" : __DIR__"riverside_n2",
        "south" : __DIR__"riverside_s"
    ]));
    set("fishing", 1);
    set("detail/溪水", "溪水在這段水岸邊打著淺淺的旋，岸邊的暗影裡有魚影一閃而過，垂釣 (fish) 或許能有收穫。");
    setup();
    replace_program(ROOM);
    set("map/area", "李家村");
}
