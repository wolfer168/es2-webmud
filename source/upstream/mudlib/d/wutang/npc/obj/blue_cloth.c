// /d/wutang/npc/obj/blue_cloth.c — 青布衣（Blue cloth），五堂鎮青年書生身上的衣服。
// 依設計表：防禦比一般布衣（obj/area/obj/cloth.c，防禦 1、價值 200）多 3，價值高 50%。
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("青布衣", ({ "blue cloth", "cloth" }));
    set_weight(1000);
    setup_cloth();
    if( !clonep() ) {
        set("unit", "件");
        set("value", 300);
        set("long", "一件用青色棉布縫製的長衫，樣式樸素，是讀書人常穿的衣服。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 4,
        ]));
    }
    setup();
}
