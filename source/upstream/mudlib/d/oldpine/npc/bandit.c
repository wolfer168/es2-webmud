// /d/oldpine/npc/bandit.c — 老松林 NPC：土匪（依老松林設計表）。

#include <npc.h>

inherit F_FIGHTER;


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
    set_name("土匪", ({ "bandit" }));
    set_race("human");
    set_class("thief");
    set_level(10);
    set("age", 30);
    set("long", @LONG
滿臉橫肉看起來一副凶神惡煞的樣子。
LONG
    );
    set_skill("blade", 20);
    set_skill("dodge", 20);
    set_skill("parry", 20);
    set_skill("unarmed", 20);
    // 擊殺者獲得戰場功勳。
    set("bounty", ([ "military service": 15 ]));
    set_power("C");
    setup();
    carry_object("/obj/area/obj/blade")->wield();
    carry_object("/d/oldpine/npc/obj/leather_vest")->wear();
    carry_money("silver", 5);
}
