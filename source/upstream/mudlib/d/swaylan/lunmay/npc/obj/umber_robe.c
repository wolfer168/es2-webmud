/* 繭綢長袍 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("繭綢長袍", ({ "umber robe", "robe" }));
    set_weight(1000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 4500);
        set("long",
            "這是一件式樣樸實的繭綢醬色長袍﹐是中上人家的男子衣衫。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 6,
        ]));
    }
    setup();
}
