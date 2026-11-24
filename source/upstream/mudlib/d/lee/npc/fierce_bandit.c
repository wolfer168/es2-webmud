// /d/lee/npc/fierce_bandit.c — 野羊山山賊（武者，粗野刀法）
// 李家村事件「野羊山山賊洗劫李家村」的入侵者，設計見 docs/LEE_BANDIT_RAID.md。
#include <ansi.h>

inherit "/d/lee/npc/raider";

void create()
{
    seteuid(getuid());
    set_name("野羊山山賊", ({ "fierce bandit", "bandit" }));
    set_race("human");
    set_class("fighter");
    set_level(40);
    set("gender", "male");
    set("age", 22);
    set("long",
        "一個滿臉橫肉的山賊，手裡提著一把羊頭刀，走起路來東張西望，一看見有人就兩眼放光。\n");
    set_skill("rough-blade", 70);
    map_skill("blade", "rough-blade");
    map_skill("parry", "rough-blade");
    // 擊殺者獲得戰場功勳。
    set("bounty", ([ "military service": 80 ]));
    set_power("B");
    setup_raider();
    setup();
    carry_object("/d/lee/npc/obj/goat_blade")->wield("blade");
}
