/* 淡紅女衫 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("淡紅女衫", ({ "pink dress", "dress" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 5000);
        set("long",
            "一件淡紅色的女子衣衫﹐式樣相當豔麗。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 1,
        ]));
    }
    setup();
}
