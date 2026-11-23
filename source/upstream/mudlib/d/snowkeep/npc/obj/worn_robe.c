/* 舊長袍 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("舊長袍", ({ "worn robe", "robe" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 2500);
        set("long",
            "一件看起來就知道已經穿了幾十年的長袍﹐顏色灰撲撲的。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "dodge": -1,
            "armor": 1,
        ]));
    }
    setup();
}
