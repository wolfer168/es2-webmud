/* 偃月刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("\x1b[1;37m偃月刀\x1b[m", ({ "moon blade", "blade" }));
    set_weight(14500);
    init_damage(3, 16, 105, 0, "twohanded blade");

    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 80000);
        set("long",
            "一把雪白色的寶刀, 刀身隱隱泛出溫和的白光\n");
        set("apply_weapon/twohanded blade", ([
            "attack": 10,
            "intimidate": 10,
            "parry": 10,
        ]));
    }
    setup();
}
