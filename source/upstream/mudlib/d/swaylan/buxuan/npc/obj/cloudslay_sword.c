/* 落雲刃 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;36m落雲刃\x1b[m", ({ "cloudslay sword", "sword" }));
    set_weight(8700);
    init_damage(3, 18, 100, 6, "sword");
    init_damage(3, 18, 100, 6, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 15000);
        set("long",
            "此劍劍身不長，日光下映射出的幽幽藍光中似有一絲寒意，揮動起來毫無阻\n"
            "力，是把可遇不可求的短刃。\n");
        set("apply_weapon/sword", ([
            "armor_vs_wind": 50,
            "intimidate": 50,
            "armor_vs_ice": 50,
            "armor_vs_fire": 50,
            "armor_vs_lightning": 50,
        ]));
        set("apply_weapon/secondhand sword", ([
            "armor_vs_wind": 50,
            "intimidate": 50,
            "armor_vs_ice": 50,
            "armor_vs_fire": 50,
            "armor_vs_lightning": 50,
        ]));
    }
    setup();
}
