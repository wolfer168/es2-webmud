// /d/oldpine/npc/wild_bear.c — 迷霧森林／老松林 野獸：凶暴的野熊（強度 7，野豬為 4）。

#include <npc.h>

// 看到玩家就下殺手（kill），玩家昏倒後也會繼續攻擊直到死亡。
void init()
{
    object ob = this_player();

    ::init();
    if( objectp(ob) && userp(ob) && living(this_object()) && !is_fighting(ob)
    &&  !environment()->query("no_fight") && visible(ob) ) {
        kill_ob(ob);
    }
}

void create()
{
    seteuid(getuid());
    set_name("凶暴的野熊", ({ "bear", "wild bear" }));
    set_race("beast");
    set_class("commoner");
    set_level(1);
    set("long", @LONG
體型壯碩的大熊，且不知為何異常兇暴。
LONG
    );
    set("unit", "頭");
    set("beast_actions", ({
        ([ "action": "$N人立而起，揮掌往$n的$l拍去", "damage_type": "瘀傷" ]),
        ([ "action": "$N張開血盆大口往$n的$l咬去", "damage_type": "咬傷" ]),
        ([ "action": "$N龐大的身軀往$n的$l猛撞過去", "damage_type": "瘀傷" ])
    }));
    // 野獸強度（1～10），數值見 daemon/race/beast.c。
    set_beast(7);
    setup();
    carry_object("/d/npc/obj/meat");
}
