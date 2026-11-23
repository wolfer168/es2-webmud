/* 虎嘯旭日鎧 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("\x1b[1;37m虎嘯旭日鎧\x1b[m", ({ "tiger plate", "plate" }));
    set_weight(12000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 25000);
        set("long",
            "一副用上等的灰鋼打造的鎧甲。鎧甲的背面和側面總共刻了六隻\n"
            "猛虎，正面刻的是一輪旭日。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 30,
            "damage": 10,
        ]));
    }
    setup();
}
