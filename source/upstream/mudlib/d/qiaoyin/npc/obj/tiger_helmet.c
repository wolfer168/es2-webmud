/* 虎首盔 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("\x1b[1;33m虎首盔\x1b[m", ({ "tiger helmet", "helmet" }));
    set_weight(2000);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 25000);
        set("long",
            "一頂金黃色的虎頭形鋼盔﹐一雙憤怒的虎眼炯炯有神﹐似乎正掃視著\n"
            "週邊的敵人。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "cor": 1,
            "damage": 5,
            "defense": 10,
        ]));
    }
    setup();
}
