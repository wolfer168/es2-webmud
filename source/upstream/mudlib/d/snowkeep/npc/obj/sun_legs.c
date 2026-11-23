/* 烈陽護膝 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_LEG_EQ;

void create()
{
    set_name("烈陽護膝", ({ "sun legs", "legs" }));
    set_weight(600);
    setup_leg_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 5000);
        set("long",
            "一套具有護膝功用的防具, 由於這套護膝是金黃色的, 看起來特別耀眼.\n");
        set("wear_as", "leg_eq");
        set("apply_armor/leg_eq", ([
            "cor": 1,
            "armor": 3,
        ]));
    }
    setup();
}
