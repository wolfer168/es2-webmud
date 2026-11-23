/* 紫紗衫 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("\x1b[1;35m紫紗衫\x1b[m", ({ "violet cloth", "cloth" }));
    set_weight(1000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 10000);
        set("long",
            "一件用紫色輕紗所製的衣服，質感十分柔軟。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "spi": -1,
            "armor": 5,
            "dex": 1,
            "armor_vs_ice": 30,
        ]));
    }
    setup();
}
