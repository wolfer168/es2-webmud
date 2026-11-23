/* 黃金指環 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("黃金指環", ({ "golden ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 7000);
        set("long",
            "一枚黃澄澄的金戒指，摸起來有點溫熱的感覺。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "con": 1,
            "dex": -1,
        ]));
    }
    setup();
}
