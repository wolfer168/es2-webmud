/* 軟櫬甲 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("軟櫬甲", ({ "padded armor", "armor" }));
    set_weight(3000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 9500);
        set("long",
            "這是一種輕型的甲冑，在棉花中夾縫著一片片的鐵片，防護力中等，也\n"
            "不會妨礙行動，不過大熱天穿起來非常悶熱。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor_vs_ice": 20,
            "armor": 14,
        ]));
    }
    setup();
}
