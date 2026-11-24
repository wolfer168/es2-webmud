// /d/lee/npc/obj/goat_blade.c
// NEW（野羊山事件新增道具，設計見 docs/LEE_BANDIT_RAID.md）
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("羊頭刀", ({ "goat blade", "blade" }));
    set_weight(7000);
    setup_blade(3, 12, 110, 5);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 1200);
        set("long",
            "一把刀背上鑄著羊頭的厚背砍刀，羊頭鑄得歪鼻斜眼，不倫不類，山寨裡的嘍\n"
            "囉人手一把，砍起人來卻是實打實的。\n");
        set("apply_weapon/blade", ([
            "attack": 25,
            "dex": 2,
        ]));
    }
    setup();
}
