// /d/lee/npc/obj/black_stone_axe.c
// NEW（野羊山事件新增道具，設計見 docs/LEE_BANDIT_RAID.md）
#include <ansi.h>
#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("黑石斧", ({ "black stone axe", "axe" }));
    set_weight(14000);
    setup_axe(3, 14, 120, 5);

    if( !clonep() ) {
        set("wield_as", ({ "axe", "secondhand axe" }));
        set("unit", "把");
        set("value", 3000);
        set("long",
            "一把黑黝黝的石斧，斧頭是整塊黑石打磨而成，木柄上纏著一圈圈發黑的麻繩，\n"
            "乍看不過是柴房裡劈柴的粗貨，掄起來卻沉得壓手，一斧下去連門板都能劈穿。\n");
        set("apply_weapon/axe", ([
            "str": 1,
            "damage": 5,
            "move": 30,
        ]));
        set("apply_weapon/secondhand axe", ([
            "str": 1,
            "damage": 5,
            "move": 30,
        ]));
    }
    setup();
}
