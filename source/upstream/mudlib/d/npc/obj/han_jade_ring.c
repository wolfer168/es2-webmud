/* 漢玉戒指 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;32m漢玉戒指\x1b[m", ({ "jade ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 40000);
        set("long",
            "這枚戒指鑲著一粒質地相當細緻的漢玉﹐看來價值不菲。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "force": 5,
            "armor": 5,
            "defense": 30,
        ]));
    }
    setup();
}
