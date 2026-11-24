// /d/lee/npc/obj/bone_blade.c
// NEW（野羊山事件新增道具，設計見 docs/LEE_BANDIT_RAID.md）
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("羊骨刀", ({ "bone blade", "blade" }));
    set_weight(11000);
    init_damage(3, 17, 150, 4, "twohanded blade");

    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 2500);
        set("long",
            "一把用整根羊腿骨磨成的大砍刀，刀身慘白厚實，刃口卻磨得雪亮，握柄處胡\n"
            "亂纏了幾圈羊皮，看似粗製濫造，劈下去的分量卻一點也不輕。\n");
        set("apply_weapon/twohanded blade", ([
            "intimidate": 15,
            "cor": 1,
            "damage": 5,
        ]));
    }
    setup();
}
