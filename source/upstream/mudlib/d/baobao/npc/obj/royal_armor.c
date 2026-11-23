/* 霸王鎧 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

// 原資料「職業限制：軍人」：只有軍人能穿戴。
varargs int wear(string on_part)
{
    object owner = environment();

    if( objectp(owner) && owner->query_class() != "soldier" )
        return notify_fail("只有軍人才能穿戴這樣東西。\n");
    return ::wear(on_part);
}

void create()
{
    set_name("\x1b[1;37m霸王鎧\x1b[m", ({ "royal armor", "armor" }));
    set_weight(12000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 15000);
        set("long",
            "亮白色的寶甲，護著肩部的地方是兩個虎頭，正中一面雪亮的護\n"
            "心鏡。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "parry": 10,
            "powerblow": 10,
            "armor": 25,
        ]));
    }
    setup();
}
