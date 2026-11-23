/* 銀霜鎧 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("\x1b[1;37m銀霜鎧\x1b[m", ({ "silver platemail of frost", "platemail" }));
    set_weight(12000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 250000);
        set("long",
            "這是一件銀白色的鎧甲，是梅影風特地託奐族人打造的﹒奐族工匠打\n"
            "造的武器乃是天朝武林人士夢寐以求的寶物，不但堅固耐用，而且輕\n"
            "便﹒梅影風這件鎧甲，尤為上品。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "intimidate": 25,
            "armor": 35,
            "armor_vs_ice": 50,
        ]));
    }
    setup();
}
