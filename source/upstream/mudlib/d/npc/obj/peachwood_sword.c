/* 桃木劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("桃木劍", ({ "peachwood sword", "sword" }));
    set_weight(2600);
    init_damage(1, 15, 40, 1, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 4000);
        set("long",
            "一把桃木所刻的長劍﹐道士作法時常用桃木劍增加魔力。\n");
        set("apply_weapon/sword", ([
            "spells": 10,
            "magic": 10,
        ]));
    }
    setup();
}
