/* 百鬼腰束 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("百鬼腰束", ({ "ghosts girdle", "girdle" }));
    set_weight(300);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 20000);
        set("long",
            "一條寬寬的﹐縫製得十分精細的腰帶。腰帶正反兩面共繡有各種鬼類一百整。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "defense": 5,
            "awarness": 15,
            "str": 1,
        ]));
    }
    setup();
}
