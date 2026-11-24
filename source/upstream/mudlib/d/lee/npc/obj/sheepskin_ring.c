// /d/lee/npc/obj/sheepskin_ring.c
// NEW（野羊山事件新增道具，設計見 docs/LEE_BANDIT_RAID.md）
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("羊皮脂環", ({ "sheepskin ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 3000);
        set("long",
            "一枚用羊皮裹著油脂搓成的粗環，戴在指上滑膩膩的，帶著一股淡淡的羊騷味，\n"
            "山寨裡的大當家卻戴得挺得意，說是能壯膽氣。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "wittiness": -10,
            "intimidate": 15,
            "damage": 5,
            "dex": 2,
        ]));
    }
    setup();
}
