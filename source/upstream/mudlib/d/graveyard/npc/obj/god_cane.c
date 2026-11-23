/* 九曲十彎 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("九曲十彎", ({ "god cane", "staff" }));
    set_weight(21400);
    init_damage(4, 18, 225, 10, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("unit", "把");
        set("value", 40000);
        set("long",
            "青邪宮殘蟻師太的獨門兵器，是一根奇形怪狀的彎曲拐杖。\n");
        set("apply_weapon/twohanded staff", ([
            "force": 10,
            "str": 2,
        ]));
    }
    setup();
}
