/* 白長袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("白長袍", ({ "white cloth", "cloth" }));
    set_weight(1000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 10000);
        set("long",
            "這是一件雪白的絲綢長袍。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "int": 2,
        ]));
    }
    setup();
}
