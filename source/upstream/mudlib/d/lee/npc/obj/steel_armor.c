// 特性依 ES2 原始護具資料「精鋼戰甲(Steel armor)」（所有者米沛等）。
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("精鋼戰甲", ({ "steel armor", "steel", "armor" }));
    set_weight(12000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 60000);
        set("long",
            "一件金鏤內襯，外披精鋼鐵環的鍊子甲，乃是專為沙場戰將所打造\n"
            "的上品戰甲，有著強大的防護力。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "cor": 2,
            "damage": 5,
            "armor": 25,
        ]));
    }

    setup();
}
