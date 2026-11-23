/* 白玉戒指 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;37m白玉戒指\x1b[m", ({ "white ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 25000);
        set("long",
            "一枚鑲嵌著白玉的戒指。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "cps": 2,
            "armor_vs_ice": 50,
        ]));
    }
    setup();
}
