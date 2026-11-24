// /d/lee/wroad5.c — 上山小路（李家村事件「野羊山山賊洗劫李家村」，設計見 docs/LEE_BANDIT_RAID.md）。
// NEW（新增房間，非原始 ES2 資料）。村口大門以西，野羊山探子躲在暗處等人接頭。

inherit ROOM;

void create()
{
    set("short", "上山小路");
    set("long", @LONG
離開李家村的木門﹐小路沿著山腳彎進林子裡﹐村口一帶的石徑還算平整乾淨﹐再往前走﹐路面便漸漸爬滿野草﹐腳印也稀了。道旁的灌木叢密得不見底﹐枝葉間偶爾傳來細碎的聲響﹐教人總覺得暗處有雙眼睛正盯著自己。
LONG
    );
    set("objects", ([
        "/d/lee/npc/bandit_scout" : 1
    ]));
    set("exits", ([
        "east" : __DIR__"gate_w"
    ]));
    setup();
    replace_program(ROOM);
    set("map/area", "李家村");
}
