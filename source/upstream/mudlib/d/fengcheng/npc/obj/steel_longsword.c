/* 精鋼長劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("精鋼長劍", ({ "steel longsword", "sword" }));
    set_weight(3300);
    init_damage(2, 10, 50, 1, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 7500);
        set("long",
            "一把精鋼鑄造的長劍，寒光四射，看來是口利器。\n");
        set("apply_weapon/sword", ([
            "parry": 5,
        ]));
    }
    setup();
}
