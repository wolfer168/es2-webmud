/* 黑斗笠 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("\x1b[1;30m黑斗笠\x1b[m", ({ "black doli", "doli" }));
    set_weight(300);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 50);
        set("long",
            "一頂用竹葉編成的鬥笠，塗上黑漆以加強防水效果。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "wittiness": 50,
        ]));
    }
    setup();
}
