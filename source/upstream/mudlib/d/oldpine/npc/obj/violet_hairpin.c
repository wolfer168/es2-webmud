/* 紫玉釵 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("\x1b[1;35m紫玉釵\x1b[m", ({ "violet hairpin", "hairpin" }));
    set_weight(100);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 25000);
        set("long",
            "一條綁成蝴蝶結狀的髮帶，上面鑲有一顆紫色寶石。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "defense": 1,
            "int": 1,
        ]));
    }
    setup();
}
