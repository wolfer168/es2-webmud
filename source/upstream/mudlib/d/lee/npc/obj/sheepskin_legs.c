// /d/lee/npc/obj/sheepskin_legs.c
// NEW（野羊山事件新增道具，設計見 docs/LEE_BANDIT_RAID.md）
#include <ansi.h>
#include <armor.h>

inherit F_LEG_EQ;

void create()
{
    set_name("羊皮綁腿", ({ "sheepskin legs", "legs" }));
    set_weight(700);
    setup_leg_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 1200);
        set("long",
            "用羊皮條纏在小腿上的綁腿，一圈圈纏得扎扎實實，走起路來帶著風，山裡的\n"
            "好漢都愛這麼穿。\n");
        set("wear_as", "leg_eq");
        set("apply_armor/leg_eq", ([
            "defense": 10,
            "armor": 10,
        ]));
    }
    setup();
}
