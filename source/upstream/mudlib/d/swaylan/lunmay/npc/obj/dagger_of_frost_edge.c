/* 冰雪匕 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("\x1b[1;37m冰雪匕\x1b[m", ({ "dagger of frost-edge", "dagger" }));
    set_weight(8800);
    init_damage(3, 17, 85, 10, "dagger");
    init_damage(3, 17, 85, 10, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 10000);
        set("long",
            "一把通體白皙的短刃, 和寒霜劍同為冷梅莊莊主的成名兵器。\n");
        set("apply_weapon/dagger", ([
            "cps": 1,
            "armor": 10,
            "wittiness": 30,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "cps": 1,
            "armor": 10,
            "wittiness": 30,
        ]));
    }
    setup();
}
