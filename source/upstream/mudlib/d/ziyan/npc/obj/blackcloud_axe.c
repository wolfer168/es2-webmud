/* 闇雲雙刃斧 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("\x1b[1;37m闇雲雙刃斧\x1b[m", ({ "blackcloud axe", "axe" }));
    set_weight(6800);
    init_damage(3, 30, 133, 1, "twohanded axe");
    init_damage(3, 15, 100, 1, "axe");

    if( !clonep() ) {
        set("wield_as", ({ "twohanded axe", "axe" }));
        set("unit", "把");
        set("value", 5000);
        set("long",
            "一把通身墨黑的雙刃斧,銳利的雙鋒閃耀著詭異的光芒,是由這一帶的特殊鐵礦鍛煉出來的兵器\n");
        set("apply_weapon/twohanded axe", ([
            "cps": -1,
            "attack": 10,
            "str": 1,
        ]));
    }
    setup();
}
