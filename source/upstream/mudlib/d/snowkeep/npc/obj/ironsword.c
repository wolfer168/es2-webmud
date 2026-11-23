/* 雛鐵劍 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("雛鐵劍", ({ "ironsword", "sword" }));
    set_weight(3300);
    init_damage(2, 10, 50, 1, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 85000);
        set("long",
            "這是一把雛鐵所鑄的重劍﹐拿在手中沈甸甸的。\n");
        set("apply_weapon/sword", ([
            "parry": 10,
            "attack": 10,
        ]));
    }
    setup();
}
