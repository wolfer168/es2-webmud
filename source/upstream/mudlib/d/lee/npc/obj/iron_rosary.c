/* 鐵佛珠 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("鐵佛珠", ({ "iron rosary", "rosary" }));
    set_weight(800);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "串");
        set("value", 30000);
        set("long",
            "一串暗黑色的佛珠﹐沉重的鐵珠子上透著一股殺氣。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "cor": 1,
            "armor": 10,
        ]));
    }
    setup();
}
