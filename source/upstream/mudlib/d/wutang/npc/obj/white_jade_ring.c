/* 寒玉戒指 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("寒玉戒指", ({ "white ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 60000);
        set("long",
            "一枚鑲有上等白玉的金戒指。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "con": -1,
            "armor": 1,
            "int": 1,
        ]));
    }
    setup();
}
