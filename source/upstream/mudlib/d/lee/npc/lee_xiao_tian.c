// 李家村事件「野羊山山賊洗劫李家村」的起點（設計見 docs/LEE_BANDIT_RAID.md）：
// 玩家 ask lee about 孝敬，聽完來龍去脈後說「幫忙」，他就請玩家到村子西邊與野羊山的人接頭。
// 說話用 say，每句間隔 1 tick（2 秒）。
#include <npc.h>
inherit F_VILLAGER;

#define RAID_D "/daemon/misc/lee_raid_d"
#define ASKING "lee_raid/asking"     // 李嘯天暫存：正在等誰回答「幫不幫忙」

// 愁眉苦臉在當鋪裡來回踱步，接著自言自語（事件進行中就不唸了）。
void pace()
{
    if( RAID_D->query_state() > 1 ) return;
    command("emote 愁眉苦臉，在當鋪裡來回踱步。");
    call_out("mutter", 2);
}

void mutter()
{
    if( RAID_D->query_state() > 1 ) return;
    command("say 這孝敬該給還是不該給....");
}

void create()
{
    set_name("李嘯天", ({ "lee xiao tian", "li xiao tian", "manager lee", "lee", "li", "xiao", "tian" }));
    set_race("human");
    set_class("fighter");
    set_level(20);
    set("age", 40);
    set("long", "李員外家的二總管為人精明，年少時好舞刀弄槍，被派任當鋪掌櫃之後，諸事都處理得緊緊有條。\n");
    // 平常愁眉苦臉地踱步、嘴裡唸著孝敬的事；約 5～7 tick 一次。
    set("chat_chance", 15);
    set("chat_msg", ({
        (: pace :),
        (: pace :),
        "李嘯天低頭翻著帳簿，偶爾撥動算盤珠。\n",
    }));
    set_power("B");
    setup();
    carry_object("/d/npc/obj/yellow_jade_ring")->wear();
    carry_object("/d/lee/npc/obj/willow_blade")->wield();
}

private int here(object who)
{
    return objectp(who) && environment(who) == environment();
}

// 依序說話：lines 每項是一個指令字串；全部說完後呼叫 after（可為 0）。
void play(object who, string *lines, int i, string after)
{
    if( !living(this_object()) ) return;
    if( i >= sizeof(lines) ) {
        if( stringp(after) && here(who) ) call_other(this_object(), after, who);
        return;
    }
    command(lines[i]);
    call_out("play", 2, who, lines, i + 1, after);
}

private void talk(object who, string *lines, string after)
{
    call_out("play", 2, who, lines, 0, after);
}

void accept_inquiry(object who, string key)
{
    int st;

    if( strsrch(key, "孝敬") == -1 ) return;
    st = RAID_D->query_state();
    if( st == 2 || st == 3 ) {
        talk(who, ({ "say 野羊山的人已經殺進村子裡了，快去幫忙！" }), 0);
        return;
    }
    if( st == 1 ) {
        talk(who, ({ "say 已經有人去跟他們接頭了，您先等等看。" }), 0);
        return;
    }
    talk(who, ({
        "say 原本這是我們的家事，不敢打擾" + who->rank("respectful"),
        "say 不過昨兒個當鋪招牌被射了一箭，上面還掛了封信",
        "say 信寫得狗屁不通，畫了堆錢寫孝敬，還畫了顆羊頭掛把刀",
        "say 一看就是野羊四傻... 不，野羊四傑的手筆",
        "say 不給怕出亂子，給了又怎麼跟李員外交代，又不好開口找人幫忙...",
    }), "wait_help");
}

// 說完來龍去脈，等玩家回答「幫忙」；一直不回答就不等了。
void wait_help(object who)
{
    set_temp(ASKING, who);
    remove_call_out("give_up");
    call_out("give_up", 60, who);
}

void give_up(object who)
{
    if( query_temp(ASKING) == who ) delete_temp(ASKING);
}

// 玩家說了「幫」字（幫忙、幫你、我幫）就算答應。
void relay_say(object who, string arg)
{
    if( query_temp(ASKING) != who || !stringp(arg) || strsrch(arg, "幫") == -1 ) return;
    delete_temp(ASKING);
    remove_call_out("give_up");
    who->set_temp("lee_raid/ok", 1);
    talk(who, ({
        "say 這... 就先謝過" + who->rank("respectful") + "，信裡要我到村子西邊與野羊山的好漢接頭",
        "say 至於後續如何還未有吩咐",
    }), 0);
}
