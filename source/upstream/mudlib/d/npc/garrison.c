// /d/npc/garrison.c — 各區域通用的官兵。
// 與 /d/snow/npc/garrison 相同，但不會攔人前往野羊山；
// 會攔人的那組專屬於雪亭鎮山路（/d/snow/ngate）。

#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("官兵", ({ "garrison" }) );
    set_race("human");
    set_class("soldier");
    set_level(15);

    set_skill("twohanded sword", 60);
    set_skill("blade", 50);

    set("long",
        "一位負責維護地方治安的官兵﹐他們受過相當的訓練﹐有時候\n"
        "也加入軍隊作戰。\n");
    set("vendetta_mark", "authority");
    set_power("B");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("broadsword") )->wield();
}

int accept_fight(object ob)
{
    do_chat((: command, "emote 瞪了瞪眼﹐說道﹕滾開滾開﹗少在這裡囉唆﹗":));
    return 0;
}
