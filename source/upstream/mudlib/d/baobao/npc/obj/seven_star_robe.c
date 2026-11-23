/* 七星道袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("七星道袍", ({ "seven star robe", "robe" }));
    set_weight(1000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 10000);
        set("long",
            "一件由天山冰蠶所吐出的蠶絲織成的暗紅色道袍，傳聞中此袍\n"
            "不畏冰火，乃道家珍寶。繡著八卦的袍上，在右胸上更有金絲\n"
            "所繡成的七星圖案。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor_vs_ice": 15,
            "spell": 10,
            "armor": 10,
            "armor_vs_fire": 15,
        ]));
    }
    setup();
}
