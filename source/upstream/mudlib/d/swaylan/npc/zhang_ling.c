// /d/swaylan/npc/zhang_ling.c — 水嵐縣 NPC：張齡（依水嵐縣設計表）。

/*
張齡自創幻劍術（virtual sword），設計見 docs/martial_arts/道士共通_幻劍術.md：
對他 say 幻劍術，或 ask zhang about 幻劍術 → 他談起這套劍術 → 傳授。
道士、人物等級與劍術都要夠（說出口的敘述不提數字）；每人只傳一次。
說話用 say、動作用 emote，一句一行不斷行（使用者指示，2026-11-14）。
*/
#include <ansi.h>
#include <npc.h>
inherit F_FIGHTER;

#define TAUGHT   "virtual_sword/taught"
#define BUSY     "teaching_virtual_sword"
#define KEYWORD  "幻劍術"

void create()
{
    seteuid(getuid());
    set_name("張齡", ({ "zhang ling", "zhang", "ling" }));
    set_race("human");
    set_class("taoist");
    set_level(30);
    set("gender", "male");
    set("age", 65);
    set("long", @LONG
一位鬚髮斑白的老者，腰間佩著一柄古劍，身上卻穿著道袍。據說他年輕時是個劍客，後來沉迷法術，竟將劍術與道法融為一爐，自創了一套幻劍術。
LONG
    );
    set_skill("unarmed", 60);
    set_skill("dodge", 60);
    set_skill("parry", 60);
    set_skill("sword", 60);
    set_power("B");
    setup();
    carry_object("/obj/area/obj/longsword")->wield();
    carry_object("/obj/area/obj/robe")->wear();
}

// ------------------------------------------------------------------
// 傳授幻劍術
// ------------------------------------------------------------------

private int still_here(object who)
{
    return objectp(who) && environment(who) == environment();
}

void play(object who, string *lines, int idx)
{
    if( !still_here(who) ) { delete_temp(BUSY); return; }
    if( idx >= sizeof(lines) ) {
        delete_temp(BUSY);
        if( who->query(TAUGHT) ) return;
        who->set(TAUGHT, 1);
        if( who->query_learn("virtual sword") < who->skill_threshold("virtual sword", 1) )
            who->improve_skill_exact("virtual sword",
                who->skill_threshold("virtual sword", 1) - who->query_learn("virtual sword"));
        tell_object(who, HIY "你學會了幻劍術。\n" NOR);
        return;
    }
    command(replace_string(lines[idx], "$N", who->name()));
    call_out("play", 2, who, lines, idx + 1);   // 說話之間停頓 1 tick（2 秒）
}

private void start_teach(object who)
{
    if( !objectp(who) || environment(who) != environment() ) return;
    if( who->query(TAUGHT) || who->query_learn("virtual sword") > 0
    ||  who->query_skill("virtual sword", 1) > 0 ) {
        command("say 幻劍術的門道老夫都說與你聽了﹐往後全看你自己的火候。");
        return;
    }
    if( query_temp(BUSY) ) {
        command("say 稍等﹐老夫正和人說話。");
        return;
    }
    if( who->query_class() != "taoist" ) {
        command("emote 瞥了" + who->name() + "一眼﹐淡淡一笑。");
        command("say 這是道門的法門﹐與你無緣。");
        return;
    }
    if( who->query_level() < 5 ) {
        command("emote 上下打量了" + who->name() + "一眼﹐搖了搖頭。");
        command("say 你的根基太淺﹐現在教你﹐只怕連劍訣都捏不穩﹐先去江湖上歷練歷練吧。");
        return;
    }
    if( who->query_skill("sword", 1) < 30 ) {
        command("emote 瞧了瞧" + who->name() + "的手﹐皺起眉頭。");
        command("say 你的劍術還不夠火候﹐連劍都使不順﹐如何放得出幻劍﹖先把劍練好再來。");
        return;
    }
    set_temp(BUSY, 1);
    play(who, ({
        "emote 撫著斑白的鬍鬚﹐上下打量了$N一番。",
        "say 幻劍術﹖那是老夫把一輩子的劍術與道法揉在一塊兒琢磨出來的玩意兒。",
        "say 劍不離手﹑咒不離口﹐咒聲一落﹐千百口幻劍便隨念而生﹐傷人於無形。",
        "emote 右手劍訣一領﹐腰間古劍錚然出鞘半寸﹐數道幻影一閃而逝。",
        "say 從十面埋伏﹑六陰六陽劍﹐到四九歸元﹑六十四爻誅殺訣﹐再到九九陽極幻劍﹐終至無極幻影﹐皆由此化出。",
        "emote 將幻劍術的口訣與運劍法門細細講解了一遍﹐$N在一旁凝神記下。",
    }), 0);
}

// say 幻劍術
void relay_say(object who, string arg)
{
    if( !stringp(arg) || strsrch(arg, KEYWORD) == -1 ) return;
    start_teach(who);
}

// ask zhang about 幻劍術
void accept_inquiry(object who, string key)
{
    if( !stringp(key) || strsrch(key, KEYWORD) == -1 ) return;
    start_teach(who);
}
