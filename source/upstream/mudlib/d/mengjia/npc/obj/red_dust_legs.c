/* 風塵腿護 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_LEG_EQ;

void create()
{
    set_name("風塵腿護", ({ "red-dust legs", "legs" }));
    set_weight(300);
    setup_leg_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 4000);
        set("long",
            "十分輕便的護具，在注重舒適感的同時，也十分注重防禦能力。\n");
        set("wear_as", "leg_eq");
        set("apply_armor/leg_eq", ([
            "armor": 5,
            "defense": 5,
        ]));
    }
    setup();
}
