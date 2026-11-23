/* 蛟骨刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("蛟骨刀", ({ "blade of hydra bone", "blade" }));
    set_weight(9200);
    init_damage(3, 20, 110, 4, "blade");

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 25000);
        set("long",
            "一把用鮫蛟之骨打磨而成的妖刀﹐臃腫的刀身是用橫七豎八鮫蛟骨拼湊而成。\n"
            "此刀雖然無鋒﹐但是卻散發出一股強烈的殺氣。\n");
        set("apply_weapon/blade", ([
            "intimidate": 10,
            "deep blade": 20,
        ]));
    }
    setup();
}
