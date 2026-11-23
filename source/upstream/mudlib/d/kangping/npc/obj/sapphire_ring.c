/* 藍水晶戒指 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;34m藍水晶戒指\x1b[m", ({ "sapphire ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 70000);
        set("long",
            "一枚散發出深藍色光芒的水晶戒指﹐看久了讓人有點不舒服。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "spi": 2,
            "force": -5,
        ]));
    }
    setup();
}
