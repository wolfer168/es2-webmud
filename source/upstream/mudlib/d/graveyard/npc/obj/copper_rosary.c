/* 黃銅佛珠 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("黃銅佛珠", ({ "copper rosary", "rosary" }));
    set_weight(200);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "串");
        set("value", 2000);
        set("long",
            "一串土色的巨大佛珠﹐表面隱隱透著渡化之氣。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "str": 3,
        ]));
    }
    setup();
}
