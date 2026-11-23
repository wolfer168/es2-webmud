/* 白色長衫 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("白色長衫", ({ "white dress", "dress" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 4000);
        set("long",
            "一件白色裐布織成的長擺衣衫，通常是書生、文士們所穿著。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "dodge": -5,
            "armor": 2,
        ]));
    }
    setup();
}
