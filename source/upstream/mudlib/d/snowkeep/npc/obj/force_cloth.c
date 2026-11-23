/* 真元戰袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("真元戰袍", ({ "force cloth", "cloth" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 3000);
        set("long",
            "這是一件質地相當不錯的長袍﹐穿在身上一定又舒服又暖和。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor_vs_ice": 50,
            "armor": 10,
            "defense": 25,
            "force": 10,
        ]));
    }
    setup();
}
