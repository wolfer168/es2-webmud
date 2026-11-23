/* 洗銀劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;37m洗銀劍\x1b[m", ({ "silver sword", "sword" }));
    set_weight(3300);
    init_damage(2, 10, 50, 1, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 80000);
        set("long",
            "一把銀製的短劍﹐鑄造得十分精美。\n");
        set("apply_weapon/sword", ([
            "taoism of dunja": 5,
            "virtual sword": 5,
            "mysticism": 5,
        ]));
    }
    setup();
}
