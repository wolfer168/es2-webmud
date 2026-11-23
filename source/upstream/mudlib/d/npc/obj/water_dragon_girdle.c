/* 蛟龍帶 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("蛟龍帶", ({ "water dragon girdle", "girdle" }));
    set_weight(300);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 1000);
        set("long",
            "一條縫製得十分精細的腰帶﹐腰帶上還繡了一條蛟龍。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "cps": 1,
            "armor": 10,
            "armor_vs_ice": 10,
        ]));
    }
    setup();
}
