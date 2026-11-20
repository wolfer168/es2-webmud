// /d/lee/riverside_s.c
// 李家村復原版。RECONSTRUCTED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "溪邊小路");
    set("long", @LONG
溪邊小路到了村東門附近，西面可回村口大門，南北則沿著溪岸延伸。水聲在這一帶十分清楚。幾名村婦聚在溪邊，一邊浣洗衣物一邊閒話家常，笑聲不時隨著水聲飄散開來，是這一帶少見的熱鬧光景。
LONG
    );
    set("objects", ([
        "/d/lee/npc/woman" : 4
    ]));
    set("exits", ([
        "west" : __DIR__"gate_e",
        "north" : __DIR__"riverside_n1",
        "south" : __DIR__"creek",
        "southwest" : __DIR__"watermelon_n3"
    ]));
    set("fishing", 1);
    set("detail/溪水", "溪水在村東門附近稍稍變寬，水面下魚影成群，可惜浣衣的村婦多，要垂釣 (fish) 得找個清靜些的角落。");
    setup();
    replace_program(ROOM);
    set("map/area", "李家村");
}
