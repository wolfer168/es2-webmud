// /d/qiaoyin/npc/waiter.c — 喬陰縣 NPC：店小二（金水客棧）（依使用者設計表，2026-10-16）。

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
    set("gender", "male");
    set("age", 22);
    set("long", @LONG
金水客棧的店小二，肩上搭著一條白毛巾，忙進忙出地招呼客人。
LONG
    );
    // 比照五堂鎮醇雨樓客棧的店小二。
    set("merchandise", ([
        "/obj/food/dumpling" : 50,
        "/obj/food/manto" : 50,
        "/obj/food/pork" : 50,
        "/d/npc/obj/roast_chicken" : 30,
    ]));
    set_power("C");
    setup();
}
