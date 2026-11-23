/* 暗默珠 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("暗默珠", ({ "silance rosary", "rosary" }));
    set_weight(200);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "串");
        set("value", 10000);
        set("long",
            "一串暗黑色的珠子，給人一種平穩寧靜的感覺。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "cps": 2,
            "absorption": 5,
            "armor": 10,
        ]));
    }
    setup();
}
