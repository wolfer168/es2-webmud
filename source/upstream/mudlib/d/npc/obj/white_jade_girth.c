/* 流雲清玉帶 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("\x1b[1;37m流雲清玉帶\x1b[m", ({ "white-jade girth", "girth" }));
    set_weight(800);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 30000);
        set("long",
            "這是一條用上好的白玉做成的腰帶．手工精緻，樣式高雅﹐讓你愛不釋手。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "dodge": 5,
            "force": 5,
        ]));
    }
    setup();
}
