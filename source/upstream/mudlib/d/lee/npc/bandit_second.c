// /d/lee/npc/bandit_second.c — 野羊山二當家（武者，迅雷斧法雙斧）
// 李家村事件「野羊山山賊洗劫李家村」的入侵者，設計見 docs/LEE_BANDIT_RAID.md。
#include <ansi.h>

inherit "/d/lee/npc/raider";

void create()
{
    seteuid(getuid());
    set_name("歐陽建", ({ "ou-yang chien", "ou-yang", "chien", "bandit second", "second" }));
    set("title", "野羊山二當家");
    set_race("human");
    set_class("fighter");
    set_level(70);
    set("gender", "male");
    set("age", 32);
    set("long",
        "一個眼珠滴溜溜亂轉的瘦高漢子，雙手各提一柄黑石斧，滿臉精明相，可是三句話不離「幹完這票就衣錦還鄉」，一聽就知道腦袋裡裝的全是白日夢。\n");
    set_skill("soonlight axe", 150);
    map_skill("axe", "soonlight axe");
    map_skill("secondhand axe", "soonlight axe");
    // 擊殺者獲得戰場功勳。
    set("bounty", ([ "military service": 800 ]));
    set_power("B");
    setup_raider();
    setup();
    carry_object("/d/lee/npc/obj/black_stone_axe")->wield("axe");
    carry_object("/d/lee/npc/obj/black_stone_axe")->wield("secondhand axe");
    carry_object("/custom/armor/waist/golden_jade_belt")->wear();
    carry_object("/d/lee/npc/obj/iron_rosary")->wear();
}
