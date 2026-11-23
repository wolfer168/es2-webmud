/* 虛靈劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一把；NPC 重生時
// 若它還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_SWORD;

void create()
{
    set_name("虛靈劍", ({ "numinous sword", "sword" }));
    set_weight(7200);
    init_damage(3, 15, 100, 4, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 55000);
        set("long",
            "古奇劍就一直歸『紫衣派』所有﹐被當作是鎮門密寶﹐一般弟子尚不可隨意接\n"
            "近此劍。\n");
        set("apply_weapon/sword", ([
            "wis": 2,
            "parry": 20,
            "taoism-thunder": 15,
            "armor": 20,
        ]));
    }
    setup();
}
