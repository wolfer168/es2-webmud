/* 星雲腿護 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_LEG_EQ;

void create()
{
    set_name("星雲腿護", ({ "star_studded legs", "legs" }));
    set_weight(1000);
    setup_leg_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 5000);
        set("long",
            "一套釉黃色腿護, 上面溶配了許多星星, 配裝於腿上, 頗具防護之效.\n");
        set("wear_as", "leg_eq");
        set("apply_armor/leg_eq", ([
            "armor": 5,
            "armor_vs_fire": 50,
            "armor_vs_lightning": 50,
        ]));
    }
    setup();
}
