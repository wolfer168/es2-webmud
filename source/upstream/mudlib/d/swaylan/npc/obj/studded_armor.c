/* 鑲釘皮鎧 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("鑲釘皮鎧", ({ "studded armor", "armor" }));
    set_weight(5000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 30000);
        set("long",
            "一副用好幾層牛皮疊在一起，用釘子穿過連結而成的皮鎧甲。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "intimidate": -5,
            "armor": 25,
            "armor_vs_ice": 10,
        ]));
    }
    setup();
}
