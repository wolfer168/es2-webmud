/* 紫雲玉珮 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一件；NPC 重生時
// 若它還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_WAIST_EQ;

void create()
{
    set_name("\x1b[1;35m紫雲玉珮\x1b[m", ({ "voliet jade", "jade" }));
    set_weight(800);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "個");
        set("value", 65000);
        set("long",
            "一個由相當罕見的紫雲玉所做成的玉珮，相傳這是紫雲宮歷代宮主才\n"
            "能配帶，玉珮上雕刻著鳳凰的圖案。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "spi": 2,
            "int": 1,
            "armor": 5,
            "defense": 20,
        ]));
    }
    setup();
}
