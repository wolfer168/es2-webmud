/* 青竹腿護 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_LEG_EQ;

void create()
{
    set_name("青竹腿護", ({ "bamboo legs", "legs" }));
    set_weight(300);
    setup_leg_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 500);
        set("long",
            "十分輕便的護具，雖然做工十分簡單﹐但是卻有著不錯的防護能力。\n");
        set("wear_as", "leg_eq");
        set("apply_armor/leg_eq", ([
            "defense": 5,
            "wittiness": 5,
        ]));
    }
    setup();
}
