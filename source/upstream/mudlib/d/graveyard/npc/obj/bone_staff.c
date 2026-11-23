/* 白骨杖 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("白骨杖", ({ "bone staff", "staff" }));
    set_weight(2600);
    init_damage(2, 8, 90, 0, "staff");
    init_damage(3, 12, 135, 0, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", ({ "staff", "twohanded staff" }));
        set("unit", "把");
        set("value", 100000);
        set("long",
            "白骨杖其實就是一根又粗又長的大骨頭.\n");
    }
    setup();
}
