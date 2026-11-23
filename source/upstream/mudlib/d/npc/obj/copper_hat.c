/* 青銅道冠 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("青銅道冠", ({ "copper hat", "hat" }));
    set_weight(800);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 1000);
        set("long",
            "這是一頂青銅製的道冠﹐是道士們頭上所戴的東西。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "dodge": -1,
            "armor": 3,
        ]));
    }
    setup();
}
