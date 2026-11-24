// /d/lee/npc/bandit_fourth.c — 野羊山四當家（武者，粗野刀法雙握大刀）
// 李家村事件「野羊山山賊洗劫李家村」的入侵者，設計見 docs/LEE_BANDIT_RAID.md。
#include <ansi.h>

inherit "/d/lee/npc/raider";

void create()
{
    seteuid(getuid());
    set_name("野羊山四當家", ({ "bandit fourth", "fourth" }));
    set_race("human");
    set_class("fighter");
    set_level(70);
    set("gender", "male");
    set("age", 44);
    set("long",
        "一個滿臉虯髯的大漢，雙手握著一柄慘白的大砍刀，架勢倒像模像樣。據說他偷看過虎刀門練功，可惜學的只是皮毛，真使起來畫虎不成反類犬。\n");
    set_skill("rough-blade", 150);
    map_skill("twohanded blade", "rough-blade");
    map_skill("blade", "rough-blade");
    map_skill("parry", "rough-blade");
    // 擊殺者獲得戰場功勳。
    set("bounty", ([ "military service": 500 ]));
    set_power("B");
    setup_raider();
    setup();
    carry_object("/d/lee/npc/obj/bone_blade")->wield("twohanded blade");
    carry_object("/d/lee/npc/obj/sheepskin_legs")->wear();
    carry_object("/d/lee/npc/obj/straw_boots")->wear();
    carry_object("/d/lee/npc/obj/cowhide_vest")->wear();
}
