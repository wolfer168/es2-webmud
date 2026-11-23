/* 火鱗胸鎧 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("火鱗胸鎧", ({ "red_scale plate", "plate" }));
    set_weight(5000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 50000);
        set("long",
            "一件滿飾火紅色鱗片的鎧甲，鱗片上微微透出暗紅色的光暈。相傳柳東蘆早年\n"
            "遊經祈國與練火大山邊境時，曾仗著手中玄蘇劍，用計斬殺了一隻頭生雙角、\n"
            "口吐火燄的巨蟒，之後以巨蟒皮製成幾套防具，看來這就是其中一件了。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 35,
            "twohanded sword": 10,
            "armor_vs_fire": 50,
            "armor_vs_lightning": 100,
        ]));
    }
    setup();
}
