// /d/lee/npc/bandit_scout.c — 野羊山探子（李家村事件「野羊山山賊洗劫李家村」，設計見 docs/LEE_BANDIT_RAID.md）。
//
// 躲在上山小路的暗處。聽了李嘯天交代、前來接頭的玩家走進來，他就跳出來盤問、討孝敬：
//   問完銀兩之後，玩家說任何話、或對他做任何表情，他再催一次；交出足夠的銀兩（give bandit N silver）
//   就放煙火通知山寨。問完 60 秒內沒交錢，就算失敗（由 raid_d 計時）。
// 說話用 say、神情用 emote，每句間隔 1 tick（2 秒）。
#include <npc.h>
#include <ansi.h>

inherit F_FIGHTER;

#define RAID_D "/daemon/misc/lee_raid_d"
#define TALK   "scout/talking"      // 暫存：正在對誰說開場白（避免重複觸發）
#define ASKED  "scout/asked"        // 暫存：問過銀兩、在等這位玩家回應
#define REPLY  "scout/replied"      // 暫存：玩家已經回應過了

void create()
{
    seteuid(getuid());
    set_name("野羊山探子", ({ "bandit scout", "scout", "bandit" }));
    set_race("human");
    set_class("thief");
    set_level(15);
    set("gender", "male");
    set("age", 24);
    set("long", "一個鬼鬼祟祟的漢子，縮著脖子躲在樹叢的暗處，賊眉鼠眼地四下張望，腰間掛著一把磨得發亮的短刀。\n");
    set_power("C");
    setup();
    carry_object("/d/lee/npc/obj/goat_blade")->wield("blade");
}

private int here(object who)
{
    return objectp(who) && environment(who) == environment();
}

// 價錢用中文：三千、四千……。
private string price_text(object who)
{
    return chinese_number(RAID_D->query_price(who));
}

private void fireworks();

// 依序做事：lines 每項是一個指令字串；全部做完後呼叫 after（可為 0）。
void play(object who, string *lines, int i, string after)
{
    if( !living(this_object()) ) return;
    if( i >= sizeof(lines) ) {
        if( stringp(after) && here(who) ) call_other(this_object(), after, who);
        return;
    }
    if( lines[i] == "@fireworks" ) fireworks();
    else command(lines[i]);
    call_out("play", 2, who, lines, i + 1, after);
}

private void talk(object who, string *lines, string after)
{
    call_out("play", 2, who, lines, 0, after);
}

// 帶著李嘯天的交代前來接頭的玩家走進來：跳出來盤問。
void init()
{
    object who = this_player();

    ::init();
    if( !userp(who) || !living(this_object()) ) return;
    if( !who->query_temp("lee_raid/ok") ) return;     // 沒聽過李嘯天交代的，他躲著不出聲
    if( RAID_D->query_state() != 0 ) return;          // 事件已經開了
    if( query_temp(TALK) ) return;
    set_temp(TALK, who);
    talk(who, ({
        "emote 從暗處跳了出來。",
        "say 此山是我開，此樹是我栽、若要過此路... 咦？",
        "emote 正盯著你看，不知道打些什麼主意。",
        "say 看你這副德行，你應該是李掌櫃派來的吧？",
    }), "ask_money");
}

// 問銀兩，同時開始 60 秒的計時。
void ask_money(object who)
{
    if( !here(who) || RAID_D->query_state() != 0 ) {
        delete_temp(TALK);
        return;
    }
    if( !RAID_D->begin_pay(who, this_object()) ) {
        delete_temp(TALK);
        return;
    }
    command("say 說好的" + price_text(who) + "兩白銀帶來了嗎？");
    set_temp(ASKED, who);
    delete_temp(REPLY);
}

// 玩家說了任何話：催他交錢。
void relay_say(object who, string arg)
{
    if( query_temp(ASKED) != who || query_temp(REPLY) ) return;
    set_temp(REPLY, 1);
    talk(who, ({ "say 還愣著幹甚麼？銀兩呢？" }), 0);
}

// 對探子做任何表情也一樣。
void relay_emote(object who, string verb)
{
    relay_say(who, verb);
}

// 交錢：只認開啟事件的那位玩家，而且要夠數。
int accept_object(object who, object ob)
{
    int price;

    if( !ob->query("money_id") ) {
        command("say 老子要的是銀子，誰要你這破玩意兒！");
        return 0;
    }
    if( query_temp(ASKED) != who || RAID_D->query_state() != 1 ) {
        command("say 沒你的事，一邊涼快去！");
        return 0;
    }
    price = RAID_D->query_price(who) * 100;     // 價錢以兩銀計，錢的 value() 以文計
    if( ob->value() < price ) {
        command("say 這點錢也想打發老子？當老子是叫化子嗎！");
        return 0;
    }

    delete_temp(ASKED);
    delete_temp(REPLY);
    RAID_D->paid(who);
    who->delete_temp("lee_raid/ok");
    talk(who, ({
        "say 老子收都收了，不給點回禮倒顯得小氣了",
        "emote 「嘿嘿嘿....」地奸笑了幾聲。",
        "@fireworks",
    }), "after_signal");
    return 1;
}

// 放煙火通知山寨：全頻廣播（沒有頻道標籤、玩家無法關掉），整句一行不斷行。
private void fireworks()
{
    message("system",
        HIG "「砰」的一聲，一枚青綠色的煙火在空中迸射開來，化成了一顆羊頭的形狀。\n" NOR,
        users());
    RAID_D->signal_sent();
}

void after_signal(object who)
{
    delete_temp(TALK);
}

// 超過 60 秒沒交錢：任務失敗，要重新來過。
void pay_failed()
{
    object who = query_temp(ASKED);

    delete_temp(ASKED);
    delete_temp(REPLY);
    delete_temp(TALK);
    if( objectp(who) ) who->delete_temp("lee_raid/ok");
    command("say 耍老子是吧？回去告訴你們掌櫃，這事沒完！");
    command("emote 啐了一口，轉身鑽進樹叢裡不見了。");
}
