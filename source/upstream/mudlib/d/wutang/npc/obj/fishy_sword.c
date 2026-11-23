/* 魚腸 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;36m魚腸\x1b[m", ({ "fishy sword", "sword" }));
    set_weight(9400);
    init_damage(3, 20, 150, 5, "sword");
    init_damage(3, 20, 150, 5, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 50000);
        set("long",
            "魚腸劍乃是奐族人用青鋼打製，置於清水之中數年後才開封的短劍\n"
            "的總稱。此類劍身偏寬且長不及常人小臂，然而，其劍刃卻有一陣\n"
            "青藍色的寒光湧現，是不可多得的利器。\n");
        set("apply_weapon/sword", ([
            "intimidate": 15,
            "attack": 30,
        ]));
        set("apply_weapon/secondhand sword", ([
            "intimidate": 15,
            "attack": 30,
        ]));
    }
    setup();
}
