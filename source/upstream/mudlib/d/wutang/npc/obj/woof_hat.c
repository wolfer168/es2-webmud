/* 狼皮帽 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("狼皮帽", ({ "woof hat", "hat" }));
    set_weight(800);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 1000);
        set("long",
            "一頂狼皮做的帽子﹐非常的保暖﹐外型也很好看。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor": 2,
        ]));
    }
    setup();
}
