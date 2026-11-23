// /d/baihua/npc/kao_yeu.c — 百花村 NPC：「穿雲槍」高玉（依使用者設計表，2026-10-20）。

#include <npc.h>
#include <ansi.h>
inherit F_FIGHTER;
#include "/d/baihua/skypike_quest.h"

void create()
{
    seteuid(getuid());
    set_name("高玉", ({ "kao yeu", "kao", "yeu" }));
    set_race("human");
    set_class("fighter");
    set_level(35);
    set("gender", "male");
    set("age", 35);
    set("long", @LONG
高玉是江湖上小有名氣的槍法好手，一桿長槍使得出神入化，人稱「穿雲槍」。此刻他倚著岩壁坐在平台一角，衣襟上血跡斑斑，臉色蒼白，胸口纏著的布條還隱隱滲出血來，顯然受了不輕的傷，只是一雙眼睛依舊銳利，始終緊握著手中的長槍。
LONG
    );
    set("nickname", "穿雲槍");
    set_skill("sky_pike", 105);
    set_power("B");
    setup();
    carry_object("/d/baihua/npc/obj/dragon_bone_pike")->wield();
    carry_object("/d/npc/obj/golden_feather_helm")->wear();
    carry_object("/d/baihua/npc/obj/ringmail")->wear();
    carry_object("/d/npc/obj/forgod_boots")->wear();
}

// 穹槍訣任務的終點（設計見 docs/martial_arts/穹槍訣.md）：收下血靈芝粉，傷癒後傳授穹槍訣；
// 已學過的人改送一顆武魁龍轉。高玉演完就爬上去離開，下次房間重置才回來。
void leave();

int accept_object(object who, object ob)
{
    int learned;

    if( !userp(who) || quest_busy || !sq_is(ob, SQ_MED_FILE) || sq_stage(who) != SQ_MEDICINE )
        return 0;
    who->delete(SQ_STAGE);
    call_out("sq_drop", 1, ob);
    learned = !undefinedp(who->query_skills()["sky_pike"]);
    sq_start(({
        "emote 一手攙著你的肩膀，小心翼翼地接過血靈芝粉。",
        "emote 服下了藥，兩腿盤坐引氣調息，臉色逐漸轉為紅潤。",
        "emote 突然大吼一聲，跳了起來。",
        "say 有效，果真有效！",
        "emote 說著說著狂笑了起來。",
        "emote 拱手作揖。",
        "say 感謝這位壯士，救命之恩難以報答。",
        learned ? "say 在下這點槍法，壯士早已學成，也沒什麼能再傳授的了，這顆藥丸請您收下。"
                : "say 在下這槍法亦敢稱槍中之神，便傳授與您，盼於恩人有助。",
    }), learned ? "give_pill" : "teach", who);
    return 1;
}

void teach(object who)
{
    if( objectp(who) ) {
        who->improve_skill_exact("sky_pike", 1);
        if( sq_here(this_object(), who) )
            tell_object(who, CYN "(高玉匆匆演示了一遍穹槍訣，你記下了基本的招式)\n" NOR);
    }
    leave();
}

void give_pill(object who)
{
    if( objectp(who) ) {
        sq_give(this_object(), who, SQ_PILL_FILE);
        if( sq_here(this_object(), who) )
            message_vision(CYN "$N交給$n一顆武魁龍轉。\n" NOR, this_object(), who);
    }
    leave();
}

// 爬上峭壁離開；房間下次重置（reborn）時再補一個高玉。
void leave()
{
    sq_start(({
        "say 老匹夫，我高玉又來啦！",
        "emote 往上一縱，攀著峭壁爬走了。",
    }), "go_away", 0);
}

void go_away(object who)
{
    destruct(this_object());
}
