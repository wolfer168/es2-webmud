/* 天蠶寶衣 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("\x1b[1;37m天蠶寶衣\x1b[m", ({ "silk cloth", "cloth" }));
    set_weight(1000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 15000);
        set("long",
            "這件寶衣乃以摻有西域雪山上特產的天蠶絲之絲線所織成之戰衣, 具有\n"
            "輕薄暖的特色, 更重要的是, 天蠶絲水火不侵, 刀槍不入, 是武林中相\n"
            "當罕見的珍物, 此衣之防護能力也因摻入天蠶絲而大增。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "con": 1,
            "armor": 4,
            "armor_vs_fire": 12,
            "armor_vs_ice": 12,
        ]));
    }
    setup();
}
