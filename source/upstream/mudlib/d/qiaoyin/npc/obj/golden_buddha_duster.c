/* 金絲拂塵 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_WHIP;

void create()
{
    set_name("\x1b[1;33m金絲拂塵\x1b[m", ({ "golden buddha duster", "whip" }));
    set_weight(6300);
    init_damage(3, 12, 100, 7, "whip");

    if( !clonep() ) {
        set("wield_as", "whip");
        set("unit", "把");
        set("value", 10000);
        set("long",
            "一根白鐵為柄、金絲為鬚的拂塵，看起來頗為素雅。\n");
        set("apply_weapon/whip", ([
            "damage": 30,
            "attack": 30,
        ]));
    }
    setup();
}
