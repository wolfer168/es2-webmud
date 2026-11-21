// /d/wutang/npc/old_woman.c — 五堂鎮 NPC：老婦人（百花村老王妻子的姊姊，穹槍訣任務，2026-11-21）。
//
// 玩家把老王尋妻的事告訴她（對她說「老王」），她認出妹妹，寫一封信請玩家轉交妹夫。
// 設計見 docs/martial_arts/穹槍訣.md「任務：老王尋妻」；進度存在玩家身上，各自進行。

#include <ansi.h>
#include <npc.h>
inherit F_VILLAGER;
#include "/d/baihua/skypike_quest.h"

void create()
{
    seteuid(getuid());
    set_name("老婦人", ({ "old woman", "woman" }));
    set_race("human");
    set_class("commoner");
    set_level(1);
    set("gender", "female");
    set("age", 62);
    set("long", @LONG
一位鬢髮斑白的老婦人，手裡捻著幾炷清香，在香案前低頭默禱，神情中帶著說不出的哀戚。
LONG
    );
    // 約 5～7 tick 一次（每 tick 16% 機率）。
    set("chat_chance", 15);
    set("chat_msg", ({
        "老婦人拈著清香，在神像前深深拜了三拜，口中喃喃地不知在祈求些什麼。\n",
        "老婦人望著香案上裊裊升起的煙，輕輕嘆了一口氣。\n",
    }));
    set_power("C");
    setup();
    carry_object("/obj/area/obj/cloth")->wear();
}

// 對她說起老王：進度到了要找姊姊，她寫信；已經有信卻弄丟了（還在這個進度）就補一封。
void relay_say(object who, string msg)
{
    if( !userp(who) || !stringp(msg) || strsrch(msg, "老王") == -1 || quest_busy ) return;

    switch( sq_stage(who) ) {
    case SQ_TO_SIS:
        who->set(SQ_STAGE, SQ_LETTER);
        sq_start(({
            "emote 仔細聽完你說的老王妻子遺骸的事，嘆了一口氣，點了點頭。",
            "say 我妹妹以前常牙疼，只是都不跟老王訴苦，如果真是在血塊上發現右上牙蛀得深的話，那恐怕不會是別人了。",
            "say 唉……我可憐的妹子，嫁到王家沒幾年就遇上洪水，幾十年音訊全無，現在找到了，竟然是……唉。",
            "say 我寫封信，請你轉交我妹夫。",
            "emote 拿了張紙出來，提筆寫了幾行字。",
        }), "give_letter", who);
        break;
    case SQ_LETTER:
        if( present("letter to wang", who) ) {
            command("say 信不是已經交給你了嗎？快送去給我妹夫吧。");
            break;
        }
        sq_start(({
            "say 信弄丟了嗎？也難怪，我再寫一封給你。",
            "emote 拿了張紙出來，提筆寫了幾行字。",
        }), "give_letter", who);
        break;
    default:
        command("say 老王？我不認得這個人。");
    }
}

void give_letter(object who)
{
    if( !objectp(who) ) return;
    sq_give(this_object(), who, SQ_LETTER_FILE);
    if( sq_here(this_object(), who) )
        message_vision(CYN "$N交給$n一封信。\n" NOR, this_object(), who);
}
