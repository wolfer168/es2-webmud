/* 黑鋼短刃 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("黑鋼短刃", ({ "black iron dagger", "dagger" }));
    set_weight(5700);
    init_damage(2, 15, 100, 8, "dagger");
    init_damage(2, 15, 100, 8, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 4000);
        set("long",
            "一把用黑鋼打製成的沉重短刃, 刃柄上刻了一些奇怪的紋路。\n");
        set("apply_weapon/dagger", ([
            "attack": 30,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "attack": 30,
        ]));
    }
    setup();
}
