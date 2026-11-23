/* 鑲玉短劍 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("鑲玉短劍", ({ "jeweled shortsword", "shortsword" }));
    set_weight(3300);
    init_damage(2, 10, 50, 1, "sword");
    init_damage(2, 10, 50, 1, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 60000);
        set("long",
            "這把短劍上面嵌了一塊碧綠的美玉﹐看起來相當名貴。\n");
        set("apply_weapon/sword", ([
            "spi": 1,
            "spell": 5,
            "wis": 1,
        ]));
        set("apply_weapon/secondhand sword", ([
            "spi": 1,
            "spell": 5,
            "wis": 1,
        ]));
    }
    setup();
}
