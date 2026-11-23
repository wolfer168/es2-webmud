// /d/lee/npc/obj/hemp_boots.c
// NEW（李家村復原版新增道具，非原始 ES2 資料，由專案成員指定數值）
// 以 obj/area/obj/leather_boot.c（皮短靴）為基礎。防禦值(armor)已經是系統最低的
// 有效整數(1)，無法再降，經確認後維持 armor=1，改用降低重量與售價來表現
// 「較廉價、較單薄」的定位。

#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("麻布鞋", ({ "hemp boots", "hemp shoes", "boots" }));
    set_weight(600);            // 皮短靴 1000，麻布材質較輕
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("long", "一雙用麻布縫製的鞋子，樸素耐磨，價格低廉。\n");
        set("value", 100);      // 皮短靴 400，材質較差、售價較低
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor" : 1
        ]));
    }

    setup();
}
