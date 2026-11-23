/* 蝴蝶短刺 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("蝴蝶短刺", ({ "butterfly stiletto", "dagger" }));
    set_weight(4400);
    init_damage(3, 8, 50, 5, "dagger");
    init_damage(3, 8, 50, 5, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 65000);
        set("long",
            "一把銳利的短刺, 由於刻有蝴蝶圖案, 顯的相當典雅, 是一把特製的短刃\n"
            ", 最適合偷襲之用。\n");
        set("apply_weapon/dagger", ([
            "butterfly-steps": 5,
            "dodge": 5,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "butterfly-steps": 5,
            "dodge": 5,
        ]));
    }
    setup();
}
