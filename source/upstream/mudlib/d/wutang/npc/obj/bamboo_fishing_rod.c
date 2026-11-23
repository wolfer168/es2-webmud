/* 竹釣竿 — 一般釣竿，比生鐵釣竿弱；產生時會隨機獲得武器附加屬性（adm/daemons/enhanced.c）。 */
#include <weapon.h>

inherit F_WHIP;

void create()
{
    set_name("竹釣竿", ({ "bamboo fishing rod", "fishing rod", "rod", "whip" }));
    set_weight(3500);
    init_damage(2, 10, 100, 4, "whip");

    if( !clonep() ) {
        set("wield_as", "whip");
        set("affix_short_name", "竿");
        set("unit", "支");
        set("value", 2000);
        set("long",
            "一支用老竹削成的釣竿，竿身輕巧柔韌，是漁夫常用的釣具，危急時也能拿來揮打防身。\n");
        set("apply_weapon/whip", ([
            "halieutics": 3,
        ]));
    }
    setup();
    // 武器附加屬性：每支新產生的釣竿擲一次前綴／後綴。
    if( clonep() ) ENHANCE_D->roll_affix(this_object());
}
