// /d/lee/npc/obj/leather_boots.c
// NEW（李家村復原版新增道具，非原始 ES2 資料，由專案成員指定數值）
// 屬性與 obj/area/obj/leather_boot.c（皮短靴）完全一致，僅名稱不同。

#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("皮靴", ({ "leather boots", "boots" }));
    set_weight(1000);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("long", "這是一雙皮製的短靴，看起來有些舊了。\n");
        set("value", 400);
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 1,
        ]));
    }

    setup();
}
