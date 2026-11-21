// /d/baihua/npc/old_wang.c — 百花村 NPC：老王（依使用者設計表，2026-10-20）。
//
// 穹槍訣任務（使用者提供舊資料，2026-11-21；設計見 docs/martial_arts/穹槍訣.md「任務：老王尋妻」）：
// 玩家坐下聽完老王說故事、說願意幫忙；拿野熊的肉塊給他看，他不信，要玩家去找陳維俠；
// 再去五堂城隍廟問她姊姊，拿信回來；收下遺骨與化屍粉後，老王回贈血靈芝粉。
// 進度存在玩家身上，各自進行。

#include <npc.h>
inherit F_VILLAGER;
#include "/d/baihua/skypike_quest.h"

void create()
{
    seteuid(getuid());
    set_name("老王", ({ "old wang", "wang" }));
    set_race("human");
    set_class("commoner");
    set_level(1);
    set("gender", "male");
    set("age", 55);
    set("long", @LONG
百花村最德高望重的人，慈祥和藹的樣子背後藏著令人辛酸的往事。
LONG
    );
    set_power("C");
    setup();
}

// 玩家走進來，進度還沒開始就招呼他坐下（舊資料的第一句）。
void init()
{
    object who = this_player();

    ::init();
    if( !userp(who) || !living(this_object()) || is_fighting() || quest_busy ) return;
    if( sq_stage(who) == SQ_NONE && !who->query_temp(SQ_SAT) )
        call_out("greet", 1, who);
}

void greet(object who)
{
    if( sq_here(this_object(), who) && !quest_busy )
        command("say 坐呀，聽俺講故事喔！");
}

// 玩家在房裡坐下（房間的 sit）：進度還沒開始，就聽完故事；之後只得到一句慰問。
void tell_story(object who)
{
    if( quest_busy ) {
        tell_object(who, "老王正說著話，你不妨先聽他說完。\n");
        return;
    }
    if( sq_stage(who) != SQ_NONE || who->query_temp(SQ_SAT) ) {
        command("say 辛苦您了，歇會兒吧，別累壞了。");
        return;
    }
    who->set_temp(SQ_SAT, 1);
    sq_start(({
        "say 幾十年前啊，俺的家鄉水嵐縣洪水肆虐，俺的媳婦不小心被水捲走囉。",
        "say 俺那時年輕力壯，就四處去找啊！可惜俺東打聽西打聽，連個影兒也沒有。唉……",
        "emote 嚥了嚥口水，兩腳在地上磨來磨去，前前後後來回踱步。",
        "say 幾週後，俺打聽到這附近有人看到她的蹤影，俺一聽好高興，這老天爺還對咱們不薄，一家人終於能團圓啦。",
        "say 從此俺就在這兒開山破土，希望找回老婆，重組家園。",
        "say 就這樣，數十年如一日，俺老王可從沒放棄過希望，日日找，夜夜找。您可聞著這花香了吧，這兒的一花一草，可都是俺的心血啊。",
        "say 俺老婆最愛花朵囉，她一定會聞到這味兒找來這兒的，俺還是多種些香花美草，她一定會聞到的！",
        "emote 頓了頓，嘆了一口氣。",
        "say 唉……天不從人願，找來找去沒找著，不知有誰能幫幫俺這老頭子，俺的日子也不多了……",
    }), 0, who);
}

// 對老王說「幫忙」：聽完故事就答應幫忙；之後再說，依進度提點下一步。
void relay_say(object who, string msg)
{
    if( !userp(who) || !stringp(msg) || strsrch(msg, "幫") == -1 || quest_busy ) return;

    switch( sq_stage(who) ) {
    case SQ_NONE:
        if( !who->query_temp(SQ_SAT) ) {
            command("say 您要幫俺？先坐下來聽俺把話說完吧。");
            return;
        }
        who->set(SQ_STAGE, SQ_HELP);
        who->delete_temp(SQ_SAT);
        call_out("say_later", SQ_TICK, "say 您要幫俺？如果您找到俺媳婦兒，麻煩帶她來看俺，大恩不言謝。");
        break;
    case SQ_HELP:
        command("say 如果您找到俺媳婦兒，麻煩帶她來看俺，大恩不言謝。");
        break;
    case SQ_TO_CHEN:
        command("say 難不成這玩意兒得找陳仙人瞧瞧？");
        break;
    case SQ_TO_SIS:
        command("say 俺那婆娘的姊姊就住在五堂鎮，您去城隍廟問問她吧。");
        break;
    case SQ_LETTER:
        command("say 那封信，您可帶來了？");
        break;
    }
}

