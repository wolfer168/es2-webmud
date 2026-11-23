// /d/oldpine/npc/obj/head_cloth.c — 頭巾（徐彪），防禦力 1。
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("頭巾", ({ "head cloth", "cloth" }));
    set_weight(100);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 50);
        set("long", "一條纏在頭上的灰布頭巾，沾滿了汗漬與塵土。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor": 1,
        ]));
    }
    setup();
}
