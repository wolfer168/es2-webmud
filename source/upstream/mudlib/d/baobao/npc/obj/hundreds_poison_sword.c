/* 百鬒寒鳩劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;36m百鬒寒鳩劍\x1b[m", ({ "hundreds_poison sword", "sword" }));
    set_weight(3300);
    init_damage(2, 10, 50, 1, "sword");
    init_damage(2, 10, 50, 1, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 35000);
        set("long",
            "由特有的礦石所鑄成,經過七七四十九天,利用百種不同的毒葯練製。\n");
    }
    setup();
}

// 原資料「劇毒」：命中並造成傷害時上毒（見 daemon/condition/hundred_poison.c）。
void hit_ob(object me, object victim, int damage)
{
    if( victim->query("life_form") == "ghost" ) return;
    CONDITION_D("hundred_poison")->poison(victim, me);
}
