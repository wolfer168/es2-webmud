/* 白玉腰帶 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一件；NPC 重生時
// 若它還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_WAIST_EQ;

void create()
{
    set_name("\x1b[1;37m白玉腰帶\x1b[m", ({ "white girth", "girth" }));
    set_weight(800);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 50000);
        set("long",
            "這是一條用整塊白玉彫刻而成的腰帶﹒精緻的手工，完全搭配上這塊\n"
            "白玉天然的花紋，可見雕刻者的用心﹒這條玉帶，是燕青雲送給梅影\n"
            "風的訂交之禮。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "wittiness": 30,
            "armor": 20,
            "cps": 2,
        ]));
    }
    setup();
}
