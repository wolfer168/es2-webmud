/* 法胄 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("法胄", ({ "magic armor", "armor" }));
    set_weight(3000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 25000);
        set("long",
            "這是一件畫著闢邪符咒的甲冑，硬皮護肩連著保護胸口後心要害的銅鎖片。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 10,
            "magic": 10,
            "taoism of conviction": 10,
        ]));
    }
    setup();
}
