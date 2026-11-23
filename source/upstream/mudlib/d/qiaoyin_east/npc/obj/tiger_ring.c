/* 虎紋戒指 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一件；NPC 重生時
// 若它還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[0;33m虎紋戒指\x1b[m", ({ "tiger ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 120000);
        set("long",
            "一枚黃黑相間的虎紋戒指, 戒指的側邊有著一道明顯的裂痕。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "damage": 10,
            "attack": 20,
            "dex": 2,
        ]));
    }
    setup();
}
