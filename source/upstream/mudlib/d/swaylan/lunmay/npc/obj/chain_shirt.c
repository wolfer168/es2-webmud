/* 鎖鏈背心 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("鎖鏈背心", ({ "chain shirt", "shirt" }));
    set_weight(8000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 30000);
        set("long",
            "一件用許多細小的金屬圈連成的鎖鏈背心，重量不算太重，也能提供不錯\n"
            "的防禦力。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "dex": -1,
            "armor": 27,
        ]));
    }
    setup();
}
