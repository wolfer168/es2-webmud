// /d/lee/npc/bandit_third.c — 野羊山三當家（武者，粗野拳法）
// 李家村事件「野羊山山賊洗劫李家村」的入侵者，設計見 docs/LEE_BANDIT_RAID.md。
#include <ansi.h>

inherit "/d/lee/npc/raider";

void create()
{
    seteuid(getuid());
    set_name("野羊山三當家", ({ "bandit third", "third" }));
    set_race("human");
    set_class("fighter");
    set_level(70);
    set("gender", "male");
    set("age", 35);
    set("long",
        "一個壯得像頭牛的漢子，一身蠻力使不完，拳腳功夫沒拜過師，全是自己瞎琢磨出來的野路子，一向以力服人。\n");
    set_skill("rough-fist", 150);
    map_skill("unarmed", "rough-fist");
    // 擊殺者獲得戰場功勳。
    set("bounty", ([ "military service": 600 ]));
    set_power("B");
    setup_raider();
    setup();
    carry_object("/custom/armor/finger/finger_ring")->wear();
    carry_object("/d/lee/npc/obj/heart_plate")->wear();
    carry_object("/custom/armor/waist/blessed_jade")->wear();
    carry_object("/d/lee/npc/obj/sheepskin_vest")->wear();
}
