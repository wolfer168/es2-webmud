#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("精鋼戰靴", ({ "steel boots", "steel", "boots" }));
    set_weight(3000);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 5000);
        set("long", "一雙精鋼打造的靴子，接縫幾乎沒有空隙，可以有效保護你的足部。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 5,
            "defense": -5,
        ]));
    }

    setup();
}
