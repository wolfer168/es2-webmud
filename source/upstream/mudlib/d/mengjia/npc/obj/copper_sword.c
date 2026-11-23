/* 古銅重劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("古銅重劍", ({ "copper sword", "sword" }));
    set_weight(13000);
    init_damage(3, 13, 106, 2, "twohanded sword");

    if( !clonep() ) {
        set("wield_as", "twohanded sword");
        set("unit", "把");
        set("value", 65000);
        set("long",
            "又寬又長的一把重劍，由於整把重劍都是由黃銅打造而成，所以\n"
            "需要很大的膂力才能使用。\n");
        set("apply_weapon/twohanded sword", ([
            "attack": 5,
            "parry": 10,
        ]));
    }
    setup();
}
