// /d/lee/npc/obj/bone_gauntlets.c
// NEW（野羊山事件新增道具，設計見 docs/LEE_BANDIT_RAID.md）
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("羊骨護手", ({ "bone gauntlets", "gauntlets" }));
    set_weight(900);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 3500);
        set("long",
            "用羊腿骨削成片、再以皮繩一圈圈綁在小臂上的護手，敲上去喀喀作響，看來\n"
            "粗陋，卻意外地結實，打起拳腳來也更添分量。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "str": 1,
            "powerblow": 10,
        ]));
    }
    setup();
}
