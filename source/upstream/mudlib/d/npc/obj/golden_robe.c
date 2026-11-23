/* 金絲長袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("\x1b[1;33m金絲長袍\x1b[m", ({ "golden robe", "robe" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 15800);
        set("long",
            "一件用金絲精心縫製而成的長袍，擁有相當不錯的防禦力。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "parry": 10,
            "armor": 10,
            "armor_vs_wind": 50,
        ]));
    }
    setup();
}
