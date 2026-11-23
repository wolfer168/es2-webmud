/* 闇之寶靴 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

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
    set_name("\x1b[1;30m闇之寶靴\x1b[m", ({ "dark boots", "boots" }));
    set_weight(500);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 5000);
        set("long",
            "一雙用特殊的黑色細絲線做成的靴子。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "dodge": 10,
            "sneak": 10,
            "armor_vs_lightning": 50,
        ]));
    }
    setup();
}
