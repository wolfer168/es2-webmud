/* 金絲八卦刀 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("金絲八卦刀", ({ "golden blade", "blade" }));
    set_weight(9200);
    init_damage(3, 20, 110, 4, "blade");

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 15000);
        set("long",
            "此刀刀背鍍有一層薄金，上面雕有八卦的圖案，刀口處寒光閃閃異常鋒利。\n");
        set("apply_weapon/blade", ([
            "armor": 15,
            "deep blade": 30,
            "intimidate": 50,
        ]));
    }
    setup();
}
