/* 百鬼刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("百鬼刀", ({ "ghosts blade", "blade" }));
    set_weight(6100);
    init_damage(3, 12, 90, 5, "blade");

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 20000);
        set("long",
            "刀身與普通的單刀一樣，只是在刀背上淺淺的刻著十來隻修羅。\n");
        set("apply_weapon/blade", ([
            "defense": 20,
            "cps": 2,
        ]));
    }
    setup();
}
