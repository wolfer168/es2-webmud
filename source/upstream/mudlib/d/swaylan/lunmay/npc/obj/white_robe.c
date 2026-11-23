/* 梅花白襖 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("\x1b[1;37m梅花白襖\x1b[m", ({ "white robe", "robe" }));
    set_weight(1000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 19000);
        set("long",
            "這是一件白色長袍﹒上面用黃金絲繡著冷梅莊的標誌，長袍本身的絲\n"
            "線是由西天大山上特產的冰蠶所吐的絲所製成。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 10,
            "armor_vs_ice": 15,
        ]));
    }
    setup();
}
