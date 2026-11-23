/* 驂龍翔 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("\x1b[1;35m驂龍翔\x1b[m", ({ "wyvern axe", "axe" }));
    set_weight(16500);
    init_damage(3, 16, 133, 10, "twohanded axe");

    if( !clonep() ) {
        set("wield_as", "twohanded axe");
        set("unit", "把");
        set("value", 45000);
        set("long",
            "一把紫色的龍紋巨斧, 斧背上還刻著一首短詩.\n"
            "耀如弈射九日落,\n"
            "矯為群帝驂龍翔.\n");
        set("apply_weapon/twohanded axe", ([
            "powerblow": 4,
            "heavy_parry": 4,
            "twohanded axe": 4,
            "berserk": 4,
        ]));
    }
    setup();
}
