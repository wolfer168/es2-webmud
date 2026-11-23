/* 精鋼護腕 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("精鋼護腕", ({ "steel bracers", "bracers" }));
    set_weight(800);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 2000);
        set("long",
            "一對精鋼鑄造的護腕，可以提供相當程度的保護。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "armor": 10,
            "wittiness": 15,
        ]));
    }
    setup();
}
