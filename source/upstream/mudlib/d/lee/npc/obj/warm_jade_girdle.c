// /d/lee/npc/obj/warm_jade_girdle.c
// NEW（野羊山事件新增道具，設計見 docs/LEE_BANDIT_RAID.md）
#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("暖玉束腰", ({ "warm jade girdle", "girdle" }));
    set_weight(800);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 8000);
        set("long",
            "一條嵌著幾塊暖玉的束腰，玉質溫潤，貼在腰間隱隱透著暖意，也不知是從哪\n"
            "個富戶家裡搶來的，穿在山賊頭子身上顯得有些不倫不類。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "con": 1,
            "wittiness": 10,
        ]));
    }
    setup();
}
