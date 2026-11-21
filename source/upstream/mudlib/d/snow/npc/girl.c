// girl.c

#include <npc.h>

inherit F_FIGHTER;

object *dest = ({});

void create()
{
    set_name("白衣女子", ({ "girl" }) );
    set_race("human");
    set_class("fighter");
    set_level(25);

    set_skill("sword", 140);
    set_skill("dodge", 120);
    set_skill("parry", 120);
    set_skill("blade", 70);
    set_skill("dagger", 70);
    set_skill("unarmed", 90);
    set_skill("force", 80);
    set_skill("celestial force", 80);
    map_skill("force", "celestial force");
    set("defensive", 60);


    set("age", 19);
    set("gender", "female");
    set("long",
        "一個身穿白衣的女子﹐看起來年紀不會超過二十歲﹐容貌雖不甚美﹐卻\n"
        "別有一股靈秀之氣﹐令人凜然不敢輕侮。\n" );
    set_power("S");
    setup();
    carry_object(__DIR__"obj/white_dress")->wear();
    carry_object(__DIR__"obj/slasher_sword")->wield();
}

void relay_emote(object ob, string verb)
{
    do_chat((: command, "shake" :));
}

void attack_intruder(object ob)
{
    if( !ob || member_array(ob, dest)==-1 ) return;
    dest -= ({ ob });
    if( environment(ob) != environment() ) return;
    if( wizardp(ob) ) {
	command("say 原來是" + ob->name() + "大人，小女子適才冒犯，還請見諒。");
	return;
    }
    command("say 你真是不要命了﹗\n");
    kill_ob(ob);
    ob->fight_ob(this_object());
}

void listen_request(object ob)
{
    set("pending_requester", ob);
    command("hmm");
    command("say 你想要什麼﹖說吧。");
}

int accept_object(object who, object ob)
{
    if( ob->id("bronze hairpin") ) {
        command("say 這 ... 這是我的髮簪﹗還給我﹗");
        dest -= ({ who });
        if( is_fighting(who) ) {
            remove_killer(who);
            who->remove_killer(this_object());
        }
        do_chat( (: listen_request, who :) );
        call_out("drop_item", 1, ob);
        return 1;
    } else {
        command("say 這是什麼破銅爛鐵﹖拿開﹗");
        return 0;
    }
}

void drop_invitation()
{
    object ob;

    command("say 哼﹗我道是什麼﹖拿了快滾吧﹗");
    ob = new(__DIR__"obj/invitation");
    ob->move(this_object());
    command("drop invitation");
    delete("pending_requester");
}

void relay_say(object ob, string msg)
{
    if( ob==this_object() ) return;
    if( ob != query("pending_requester") ) 
        do_chat((: command, "say 這裡沒有你說話的餘地﹐給我閉嘴﹗":));
    else {
        if( msg!="英雄帖" ) {
            do_chat((: command, "say 這種東西我沒有﹐換一種﹗" :));
            return;
        }
        do_chat((: drop_invitation :));
    }
}

void init()
{
    ::init();
    if( this_player() && (!this_player()->query_temp("hairpin_quest")) ) {
        do_chat((: command, "say 你是誰﹖滾﹗滾出去﹗不然我殺了你﹗" :));
        if( member_array(this_player(), dest)==-1 ) {
            dest += ({ this_player() });
            call_out((: attack_intruder, this_player() :), 5);
        }
    }
}

/* 收下的東西刪掉，不留在身上（give 指令只會銷毀錢；使用者定案，2026-11-22）。 */
void drop_item(object ob)
{
    if( objectp(ob) && environment(ob) == this_object() ) destruct(ob);
}
