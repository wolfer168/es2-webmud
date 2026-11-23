// /d/lee/npc/obj/crystal_ring.c
// 李家村復原版新增道具；名稱、顏色、敘述與特性改依 ES2 原始護具資料「水晶戒指(Crystal ring)」
// （所有者聶晟，防禦力 1、靈性 1、根骨 1）。價值、重量維持原值。

#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;37m水晶戒指\x1b[m", ({ "crystal ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 100000);
        set("long", "一枚由天然水晶雕刻而成的戒指，不斷閃耀著奪目的光芒。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor": 1,
            "spi": 1,
            "con": 1,
        ]));
    }

    setup();
}
