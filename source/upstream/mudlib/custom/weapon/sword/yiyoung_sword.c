/* 儀陽劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一把；NPC 重生時
// 若它還在，NPC 就不會拿到；正閒道長（taoist_master）改帶長劍（2026-11-20）。
inherit F_UNIQUE;
inherit F_SWORD;

void create()
{
    set_name("\x1b[1;30m儀陽劍\x1b[m", ({ "yiyoung sword", "sword" }));
    set_weight(7200);
    init_damage(3, 15, 100, 4, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 50000);
        set("long",
            "儀陽劍乃上清觀鎮觀之寶, 此劍透體淡墨, 利可削鐵, 乃一不可多見的神器!\n");
        set("apply_weapon/sword", ([
            "wis": 2,
            "spi": 2,
            "int": 2,
            "spell": 30,
        ]));
    }
    setup();
}
