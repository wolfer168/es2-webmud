// /d/lee/npc/rough_bandit.c — 野羊山捍匪（武者，粗野刀法，左右手各一刀）
// 李家村事件「野羊山山賊洗劫李家村」的入侵者，設計見 docs/LEE_BANDIT_RAID.md。
#include <ansi.h>

inherit "/d/lee/npc/raider";

void create()
{
    seteuid(getuid());
    set_name("野羊山捍匪", ({ "rough bandit", "bandit" }));
    set_race("human");
    set_class("fighter");
    set_level(50);
    set("gender", "male");
    set("age", 31);
    set("long",
        "一個身上帶著幾道舊疤的悍匪，一手提羊頭刀、一手握羊角刀，眼神兇惡，出手毫不留情。\n");
    set_skill("rough-blade", 100);
    map_skill("blade", "rough-blade");
    map_skill("secondhand blade", "rough-blade");
    map_skill("parry", "rough-blade");
    // 擊殺者獲得戰場功勳。
    set("bounty", ([ "military service": 100 ]));
    set_power("A");
    setup_raider();
    setup();
    carry_object("/d/lee/npc/obj/goat_blade")->wield("blade");
    carry_object("/d/lee/npc/obj/horn_blade")->wield("secondhand blade");
}
