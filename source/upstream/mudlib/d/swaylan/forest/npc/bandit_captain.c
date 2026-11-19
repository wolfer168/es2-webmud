// /d/swaylan/forest/npc/bandit_captain.c — 密林 NPC：大統領（依水嵐縣設計表第五批，docs/AREA_SWAYLAN.md）。

// 迅雷斧法任務（2026-11-19，docs/martial_arts/共通_迅雷斧法.md）：把振武軍營魯熙年的精鋼砍刀交給他，
// 他認出是仇人的兵器、問玩家是不是幹掉了魯熙年；玩家肯定回答後，他豪邁地傳授迅雷斧法。
// 說話用 say、神情用 emote，每句間隔 1 tick（2 秒）。
#include <npc.h>
#include <ansi.h>
inherit F_FIGHTER;

#define BLADE  "/custom/weapon/blade/steelblade"
#define ASKING "soonlight/asking"     // 大統領暫存：正在等誰回答
#define HOLD   "soonlight/blade"      // 大統領暫存：暫時收著的砍刀

void create()
{
    seteuid(getuid());
    set_name("大統領", ({ "bandit captain", "captain" }));
    set_race("headless");
    set_class("fighter");
    set_level(40);
    set("age", 35);
    set("long", @LONG
一個身形魁梧的形天，雙手各握一柄大斧，渾身筋肉虯結，一開口便是震耳欲聾的大嗓門。據說他與振武軍的魯熙年有不共戴天之仇。
LONG
    );
    set_skill("axe", 80);
    set_skill("secondhand axe", 80);
    set_skill("dodge", 80);
    set_skill("parry", 80);
    set_skill("unarmed", 80);
    // 罵魯熙年、官兵與這鳥地方；約 5～7 tick 說一句。
    set("chat_chance", 15);
    set("chat_msg", ({
        "大統領一斧劈在桌上：「魯熙年那個王八蛋，總有一天老子要親手剁了他！」\n",
        "大統領罵道：「官兵算什麼東西，有種就進林子裡來！」\n",
        "大統領恨恨地說：「老子堂堂好漢，竟要龜縮在這鳥地方！」\n",
    }));
    set("bounty", ([ "military service": 750 ]));
    set_power("A");
    setup();
    carry_object("/custom/weapon/axe/large_axe")->wield();
    carry_object("/custom/weapon/axe/dragon_tiger_axe")->wield("secondhand axe");   // 青龍白虎斧
    carry_money("silver", 5 + random(26));
}

// ------------------------------------------------------------------
// 迅雷斧法任務
// ------------------------------------------------------------------

private int still_here(object who)
{
    return objectp(who) && environment(who) == environment();
}

// 依序說話：lines 每項是一個指令字串；全部說完後呼叫 after（可為 0）。
void play(object who, string *lines, int i, string after)
{
    if( !living(this_object()) ) return;
    if( i >= sizeof(lines) ) {
        if( stringp(after) && still_here(who) ) call_other(this_object(), after, who);
        return;
    }
    command(lines[i]);
    call_out("play", 2, who, lines, i + 1, after);
}

private void talk(object who, string *lines, string after)
{
    call_out("play", 2, who, lines, 0, after);
}

// 問玩家：「那就是說……」，等玩家肯定回答。
void ask_kill(object who)
{
    if( !still_here(who) ) return;
    set_temp(ASKING, who);
    call_out("give_up", 60, who);   // 一直不回答就不等了，把砍刀還給對方
}

void give_up(object who)
{
    object ob = query_temp(HOLD);

    if( query_temp(ASKING) != who ) return;
    delete_temp(ASKING);
    delete_temp(HOLD);
    if( !objectp(ob) ) return;
    command("emote 等得不耐煩，把精鋼砍刀往地上一扔。");
    ob->move(environment());
}

int accept_object(object who, object ob)
{
    if( base_name(ob) != BLADE ) return 0;
    if( query_temp(ASKING) ) {
        command("say 沒看見老子正忙著嗎？待會兒再說！");
        return 0;
    }
    if( who->query_skill("soonlight axe", 1) > 0 ) {
        command("say 這刀看著眼熟，可老子的斧法你不是早就學去了嗎？留著它自己砍人去！");
        return 0;
    }
    set_temp(HOLD, ob);
    talk(who, ({ "emote 接過精鋼砍刀，在手裡掂了掂，忽然放聲大笑，震得密道頂上的碎土簌簌直落。",
                 "say 這不是魯熙年那傢伙的武器嗎？既然在你手上，那就是說……",
                 "emote 笑聲戛然而止，似笑非笑地斜眼看著你。" }), "ask_kill");
    return 1;
}

// 玩家回答：說「是」「對」「沒錯」「殺了」之類（不含「不是」「沒有」）都算肯定。
private int positive(string arg)
{
    if( !stringp(arg) ) return 0;
    if( strsrch(arg, "不") != -1 || strsrch(arg, "沒有") != -1 || strsrch(arg, "沒殺") != -1 ) return 0;
    foreach( string w in ({ "是", "對", "沒錯", "正是", "不錯", "殺了", "宰了", "幹掉", "當然", "嗯", "恩", "yes", "Yes" }) )
        if( strsrch(arg, w) != -1 ) return 1;
    return 0;
}

private void answered(object who, int yes)
{
    object ob = query_temp(HOLD);

    remove_call_out("give_up");
    delete_temp(ASKING);
    if( !yes ) {
        set_temp(ASKING, who);
        call_out("give_up", 60, who);
        talk(who, ({ "emote 眼睛一瞪，鼻孔裡重重哼了一聲。",
                     "say 少跟老子支支吾吾，想清楚了再回話！" }), 0);
        return;
    }
    delete_temp(HOLD);
    if( objectp(ob) ) destruct(ob);
    talk(who, ({ "emote 仰天大笑，笑得連桌上的酒碗都跳了起來。",
                 "say 好！痛快！魯熙年那個王八蛋也有今天！",
                 "say 老子這套斧法專劈官兵的狗頭，今天就傳給你這條好漢！",
                 "emote 抄起雙斧在大廳裡舞得風雷滾滾，斧光翻飛，一邊舞一邊扯著嗓子講解訣竅。" }),
         "teach_axe");
}

// 傳授迅雷斧法：補足到剛好學成。
void teach_axe(object who)
{
    string skill = "soonlight axe";

    if( !still_here(who) ) return;
    if( who->query_skill(skill, 1) <= 0
    &&  SKILL_D(skill)->valid_learn(who) ) {
        tell_object(who, CYN "大統領將迅雷斧法的身法與運斧要訣，連吼帶比劃地全教給了你。\n" NOR);
        who->improve_skill_exact(skill, who->skill_threshold(skill, 1) - who->query_learn(skill));
    }
    talk(who, ({ "say 學會了就別給老子藏著掖著，出了林子多砍些官兵！",
                 "say 那幫狗娘養的王八蛋、軟腳龜孫子，一個也別給他們留全屍！" }), 0);
}

void relay_say(object who, string arg)
{
    if( query_temp(ASKING) != who ) return;
    if( positive(arg) ) answered(who, 1);
    else if( strsrch(arg, "不") != -1 || strsrch(arg, "沒") != -1 ) answered(who, 0);
}

void relay_emote(object who, string verb)
{
    if( query_temp(ASKING) != who ) return;
    if( member_array(verb, ({ "nod", "smile", "grin", "bow", "agree", "ya", "sm" })) != -1 ) answered(who, 1);
    else if( verb == "shake" ) answered(who, 0);
}
