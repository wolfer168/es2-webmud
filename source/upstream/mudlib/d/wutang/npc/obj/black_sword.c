/* 黑劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("黑劍", ({ "black sword", "sword" }));
    set_weight(7200);
    init_damage(3, 15, 100, 4, "sword");
    init_damage(3, 7, 100, 4, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 10000);
        set("long",
            "一把細劍, 長度較一般長劍略短, 劍身呈墨黑, 份量相當的輕。\n");
        set("apply_weapon/sword", ([
            "attack": 15,
            "dex": 2,
        ]));
        set("apply_weapon/secondhand sword", ([
            "dex": 1,
        ]));
    }
    setup();
}
