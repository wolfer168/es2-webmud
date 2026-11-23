// /d/oldpine/npc/xue_biao.c — 老松林 NPC：土匪 徐彪（依老松林設計表）。

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
    set_name("徐彪", ({ "xue biaw", "xue", "biaw" }));
    set_race("yenhold");
    set_class("thief");
    set_level(20);
    set("title", "土匪");
    set("age", 40);
    set("long", @LONG
徐彪是老松林的土匪之一，因為在喬陰城裡犯下了不少案子，因此這一帶的
百姓都認得他，他的特徵是一條從額頭到鼻子的傷疤，不少痛恨他的百姓都
背地裡稱他「疤鼻子」。
LONG
    );
    // 擊殺者獲得戰場功勳。
    set("bounty", ([ "military service": 110 ]));
    set_power("B");
    setup();
    carry_object("/d/npc/obj/coarse_cloth")->wear();
    carry_object("/obj/area/obj/glaive")->wield();
    carry_object("/d/oldpine/npc/obj/head_cloth")->wear();
    carry_money("silver", 20);
}
