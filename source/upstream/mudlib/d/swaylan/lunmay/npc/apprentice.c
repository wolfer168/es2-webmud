// /d/swaylan/lunmay/npc/apprentice.c — 五堂鎮 NPC：冷梅莊二代弟子（依五堂鎮設計表）。

#include <npc.h>
inherit F_FIGHTER;

void create()
{
    seteuid(getuid());
    set_name("冷梅莊二代弟子", ({ "apprentice" }));
    set_race("human");
    set_class("fighter");
    set_level(25);
    set("age", 20);
    set("long", @LONG
冷梅莊弟子，在劍法、內功上已經有相當火侯。
LONG
    );
    set_skill("unarmed", 50);
    set_skill("dodge", 50);
    set_skill("parry", 50);
    set("custom_faction", "fighter.lunmay");   // 門派記號（docs/CUSTOM_NPC_SKILL.md）
    set_power("B");
    setup();
}
