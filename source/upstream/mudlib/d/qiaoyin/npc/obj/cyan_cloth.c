/* 青布官服 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("青布官服", ({ "cyan cloth", "cloth" }));
    set_weight(1000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 17000);
        set("long",
            "青色綢緞製成的官服，上有金絲繡成的花紋。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 3,
            "int": 1,
            "mysticism": 5,
        ]));
    }
    setup();
}
