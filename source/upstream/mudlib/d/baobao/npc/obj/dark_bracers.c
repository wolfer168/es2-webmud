/* 闇之護手 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

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
    set_name("\x1b[1;30m闇之護手\x1b[m", ({ "dark bracers", "bracers" }));
    set_weight(200);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 5000);
        set("long",
            "一對用堅硬的黑色細絲線製成的手護。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "cor": 2,
            "killerhood": 5,
        ]));
    }
    setup();
}
