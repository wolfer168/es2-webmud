/* 蜂尾針 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_NEEDLE;

void create()
{
    set_name("蜂尾針", ({ "bee needle", "needle" }));
    set_weight(500);
    init_damage(3, 12, 90, 4, "needle");
    init_damage(3, 12, 90, 4, "secondhand needle");

    if( !clonep() ) {
        set("wield_as", ({ "needle", "secondhand needle" }));
        set("unit", "把");
        set("value", 65000);
        set("long",
            "一支頭部極寬, 但尾部細如蜂刺的灸針。\n");
        set("apply_weapon/needle", ([
            "dex": 1,
            "wuto-needle": 10,
        ]));
    }
    setup();
}
