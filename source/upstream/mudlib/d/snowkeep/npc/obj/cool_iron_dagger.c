/* 寒鐵匕首 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("寒鐵匕首", ({ "cool-iron dagger", "dagger" }));
    set_weight(5700);
    init_damage(2, 15, 100, 8, "dagger");
    init_damage(2, 15, 100, 8, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 5000);
        set("long",
            "這是一把用寒鐵打造的精緻匕首, 看起來似乎不太鋒利。\n");
        set("apply_weapon/dagger", ([
            "cps": 1,
            "attack": 5,
            "absorption": 5,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "cps": 1,
            "attack": 5,
            "absorption": 5,
        ]));
    }
    setup();
}
