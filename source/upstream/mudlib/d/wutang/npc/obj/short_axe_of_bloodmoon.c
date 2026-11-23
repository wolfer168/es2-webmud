/* 血月短斧 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("\x1b[1;31m血月短斧\x1b[m", ({ "short axe of bloodmoon", "axe" }));
    set_weight(7900);
    init_damage(3, 16, 120, 6, "axe");
    init_damage(3, 8, 120, 6, "secondhand axe");

    if( !clonep() ) {
        set("wield_as", ({ "axe", "secondhand axe" }));
        set("unit", "把");
        set("value", 35000);
        set("long",
            "血月短斧整體以赤鐵打造，比起血月斧來小了一點，斧刃部分呈半月型。\n");
        set("apply_weapon/axe", ([
            "attack": 5,
        ]));
        set("apply_weapon/secondhand axe", ([
            "attack": 5,
        ]));
    }
    setup();
}
