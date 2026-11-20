/* 黃雀寶劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一把；NPC 重生時
// 若它還在，NPC 就不會拿到；安懶道人（old_taoist）改帶桃木劍（2026-11-20）。
inherit F_UNIQUE;
inherit F_SWORD;

void create()
{
    set_name("黃雀寶劍", ({ "sword of raven", "sword" }));
    set_weight(2600);
    init_damage(1, 15, 40, 1, "sword");
    init_damage(1, 7, 40, 1, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 45000);
        set("long",
            "一把鏤刻著四十九隻黃雀的長劍，劍柄用黑鐵鑲著八個篆字：黃鐘泉冷，薦道以雀。\n");
        set("apply_weapon/sword", ([
            "spells": 15,
            "defense": 15,
        ]));
        set("apply_weapon/secondhand sword", ([
            "spells": 15,
            "defense": 15,
        ]));
    }
    setup();
}