void say_later(string cmd) { command(cmd); }

// 收下玩家交來的東西：依進度；不對的東西或順序不收（default 的「並不願意收下」）。
int accept_object(object who, object ob)
{
    if( !userp(who) || quest_busy ) return 0;

    // 肉塊
    if( sq_is(ob, SQ_MEAT_FILE) ) {
        switch( sq_stage(who) ) {
        case SQ_NONE:
            command("emote 只顧著說故事，並沒有伸手接，你不妨坐下來聽聽 (sit)。");
            return 0;
        case SQ_HELP:
            who->set(SQ_STAGE, SQ_TO_CHEN);
            sq_start(({
                "emote 兩眼一瞪，緊張地看著你。",
                "say 甚麼，您說這……這是俺老婆？",
                "say 開甚麼玩笑，您瘋啦！",
                "say 難不成這玩意兒得找陳仙人瞧瞧？",
            }), 0, who);
            return 0;
        case SQ_TO_CHEN:
            command("say 這玩意兒俺不敢收，您去找陳仙人瞧瞧吧。");
            return 0;
        case SQ_CHEN:
            who->set(SQ_STAGE, SQ_TO_SIS);
            sq_start(({
                "emote 兩眼瞪著你，顫抖著說道：有大夫說這是六旬老婦？",
                "say 這……這也不見得就是俺可愛的老婆呀……不可能的……俺不相信……",
                "emote 臉上汗珠直滴。",
                "say 難不成得去五堂鎮，問她姊姊？",
            }), 0, who);
            return 0;
        case SQ_TO_SIS:
        case SQ_LETTER:
            command("say 這……俺還是不敢信，您先去問問她姊姊吧。");
            return 0;
        case SQ_BONE:
            who->set(SQ_STAGE, SQ_POWDER);
            call_out("sq_drop", 1, ob);
            sq_start(({
                "emote 小心翼翼地接過那塊遺骨。",
                "say 俺只有些吸水草，真不知要如何處理這未化的遺骨……",
            }), 0, who);
            return 1;
        }
        return 0;
    }

    // 信
    if( sq_is(ob, SQ_LETTER_FILE) ) {
        if( sq_stage(who) != SQ_LETTER ) return 0;
        who->set(SQ_STAGE, SQ_BONE);
        call_out("sq_drop", 1, ob);
        sq_start(({
            "emote 握著手上的信，聲淚俱下。",
            "say 這……想不到俺種花引她至此，竟反而害了她。",
            "emote 淚潸潸而下，抬頭望天大吼一聲。",
            "say 天意……天意……這就是天意嗎？",
            "emote 擦乾了眼淚。",
            "say 十分感激您來回奔波幫忙，可否將愛妻交還給俺？",
        }), 0, who);
        return 1;
    }

    // 化屍粉
    if( sq_is(ob, SQ_DUST_FILE) ) {
        if( sq_stage(who) == SQ_BONE ) {
            command("say 您先把俺老婆交給俺，再說這些。");
            return 0;
        }
        if( sq_stage(who) != SQ_POWDER ) return 0;
        if( ob->query_amount() > 1 ) {
            command("say 一包就夠了，其餘的請您收好。");
            return 0;
        }
        who->set(SQ_STAGE, SQ_MEDICINE);
        call_out("sq_drop", 1, ob);
        sq_start(({
            "emote 接過了這珍奇的藥粉，混合手上的吸水草，慢慢倒在那肉團上。",
            "emote 那塊血淋淋的肉塊發出嗤……嗤……的響聲，還冒了些甜甜的桂花香，漸漸越來越小，最後化為一堆紅色的粉末。",
            "emote 小心翼翼地把粉末掃入一個罐子裡，放入懷中。",
            "say 多虧了您幫忙，大恩大德永銘五內！",
            "say 俺只會種花種草，也沒別的相贈，此乃千年血靈芝粉，對刀劍外創有神效，請笑納。",
        }), "give_medicine", who);
        return 1;
    }
    return 0;
}

// 回贈血靈芝粉，老王抱著罐子走進內堂。
void give_medicine(object who)
{
    if( !objectp(who) ) return;
    sq_give(this_object(), who, SQ_MED_FILE);
    if( sq_here(this_object(), who) )
        command("emote 一邊細心地告訴你服藥的方法，一邊將一包紅色的東西遞給了你。");
    call_out("say_later", SQ_TICK, "emote 握著懷中的罐子，滿懷愁腸地轉身走入內堂。");
}
