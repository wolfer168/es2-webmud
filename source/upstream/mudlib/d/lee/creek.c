// /d/lee/creek.c
// 李家村復原版。RECONSTRUCTED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "小溪");
    set("long", @LONG
清淺溪水貼著李家村東側緩緩流過，岸邊散著大小不一的石塊。西面靠近瓜田，北面則可沿溪邊小路返回村東門。溪水清澈見底，偶爾能看見幾尾小魚悠游其中，石塊上還留著村婦浣衣時留下的濕痕。
LONG
    );
    set("exits", ([
        "north" : __DIR__"riverside_s",
        "west" : __DIR__"watermelon_n3"
    ]));
    set("fishing", 1);
    set("detail/溪水", "清淺的溪水貼著石塊流過，幾尾小魚在水底的卵石間悠游，坐在溪邊垂釣 (fish) 倒也愜意。");
    setup();
    replace_program(ROOM);
    set("map/area", "李家村");
}
