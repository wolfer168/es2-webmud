/* 厚柄斧 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("厚柄斧", ({ "large axe", "axe" }));
    set_weight(6900);
    init_damage(3, 14, 100, 5, "axe");

    if( !clonep() ) {
        set("wield_as", "axe");
        set("unit", "把");
        set("value", 65000);
        set("long",
            "看來相當厚重的大斧﹐一般人恐怕拿不起來。\n");
        set("apply_weapon/axe", ([
            "attack": 10,
        ]));
    }
    setup();
}
