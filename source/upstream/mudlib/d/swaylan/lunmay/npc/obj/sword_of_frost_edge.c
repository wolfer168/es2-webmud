/* 寒霜劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;37m寒霜劍\x1b[m", ({ "sword of frost-edge", "sword" }));
    set_weight(8700);
    init_damage(3, 18, 100, 6, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 15000);
        set("long",
            "一把通體白皙的鋒利寶劍, 削鐵如泥, 劍身隱隱透出白光。\n");
        set("apply_weapon/sword", ([
            "cps": 2,
            "armor": 10,
            "wittiness": 30,
        ]));
    }
    setup();
}
