/* 霸王指環 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

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
    set_name("\x1b[1;37m霸王指環\x1b[m", ({ "ring of mighty lord", "ring" }));
    set_weight(300);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 20000);
        set("long",
            "一枚看起來十分沉重銅指環﹐隱約散發出一股高貴的王者之氣。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "cor": 1,
            "powerblow": 10,
            "damage": 5,
        ]));
    }
    setup();
}
