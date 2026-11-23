/* 黑布鞋 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("黑布鞋", ({ "black boots", "boots" }));
    set_weight(500);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 1000);
        set("long",
            "修道人最常穿的鞋子，堅固耐用。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "dodge": 1,
            "armor": 1,
        ]));
    }
    setup();
}
