/* 白馬盔 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("\x1b[1;37m白馬盔\x1b[m", ({ "white helmet", "helmet" }));
    set_weight(2000);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 5000);
        set("long",
            "一頂雪白的頭盔﹐整個頭盔呈現出一種優雅的流線形﹐給人一種難言\n"
            "的美感。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "defense": 10,
            "str": 1,
            "armor": 5,
        ]));
    }
    setup();
}
