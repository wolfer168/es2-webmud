/* 長刀僉白 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一把；NPC 重生時
// 若這把刀還在，NPC 就不會拿到；褚商魂（chu_xang_when）改帶百鬼刀（2026-11-20）。
inherit F_UNIQUE;
inherit F_BLADE;

void create()
{
    set_name("\x1b[1;37m長刀僉白\x1b[m", ({ "white blade", "blade" }));
    set_weight(9200);
    init_damage(3, 20, 110, 4, "blade");

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 50000);
        set("long",
            "這是喬陰四隱之一的「饜血刀」張律年輕時所使的兵刃﹐後來送給了\n"
            "他的女婿雪吟莊的褚商魂﹐這把刀的刀刃散發著一股異樣的白色光暈\n"
            "令人無法逼視。\n");
        set("apply_weapon/blade", ([
            "damage": 30,
            "cps": 4,
        ]));
    }
    setup();
}
