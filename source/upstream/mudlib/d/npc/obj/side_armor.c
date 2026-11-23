/* 肩鎧 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("肩鎧", ({ "side armor", "armor" }));
    set_weight(2000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 1000);
        set("long",
            "這是一副精鐵打造的肩鎧，天朝內地並不常見，是屬於南方光右族\n"
            "所用的護具，肩鎧用一條皮帶穿過一個護殼縛在肩測，如果力氣不\n"
            "夠大動作會受到妨礙。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 4,
        ]));
    }
    setup();
}
