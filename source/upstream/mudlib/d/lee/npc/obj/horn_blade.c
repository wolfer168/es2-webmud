// /d/lee/npc/obj/horn_blade.c
// NEW（野羊山事件新增道具，設計見 docs/LEE_BANDIT_RAID.md）
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("羊角刀", ({ "horn blade", "blade" }));
    set_weight(3500);
    init_damage(3, 6, 100, 5, "secondhand blade");

    if( !clonep() ) {
        set("wield_as", "secondhand blade");
        set("unit", "把");
        set("value", 800);
        set("long",
            "一把彎彎的短刀，刀柄是用整支羊角削成的，握在手裡又彎又滑，使起來倒別\n"
            "有一番野路子的刁鑽。\n");
        set("apply_weapon/secondhand blade", ([
            "damage": 5,
        ]));
    }
    setup();
}
