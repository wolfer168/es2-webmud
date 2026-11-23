/* 霸王銅冠 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

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
    set_name("\x1b[1;37m霸王銅冠\x1b[m", ({ "royal helmet", "helmet" }));
    set_weight(2000);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 4000);
        set("long",
            "霸王銅冠是用黃銅製成的，雖然有些重，但是顯得十分高貴典雅。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "damage": 10,
            "attack": 15,
            "awarness": 50,
        ]));
    }
    setup();
}
