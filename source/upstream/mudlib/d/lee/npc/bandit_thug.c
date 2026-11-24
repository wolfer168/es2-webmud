// /d/lee/npc/bandit_thug.c — 野羊山毛賊（武者，粗野刀法）
// 李家村事件「野羊山山賊洗劫李家村」的入侵者，設計見 docs/LEE_BANDIT_RAID.md。
#include <ansi.h>

inherit "/d/lee/npc/raider";

void create()
{
    seteuid(getuid());
    set_name("野羊山毛賊", ({ "bandit thug", "bandit" }));
    set_race("human");
    set_class("fighter");
    set_level(40);
    set("gender", "male");
    set("age", 18);
    set("long",
        "一個年紀輕輕的毛賊，手裡的羊頭刀握得比誰都緊，一副生怕被人看輕的模樣。\n");
    set_skill("rough-blade", 50);
    map_skill("blade", "rough-blade");
    map_skill("parry", "rough-blade");
    // 擊殺者獲得戰場功勳。
    set("bounty", ([ "military service": 50 ]));
    set_power("B");
    setup_raider();
    setup();
    carry_object("/d/lee/npc/obj/goat_blade")->wield("blade");
}
