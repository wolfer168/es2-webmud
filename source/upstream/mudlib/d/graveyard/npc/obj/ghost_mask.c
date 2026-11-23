/* 鬼面 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("鬼面", ({ "ghost mask", "mask" }));
    set_weight(800);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "個");
        set("value", 60000);
        set("long",
            "一個很不起眼的破舊面具﹐上面不僅布滿了刮痕而且還有乾了的血跡。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "attack": 25,
            "awarness": 50,
        ]));
    }
    setup();
}
