/* 咒劍紅羽 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;31m咒劍紅羽\x1b[m", ({ "sword of redrune", "sword" }));
    set_weight(3300);
    init_damage(2, 10, 50, 1, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 5000);
        set("long",
            "一把從劍柄、護手、劍鞘全都如火焰般通紅的長劍，劍刃部份則刻著\n"
            "許多道家密咒，以及火焰狀的圖形。\n");
        set("apply_weapon/sword", ([
            "wis": 1,
            "spells": 5,
            "taoism-fire": 5,
        ]));
    }
    setup();
}
