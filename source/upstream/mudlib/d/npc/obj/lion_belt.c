/* 獅蠻帶 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("獅蠻帶", ({ "lion belt", "belt" }));
    set_weight(300);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 15000);
        set("long",
            "一條繡著猛獅圖案的腰帶﹐給人一種威武的感覺。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "damage": 5,
            "cor": 1,
        ]));
    }
    setup();
}
