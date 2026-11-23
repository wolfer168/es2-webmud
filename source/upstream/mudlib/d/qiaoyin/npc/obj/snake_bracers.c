/* 纏蛇護手 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("\x1b[1;37m纏蛇護手\x1b[m", ({ "snake bracers", "bracers" }));
    set_weight(400);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 4500);
        set("long",
            "一雙看起來滿耐用的護手﹐由於護手外層的皮革是纏繞在護手\n"
            "上的﹐所以好像一條黑蛇盤在上面一樣。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "wittiness": 30,
            "awarness": 30,
        ]));
    }
    setup();
}
