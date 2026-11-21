// /d/lee/riverside_n2.c
// 李家村復原版。RECONSTRUCTED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "溪邊小路");
    set("long", @LONG
小路沿著溪岸南北延伸，腳下散布著細碎石子。溪水貼著村東流過，附近草木因水氣而顯得格外茂盛。幾株垂柳沿岸而生，枝條輕拂水面，蕩起一圈圈細小的漣漪，替這段路添了幾分靜謐的氣氛。
LONG
    );
    set("exits", ([
        "south" : __DIR__"riverside_n1"
    ]));
    set("fishing", 1);
    set("detail/溪水", "垂柳的枝條拂著水面，柳蔭下的溪水特別清涼，魚兒喜歡聚在這兒，垂釣 (fish) 想必有魚上鉤。");
    setup();
    replace_program(ROOM);
    set("map/area", "李家村");
}
