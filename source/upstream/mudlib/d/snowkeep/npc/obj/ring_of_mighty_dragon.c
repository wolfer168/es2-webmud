/* 巨龍指環 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

// 原資料「職業限制：武者」：只有武者能穿戴。
varargs int wear(string on_part)
{
    object owner = environment();

    if( objectp(owner) && owner->query_class() != "fighter" )
        return notify_fail("只有武者才能穿戴這樣東西。\n");
    return ::wear(on_part);
}

void create()
{
    set_name("\x1b[1;33m巨龍指環\x1b[m", ({ "ring of mighty dragon", "ring" }));
    set_weight(300);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 90000);
        set("long",
            "一枚沉重的純金指環﹐指環上鑲著一條姿態優雅的黃金龍。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "cor": 1,
            "damage": 10,
            "armor": 5,
        ]));
    }
    setup();
}
