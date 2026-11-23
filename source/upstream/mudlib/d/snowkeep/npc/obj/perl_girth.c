/* 鑲珠束腰 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("鑲珠束腰", ({ "perl girth", "girth" }));
    set_weight(800);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 90000);
        set("long",
            "一條鑲著許多珍珠的束腰，裡面是堅厚的皮革。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "attack": 15,
            "armor": 5,
        ]));
    }
    setup();
}
