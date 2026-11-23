/* 軟麻青絲衣 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("軟麻青絲衣", ({ "soft cloth", "cloth" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 1500);
        set("long",
            "一件痲製的青色道服﹐若不仔細看還以為是件陰森的喪服。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor_vs_wind": 30,
            "armor": 10,
        ]));
    }
    setup();
}
