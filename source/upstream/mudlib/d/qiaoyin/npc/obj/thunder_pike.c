/* 紫電紅纓槍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("\x1b[1;35m紫電紅纓槍\x1b[m", ({ "thunder pike", "pike" }));
    set_weight(17100);
    init_damage(4, 14, 90, 5, "twohanded pike");

    if( !clonep() ) {
        set("wield_as", "twohanded pike");
        set("unit", "把");
        set("value", 65000);
        set("long",
            "一桿綴著紅纓的丈八長槍，槍尖平滑如鏡，近看似乎有條紫蛇在槍尖\n"
            "盤旋游動，槍桿挺直而有彈性，摸起來非金非木，不知道是什麼質料\n"
            "。\n");
        set("apply_weapon/twohanded pike", ([
            "wittiness": 20,
            "parry": 25,
        ]));
    }
    setup();
}
