/* 鹿皮手套 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("\x1b[0;33m鹿皮手套\x1b[m", ({ "skin gloves", "gloves" }));
    set_weight(400);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 1000);
        set("long",
            "一對由鹿皮所製的手套，可以提供相當程度的保護。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "damage": 5,
            "armor": 5,
        ]));
    }
    setup();
}
