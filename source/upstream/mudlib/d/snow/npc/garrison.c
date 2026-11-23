// 會攔人前往野羊山的官兵，專屬於雪亭鎮山路（/d/snow/ngate）。
// 其他地方要放官兵，請用不會攔人的 /d/npc/garrison。


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

void init()
{
    ::init();
    add_action("intercept", "go");
}

int intercept(string arg)
{
    if( (arg!= "north") || !this_player()->visible(this_object()) ) return 0;

    if( this_player()->query_level() >= 10 ) return 0;
    write( name() + "將你攔了下來。\n");
    do_chat((: command, "say 野羊山最近有盜匪出沒﹐你們走別條路吧。":) );
    return 1;
}

int accept_fight(object ob)
{
    do_chat((: command, "emote 瞪了瞪眼﹐說道﹕滾開滾開﹗少在這裡囉唆﹗":));
    return 0;
}

