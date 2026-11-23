/* 純白道袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("純白道袍", ({ "white robe", "robe" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 1000);
        set("long",
            "一件純白色的寬袖道袍﹐顏色十分醒目。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 2,
        ]));
    }
    setup();
}
