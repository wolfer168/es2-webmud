/* 素虹軟甲 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("\x1b[1;37m素虹軟甲\x1b[m", ({ "white rainbow armor", "armor" }));
    set_weight(3000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 75000);
        set("long",
            "這件素虹軟甲是雪吟莊大弟子褚商魂的傳家之寶，用練火大山的虹蛾繭\n"
            "織成，刀劍難傷，而且質輕柔軟，防火效果奇佳。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "attack": 10,
            "armor": 25,
            "armor_vs_fire": 50,
        ]));
    }
    setup();
}
