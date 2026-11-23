/* 黃呢鐵帽 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("黃呢鐵帽", ({ "brass hat", "hat" }));
    set_weight(2000);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 3200);
        set("long",
            "一頂輕便的頭盔，邊緣綴著黃呢料子，頂上有一叢雀羽。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "wittiness": 25,
            "armor": 10,
        ]));
    }
    setup();
}
