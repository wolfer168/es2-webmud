// /d/oldpine/npc/injured_traveller.c — 老松林 NPC：受傷的旅客（依老松林設計表）。

#include <npc.h>

inherit F_VILLAGER;


void create()
{
    seteuid(getuid());
    set_name("受傷的旅客", ({ "injured traveller", "traveller" }));
    set_race("human");
    set_class("commoner");
    set_level(1);
    set("age", 35);
    set("long", @LONG
看起來傷勢頗為嚴重，若不及時醫治恐危及性命。
LONG
    );
    set_skill("unarmed", 2);
    set_skill("dodge", 2);
    set_skill("parry", 2);
    set_power("C");
    setup();
    carry_object("/d/npc/obj/dragon_pill");
}
