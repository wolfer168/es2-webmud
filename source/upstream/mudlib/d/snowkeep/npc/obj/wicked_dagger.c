/* 「雨毒」 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一把；NPC 重生時
// 若它還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_DAGGER;

void create()
{
    set_name("\x1b[1;34m「雨毒」\x1b[m", ({ "wicked dagger", "dagger" }));
    set_weight(7600);
    init_damage(3, 15, 80, 7, "dagger");
    init_damage(3, 15, 80, 7, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 30000);
        set("long",
            "一把不到三寸的短匕首，上面雕著一些漩渦狀的花紋寒光閃閃，當你的手\n"
            "一靠近這把匕首，就覺得手上的汗毛一根跟都豎了起來。\n");
        set("apply_weapon/dagger", ([
            "damage": 10,
            "killerhood": 15,
            "attack": 30,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "damage": 10,
            "killerhood": 15,
            "attack": 30,
        ]));
    }
    setup();
}

// 劇毒：命中並造成傷害時上毒（見 daemon/condition/rain_poison.c）。
void hit_ob(object me, object victim, int damage)
{
    if( victim->query("life_form") == "ghost" ) return;
    CONDITION_D("rain_poison")->poison(victim, me);
}
