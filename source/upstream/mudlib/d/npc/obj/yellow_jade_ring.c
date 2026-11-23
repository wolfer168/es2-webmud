// /d/npc/obj/yellow_jade_ring.c
// NEW（李家村復原版新增道具，非原始 ES2 資料，由專案成員指定數值）

#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("黃玉戒指", ({ "yellow jade ring", "jade ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 100000);
        set("long", "一枚黃玉戒指，質地溫潤厚實，戴著讓人覺得渾身踏實有力。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "con": 1,
        ]));
    }

    setup();
}
