/* 烏讎劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("烏讎劍", ({ "sword of black justice", "sword" }));
    set_weight(7900);
    init_damage(3, 16, 120, 6, "sword");
    init_damage(3, 16, 120, 6, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 150000);
        set("long",
            "這是奐族名匠齊龍國師所鑄的一把寶劍﹐名喚「烏讎」﹐此劍通體烏黑\n"
            "﹐但是鋒利無比﹐據說這把劍藏有一個大祕密﹐和奐族所信仰的天靈神\n"
            "有關﹐但即使不知道這個祕密﹐這把劍仍然是十分罕見的利器。\n");
        set("apply_weapon/sword", ([
            "str": 1,
            "cor": 1,
        ]));
        set("apply_weapon/secondhand sword", ([
            "str": 1,
            "cor": 1,
        ]));
    }
    setup();
}
