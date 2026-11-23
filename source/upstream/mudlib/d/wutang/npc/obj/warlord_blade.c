/* 戰神劈天刀 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("戰神劈天刀", ({ "warlord blade", "blade" }));
    set_weight(30000);
    init_damage(4, 30, 195, 4, "twohanded blade");

    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 25000);
        set("long",
            "此刀重九十斤長近八尺，輕輕一揮便揚起萬丈沙塵。\n");
        set("apply_weapon/twohanded blade", ([
            "heavy_parry": 10,
            "intimidate": 30,
            "berserk": 15,
            "attack": 25,
        ]));
    }
    setup();
}
