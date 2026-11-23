/* 金剛念珠 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("金剛念珠", ({ "psakaml" }));
    set_weight(800);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "串");
        set("value", 25000);
        set("long",
            "一串深黑色金屬所鑄的念珠。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "wittiness": 50,
        ]));
    }
    setup();
}
