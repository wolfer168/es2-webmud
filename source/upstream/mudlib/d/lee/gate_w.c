// /d/lee/gate_w.c
// 李家村復原版。RECONSTRUCTED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "村口大門");
    set("long", @LONG
李家村西面的木製大門橫跨道路，門外道路通向村外，門內則接上筆直石子路。守衛偶爾在門旁巡看來往行人。門邊立著一根老舊的拴馬樁，樁身被繩索磨出深深的溝痕，看得出往來的行商經常在此歇腳餵馬。兩名守衛肩靠著門柱閒聊村里近日的瑣事，見有人靠近才收起話頭，恢復巡看的神色。
LONG
    );
    set("objects", ([
        "/d/lee/npc/guard" : 2
    ]));
    set("exits", ([
        "east" : __DIR__"wroad1",
        "west" : __DIR__"wroad5"
    ]));
    setup();
    replace_program(ROOM);
    set("map/area", "李家村");
}
