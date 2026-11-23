/* 銀彎束腰 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("\x1b[1;37m銀彎束腰\x1b[m", ({ "silver girth", "girth" }));
    set_weight(300);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 600);
        set("long",
            "一條以白色絲綢及白銀混編而成的華麗腰帶,乍看之下銀光閃閃像極滿天星斗\n"
            ",是蔚楓的貼身防具。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "wis": 1,
        ]));
    }
    setup();
}
