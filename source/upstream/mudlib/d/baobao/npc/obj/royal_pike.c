/* 霸王槍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("\x1b[1;37m霸王槍\x1b[m", ({ "royal pike", "pike" }));
    set_weight(19200);
    init_damage(3, 22, 135, 5, "twohanded pike");

    if( !clonep() ) {
        set("wield_as", "twohanded pike");
        set("unit", "把");
        set("value", 20000);
        set("long",
            "一柄用玄鐵打造的十尺長槍，槍身呈暗黑色，槍尖隱隱散發著紅光。\n");
        set("apply_weapon/twohanded pike", ([
            "powerblow": 15,
            "berserk": 15,
        ]));
    }
    setup();
}
