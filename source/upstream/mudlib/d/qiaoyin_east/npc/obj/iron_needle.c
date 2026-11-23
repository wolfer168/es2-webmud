/* 透骨釘 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_NEEDLE;

void create()
{
    set_name("透骨釘", ({ "iron needle", "needle" }));
    set_weight(500);
    init_damage(2, 9, 80, 5, "needle");
    init_damage(2, 9, 80, 5, "secondhand needle");

    if( !clonep() ) {
        set("wield_as", ({ "needle", "secondhand needle" }));
        set("unit", "把");
        set("value", 60000);
        set("long",
            "一支江湖上常見的長針, 通常是拿來當做暗器使用, 鐵鑄的細針\n"
            "相當的堅韌, 亦可拿來針灸刺穴之用。\n");
        set("apply_weapon/needle", ([
            "wuto-needle": 5,
            "attack": 5,
        ]));
        set("apply_weapon/secondhand needle", ([
            "wuto-needle": 5,
            "attack": 5,
        ]));
    }
    setup();
}
