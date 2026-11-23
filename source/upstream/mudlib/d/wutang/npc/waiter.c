// /d/wutang/npc/waiter.c — 五堂鎮 NPC：店小二（依五堂鎮設計表）。

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
    set("age", 35);
    set("long", @LONG
忙進忙出的店小二，來來去去招呼客人。你可以用 list 看可以點什麼菜，用 buy 跟店小二點菜。
LONG
    );
    set_skill("unarmed", 2);
    set_skill("dodge", 2);
    set_skill("parry", 2);
    // merchandise 的數字是庫存份數，價錢是各物品自己的 value。
    set("merchandise", ([
        "/obj/food/dumpling" : 50,
        "/obj/food/manto" : 50,
        "/obj/food/pork" : 30,
        "/d/npc/obj/roast_chicken" : 30,
    ]));
    set_power("C");
    setup();
}
