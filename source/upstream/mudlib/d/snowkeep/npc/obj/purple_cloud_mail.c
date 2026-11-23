/* 紫雲戰甲 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("\x1b[1;36m紫雲戰甲\x1b[m", ({ "purple-cloud mail", "mail" }));
    set_weight(12000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 10000);
        set("long",
            "一副看來非常神氣的鎧甲, 在整副鎧甲上都雕滿著紫色的祥雲, 令人\n"
            "感到非常的祥和, 簡直一點都不像是副作戰用的鎧甲.\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 20,
            "cps": 2,
        ]));
    }
    setup();
}
