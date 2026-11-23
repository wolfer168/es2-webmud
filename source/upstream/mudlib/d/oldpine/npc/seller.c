// /d/oldpine/npc/seller.c — 迷霧森林 NPC：旅行小販（依老松林設計表）。

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
    set_name("旅行小販", ({ "seller" }));
    set_race("human");
    set_class("commoner");
    set_level(1);
    set("age", 40);
    set("long", @LONG
揹著大貨箱四處做買賣的小販。你可以用 list 看他賣些什麼，用 buy 購買。
LONG
    );
    set_skill("unarmed", 2);
    set_skill("dodge", 2);
    set_skill("parry", 2);
    // merchandise 的數字是庫存份數，價錢是各物品自己的 value。
    set("merchandise", ([
        "/obj/area/obj/shortsword" : 3,
        "/obj/area/obj/kris" : 3,
        "/custom/item/scroll/blank" : 300,
        "/d/npc/obj/bait" : 500,   // 魚餌（釣魚用）
    ]));
    set_power("C");
    setup();
}
