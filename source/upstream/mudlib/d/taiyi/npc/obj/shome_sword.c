/* 少眉劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;33m少眉劍\x1b[m", ({ "shome sword", "sword" }));
    set_weight(3300);
    init_damage(2, 10, 50, 1, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 70000);
        set("long",
            "一把古銅色的寬刃長劍, 劍柄上刻著「少眉」兩字。\n");
        set("apply_weapon/sword", ([
            "taoism-freeze": 15,
            "armor_vs_fire": 15,
        ]));
    }
    setup();
}
