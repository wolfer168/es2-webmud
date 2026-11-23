/* 簑衣 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("簑衣", ({ "cloth" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 120);
        set("long",
            "一件很常見的簑衣, 有防雨之功用。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "halieutics": 10,
        ]));
    }
    setup();
}
