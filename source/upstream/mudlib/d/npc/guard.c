// /d/npc/guard.c — 五堂鎮 NPC：護院武師（依五堂鎮設計表）。

#include <npc.h>
inherit F_FIGHTER;

void create()
{
    seteuid(getuid());
    set_name("護院武師", ({ "guard" }));
    set_race("blackteeth");
    set_class("fighter");
    set_level(5);
    set("age", 20);
    set("long", @LONG
肌肉虯結一身橫肉，看起來並不好惹的樣子。
LONG
    );
    set_power("B");
    setup();
    carry_object("/d/npc/obj/cowhide_vest")->wear();
    carry_object("/obj/area/obj/blade")->wield();
}
