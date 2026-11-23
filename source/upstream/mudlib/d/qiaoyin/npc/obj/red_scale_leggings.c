/* 火鱗脛甲 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_LEG_EQ;

void create()
{
    set_name("火鱗脛甲", ({ "red_scale leggings", "leggings" }));
    set_weight(1000);
    setup_leg_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 10000);
        set("long",
            "一雙滿飾火紅色鱗片的脛甲，鱗片上微微透出暗紅色的光暈。相傳柳東蘆早年\n"
            "遊經祈國與練火大山邊境時，曾仗著手中玄蘇劍，用計斬殺了一隻頭生雙角、\n"
            "口吐火燄的巨蟒，之後以巨蟒皮製成幾套防具，看來這就是其中一件了。\n");
        set("wear_as", "leg_eq");
        set("apply_armor/leg_eq", ([
            "armor": 5,
            "force": 5,
            "armor_vs_fire": 15,
        ]));
    }
    setup();
}
