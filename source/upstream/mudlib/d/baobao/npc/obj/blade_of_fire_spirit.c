/* 邪刀•焱靈 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("\x1b[1;31m邪刀•焱靈\x1b[m", ({ "blade of fire spirit", "blade" }));
    set_weight(25500);
    init_damage(3, 32, 90, 6, "twohanded blade");

    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 15000);
        set("long",
            "刀身透著邪異的火紅,又似鮮血欲滴,甫一接觸刀柄令你感到如雷亟般痛楚,\n"
            "心中產生莫名殺意....\n");
        set("apply_weapon/twohanded blade", ([
            "damage": 25,
            "twohanded blade": 10,
            "armor_vs_fire": 100,
        ]));
    }
    setup();
}
