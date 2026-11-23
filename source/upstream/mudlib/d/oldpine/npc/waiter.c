// /d/oldpine/npc/waiter.c — 迷霧森林 NPC：店小二（依老松林設計表）。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;


void init()
{
    ::init();
    add_action("do_vendor_list", "list");
}

void create()
{
    seteuid(getuid());
    set_name("店小二", ({ "waiter" }));
    set_race("human");
    set_class("commoner");
    set_level(1);
    set("age", 25);
    set("long", @LONG
來往的客人雖不多，總是笑臉迎人、手腳還算利索。你可以用 list 看可以點什麼，用 buy 跟店小二點菜。
LONG
    );
    set_skill("unarmed", 2);
    set_skill("dodge", 2);
    set_skill("parry", 2);
    // merchandise 的數字是庫存份數，價錢是各物品自己的 value。
    set("merchandise", ([
        "/d/npc/obj/waterskin" : 10,
        "/obj/food/manto" : 50,
        "/d/oldpine/npc/obj/venison" : 50,
    ]));
    set_power("C");
    setup();
}
