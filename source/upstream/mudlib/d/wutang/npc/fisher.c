// /d/wutang/npc/fisher.c — 五堂鎮 NPC：釣客（依五堂鎮設計表）。

#include <npc.h>
inherit F_VILLAGER;

void create()
{
    seteuid(getuid());
    set_name("釣客", ({ "fisher" }));
    set_race("human");
    set_class("commoner");
    set_level(1);
    set("age", 30);
    set("long", @LONG
拿根釣竿悠哉的垂釣中。
LONG
    );
    set_skill("unarmed", 2);
    set_skill("dodge", 2);
    set_skill("parry", 2);
    set_power("C");
    setup();
    carry_object("/d/wutang/npc/obj/bamboo_fishing_rod")->wield();
}
