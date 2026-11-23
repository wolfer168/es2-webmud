/* 盤龍針 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_NEEDLE;

void create()
{
    set_name("盤龍針", ({ "dragon needle", "needle" }));
    set_weight(500);
    init_damage(2, 10, 85, 7, "needle");
    init_damage(2, 10, 85, 7, "secondhand needle");

    if( !clonep() ) {
        set("wield_as", ({ "needle", "secondhand needle" }));
        set("unit", "把");
        set("value", 15000);
        set("long",
            "一支用黑鐵鑄造的長針﹐針身盤有一條張牙舞爪的惡龍﹐龍尾與針\n"
            "尖融為一體﹐異常尖銳。\n");
        set("apply_weapon/needle", ([
            "kee anatomy": 15,
            "secondhand needle": 20,
            "str": 1,
        ]));
        set("apply_weapon/secondhand needle", ([
            "kee anatomy": 15,
            "secondhand needle": 20,
            "str": 1,
        ]));
    }
    setup();
}
