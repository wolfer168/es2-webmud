/* 鎖子甲 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("鎖子甲", ({ "ringmail" }));
    set_weight(8000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 8000);
        set("long",
            "一件由金屬環, 環環相扣所造成的鎖子甲, 防護力略差, 但由於輕便, 為實戰上極為常見的護甲。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "cor": 1,
            "armor": 5,
            "str": 1,
            "attack": 10,
        ]));
    }
    setup();
}
