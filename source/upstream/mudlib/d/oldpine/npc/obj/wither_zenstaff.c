/* 枯禪杖 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("\x1b[1;36m枯禪杖\x1b[m", ({ "wither zenstaff", "staff" }));
    set_weight(19000);
    init_damage(3, 20, 202, 10, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("unit", "把");
        set("value", 70000);
        set("long",
            "一把青銅鑄成的禪杖，杖頭上面鑲著十二個鐵環。\n");
        set("apply_weapon/twohanded staff", ([
            "compassion": 10,
            "wis": 2,
            "absorption": 10,
        ]));
    }
    setup();
}
