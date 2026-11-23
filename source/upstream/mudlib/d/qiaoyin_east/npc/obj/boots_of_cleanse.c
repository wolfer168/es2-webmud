/* 塵不沾 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("\x1b[1;37m塵不沾\x1b[m", ({ "boots of cleanse", "boots" }));
    set_weight(500);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 75000);
        set("long",
            "一雙用黃毛鵝羽編成的鞋子, 看起來似乎沒什麼重量。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "dodge": 30,
        ]));
    }
    setup();
}
