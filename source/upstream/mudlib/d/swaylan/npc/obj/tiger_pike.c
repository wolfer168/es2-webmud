/* 虎鳴槍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("虎鳴槍", ({ "tiger pike", "pike" }));
    set_weight(7900);
    init_damage(4, 11, 100, 10, "pike");
    init_damage(4, 11, 100, 10, "secondhand pike");

    if( !clonep() ) {
        set("wield_as", ({ "pike", "secondhand pike" }));
        set("unit", "把");
        set("value", 10000);
        set("long",
            "一把黑黃相間的長槍，由於煉槍時採用虎骨加入槍身中，使的\n"
            "槍體格外的堅仞，槍體前方有數個小洞，揮舞起來會發出類似\n"
            "虎鳴的聲音，故稱為虎鳴槍。\n");
        set("apply_weapon/pike", ([
            "damage": 10,
        ]));
        set("apply_weapon/secondhand pike", ([
            "damage": 10,
        ]));
    }
    setup();
}
