/* 牛皮背心 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("牛皮背心", ({ "leather vest", "vest" }));
    set_weight(4000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 15000);
        set("long",
            "用牛皮縫製的短背心，方便穿戴者的活動。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 7,
        ]));
    }
    setup();
}
