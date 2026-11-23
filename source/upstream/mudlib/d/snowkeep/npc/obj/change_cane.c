/* 移殤杖 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("移殤杖", ({ "change cane", "staff" }));
    set_weight(14000);
    init_damage(3, 12, 120, 10, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("unit", "把");
        set("value", 25000);
        set("long",
            "一把銀灰色看似不起眼的手杖。\n");
        set("apply_weapon/twohanded staff", ([
            "wittiness": 50,
            "armor": 10,
        ]));
    }
    setup();
}
