/* 青蟒靴 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("\x1b[0;32m青蟒靴\x1b[m", ({ "snakeskin boots", "boots" }));
    set_weight(1000);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 5000);
        set("long",
            "一雙用青色大蟒的皮縫製而成的靴子。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 5,
            "awarness": 25,
        ]));
    }
    setup();
}
