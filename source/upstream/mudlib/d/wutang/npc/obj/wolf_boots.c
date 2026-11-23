/* 狼皮靴 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("狼皮靴", ({ "wolf boots", "boots" }));
    set_weight(1000);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 25000);
        set("long",
            "一雙由狼皮製成的靴子﹐輕便耐穿而且保暖。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "parry": 2,
            "dodge": 2,
            "armor": 2,
        ]));
    }
    setup();
}
