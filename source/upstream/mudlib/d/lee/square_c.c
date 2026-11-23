// /d/lee/square_c.c
// 李家村復原版。RECONSTRUCTED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "廣場中央");
    set("long", @LONG
這裡是李家村最容易聚集人群的中央廣場，四周道路交錯。孩童常在空地追逐，村民也會停下交換消息或談論村中近事。廣場中央立著一口老水井，井欄被繩索磨出一道道深痕，是全村人取水的地方。井邊常有婦人打水閒聊，孩童們則繞著井欄追逐嬉戲，笑鬧聲響徹整個廣場。
LONG
    );
    set("objects", ([
        "/d/lee/npc/child" : 3,
        "/d/obj/well" : 1
    ]));
    set("exits", ([
        "west" : __DIR__"square_s",
        "north" : __DIR__"square_e",
        "south" : __DIR__"street1"
    ]));
    setup();
    replace_program(ROOM);
    set("map/area", "李家村");
}
