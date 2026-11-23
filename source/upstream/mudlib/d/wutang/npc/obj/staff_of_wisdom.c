/* 谷玉 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("\x1b[1;32m谷玉\x1b[m", ({ "staff of wisdom", "staff" }));
    set_weight(2600);
    init_damage(2, 8, 90, 0, "staff");
    init_damage(3, 12, 135, 0, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", ({ "staff", "twohanded staff" }));
        set("unit", "把");
        set("value", 25000);
        set("long",
            "一根晶瑩的翠綠色手杖﹐造型優雅別致華麗而不失莊重。\n");
        set("apply_weapon/staff", ([
            "taoism-storm": 15,
            "wis": 2,
            "armor": 20,
            "magic_ability": 20,
        ]));
    }
    setup();
}
