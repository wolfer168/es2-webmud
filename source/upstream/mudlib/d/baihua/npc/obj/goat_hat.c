/* 神羊帽 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("神羊帽", ({ "hat" }));
    set_weight(800);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 15000);
        set("long",
            "一頂似有神力之帽, 上面鏽了一頭黑皮巨羊, 瞠目怒容, 氣勢非常. 羖羊肉,\n"
            "主辟惡鬼, 虎狼, 止驚悸. 神羊乃冥府之神, 可剋陰陽兩界之鬼魔妖神.\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor": 4,
            "armor_vs_wind": 15,
            "armor_vs_lightning": 15,
        ]));
    }
    setup();
}
