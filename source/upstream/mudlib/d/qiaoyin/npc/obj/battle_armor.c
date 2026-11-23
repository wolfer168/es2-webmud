/* 步軍戰鎧 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("步軍戰鎧", ({ "battle armor", "armor" }));
    set_weight(12000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "套");
        set("value", 26000);
        set("long",
            "一套天朝步軍武將的制式戰甲，包括用牛皮硬化製成的各部護具，要害\n"
            "部份用鐵甲護住，又不妨礙手腳的活動，雖然沈重，但是防護力一流。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 40,
            "wittiness": 25,
        ]));
    }
    setup();
}
