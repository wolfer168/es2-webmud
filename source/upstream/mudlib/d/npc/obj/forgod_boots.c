/* 封神靴 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("\x1b[1;33m封神靴\x1b[m", ({ "forgod boots", "boots" }));
    set_weight(2000);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 75000);
        set("long",
            "這是一雙以黃金為絲的靴子﹐笨重但防禦力高。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "parry": 5,
            "armor": 20,
        ]));
    }
    setup();
}
