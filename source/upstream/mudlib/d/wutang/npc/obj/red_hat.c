/* 鮮紅道冠 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("鮮紅道冠", ({ "red hat", "hat" }));
    set_weight(300);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 1000);
        set("long",
            "一頂鮮紅色的道冠，中間繡著一幅太極。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "taoism-fire": 8,
            "armor": 1,
        ]));
    }
    setup();
}
