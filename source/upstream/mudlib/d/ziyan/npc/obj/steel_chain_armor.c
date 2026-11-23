/* 鋼戰甲 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("鋼戰甲", ({ "steel armor", "armor" }));
    set_weight(8000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 45000);
        set("long",
            "一件外披精鋼鐵環的鍊子甲，有著強大的防護力。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "cor": 1,
            "armor": 20,
        ]));
    }
    setup();
}
