/* 影匕 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("影匕", ({ "shadow dagger", "dagger" }));
    set_weight(4400);
    init_damage(3, 8, 50, 5, "dagger");
    init_damage(3, 8, 50, 5, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 10000);
        set("long",
            "一把鋒利的短匕首﹐握在手裡重量剛剛好。\n");
        set("apply_weapon/dagger", ([
            "wis": 1,
            "spi": 1,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "wis": 1,
            "spi": 1,
        ]));
    }
    setup();
}
