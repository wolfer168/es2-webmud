/* 紫紗逍遙巾 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("紫紗逍遙巾", ({ "headgear" }));
    set_weight(300);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 5000);
        set("long",
            "一條深紫色的頭巾，戴起來頗有書捲氣。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "wis": 1,
            "armor_vs_lightning": 50,
            "mysticism": 5,
        ]));
    }
    setup();
}
