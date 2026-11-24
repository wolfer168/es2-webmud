// /d/lee/npc/bandit_chief.c — 野羊山大當家（軍人，鎚法；殺死他不會與其他軍人結仇）
// 李家村事件「野羊山山賊洗劫李家村」的入侵者，設計見 docs/LEE_BANDIT_RAID.md。
#include <ansi.h>

inherit "/d/lee/npc/raider";

void create()
{
    seteuid(getuid());
    set_name("西門智", ({ "hsi-men chih", "hsi-men", "chih", "bandit chief", "chief" }));
    set("title", "野羊山大當家");
    set_race("human");
    set_class("soldier");
    set_level(70);
    set("gender", "male");
    set("age", 45);
    set("long",
        "一個膀闊腰圓的大漢，渾身筋肉虯結，肩上扛著一柄比人頭還大的黑鐵槌。看起來粗枝大葉，真動起手來卻狂野凶悍，全然不在乎傷到旁人。\n");
    set_skill("powerblow", 120);
    // 擊殺者獲得戰場功勳。
    set("bounty", ([ "military service": 1000 ]));
    set_power("A");
    setup_raider();
    setup();
    carry_object("/custom/weapon/blunt/black_iron_hammer")->wield("twohanded blunt");
    carry_object("/d/lee/npc/obj/steel_armor")->wear();
    carry_object("/d/lee/npc/obj/iron_cloth")->wear();
    carry_object("/custom/armor/head/war_hat")->wear();
    carry_object("/d/lee/npc/obj/sheepskin_ring")->wear();
    carry_object("/d/lee/npc/obj/warm_jade_girdle")->wear();
    carry_object("/d/lee/npc/obj/bone_gauntlets")->wear();
}
