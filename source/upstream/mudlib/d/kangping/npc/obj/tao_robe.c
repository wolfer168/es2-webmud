/* 杏黃道袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("杏黃道袍", ({ "tao robe", "robe" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 3000);
        set("long",
            "一件杏黃色的普通道袍，洗得有些褪色了。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "spells": 10,
            "armor": 1,
        ]));
    }
    setup();
}
