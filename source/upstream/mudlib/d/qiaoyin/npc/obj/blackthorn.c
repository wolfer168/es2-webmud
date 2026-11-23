/* 玄蘇劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;30m玄蘇劍\x1b[m", ({ "blackthorn", "sword" }));
    set_weight(23900);
    init_damage(3, 30, 157, 4, "twohanded sword");

    if( !clonep() ) {
        set("wield_as", "twohanded sword");
        set("unit", "把");
        set("value", 30000);
        set("long",
            "這是一把劍身黝黑，劍刃生滿細刺的古劍，向來是封山劍派掌門人\n"
            "所使用的配劍，據說這把劍不會染血，而且經常散發出一股可怕的\n"
            "殺氣。\n");
        set("apply_weapon/twohanded sword", ([
            "twohanded sword": 10,
            "intimidate": 50,
            "fonxansword": 10,
        ]));
    }
    setup();
}
