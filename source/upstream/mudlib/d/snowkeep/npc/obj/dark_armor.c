/* 闇之絲甲 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

// 原資料「職業限制：盜賊」：只有盜賊能穿戴。
varargs int wear(string on_part)
{
    object owner = environment();

    if( objectp(owner) && owner->query_class() != "thief" )
        return notify_fail("只有盜賊才能穿戴這樣東西。\n");
    return ::wear(on_part);
}

void create()
{
    set_name("\x1b[1;30m闇之絲甲\x1b[m", ({ "dark armor", "armor" }));
    set_weight(3000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 10000);
        set("long",
            "一套由黑色細絲製作而成的護甲，這套護甲對一些法術似乎有些擋抗力。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 20,
            "armor_vs_wind": 20,
            "sneak": 10,
            "awarness": 50,
        ]));
    }
    setup();
}
