// /d/lee/npc/obj/tight_cloth.c
// 李家村復原版新增道具；名稱、敘述與特性改依 ES2 原始護具資料「緊身衣(Cloth)」
// （防禦能力值 5、防禦力 4）。價值、重量維持原值。

#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("緊身衣", ({ "tight cloth", "tight clothes", "cloth" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 600);
        set("long", "一件特製的衣服，可緊附著身體以方便行動跟戰鬥。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "defense": 5,
            "armor": 4,
        ]));
    }

    setup();
}
