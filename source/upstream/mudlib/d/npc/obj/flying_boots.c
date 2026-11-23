/* 飛天靴 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("飛天靴", ({ "flying boots", "boots" }));
    set_weight(1000);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 15000);
        set("long",
            "一雙兔毛內襯的十分高貴的鞋子﹐鞋子的外表是一層頗有韌性的很結實的蛇皮。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "defense": 15,
            "armor": 10,
        ]));
    }
    setup();
}
