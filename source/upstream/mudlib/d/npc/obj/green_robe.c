/* 青衣道袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("青衣道袍", ({ "green robe", "robe" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 4000);
        set("long",
            "一件青色的道袍 ,是小道童們最常穿的。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 1,
        ]));
    }
    setup();
}
