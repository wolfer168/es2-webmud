/* 巨斧 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("巨斧", ({ "huge axe", "axe" }));
    set_weight(23200);
    init_damage(3, 30, 133, 1, "twohanded axe");

    if( !clonep() ) {
        set("wield_as", "twohanded axe");
        set("unit", "把");
        set("value", 95000);
        set("long",
            "一把精鋼所鑄的巨斧，份量相當沉重，軍中的力士都喜歡這種兵刃。\n");
    }
    setup();
}
