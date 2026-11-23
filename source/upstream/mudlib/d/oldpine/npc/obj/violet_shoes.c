/* 紫紗靴 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("\x1b[1;35m紫紗靴\x1b[m", ({ "violet shoes", "shoes" }));
    set_weight(500);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 15000);
        set("long",
            "一雙用紫色布料所做成的短靴,相傳擁有草上飛的功用。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 5,
            "dodge": 15,
        ]));
    }
    setup();
}
