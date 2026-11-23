/* 怒龍錦冑 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("\x1b[1;31m怒龍錦冑\x1b[m", ({ "dragon armor", "armor" }));
    set_weight(5000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 100000);
        set("long",
            "這是一件武林中的至寶﹐據說是由練火大山的幻黑龍皮所製成\n"
            "的寶甲﹐不但尋常刀槍難以透入﹐也能防火燄冰霜的侵害﹐最\n"
            "重要的是質地輕軟﹐絲毫不妨礙行動。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 45,
            "armor_vs_fire": 40,
            "armor_vs_ice": 40,
        ]));
    }
    setup();
}
