/* 附骨之蛆 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一把；NPC 重生時
// 若它還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_NEEDLE;

void create()
{
    set_name("\x1b[1;30m附骨之蛆\x1b[m", ({ "needle of bone maggot", "needle" }));
    set_weight(500);
    init_damage(3, 15, 100, 10, "needle");

    if( !clonep() ) {
        set("wield_as", "needle");
        set("unit", "把");
        set("value", 100000);
        set("long",
            "一支銀鐵色的細長灸針, 針頭上傳來濃厚的藥味...\n");
        set("apply_weapon/needle", ([
            "attack": 20,
            "kee anatomy": 20,
        ]));
    }
    setup();
}

// 劇毒：命中並造成傷害時上毒（見 daemon/condition/maggot_poison.c）。
void hit_ob(object me, object victim, int damage)
{
    if( victim->query("life_form") == "ghost" ) return;
    CONDITION_D("maggot_poison")->poison(victim, me);
}
