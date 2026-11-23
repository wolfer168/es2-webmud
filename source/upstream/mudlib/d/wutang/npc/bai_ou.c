/*---
description: 五堂鎮 NPC：白甌（鳳娘）。昔日宮裡的繡娘，替玩家把布衣繡出花樣，也替袋子繡上題名的籤牌。
design: docs/EMBROIDERY.md（使用者指示，2026-11-13）
rule: - 玩家對她說「繡花」開始；先給工錢（五兩黃金＝50000 文以上，多給不找，不足不收、不可分次），
        再給布衣（名稱叫「布衣」的三個物品檔：/obj/area/obj/cloth、/obj/armor/cloth、/obj/cloth）；順序錯、給錯東西、給繡過的衣服都不收。
      - 收下布衣後原布衣銷毀（give 時店家收下有價值的物品會自動銷毀），1 tick 後產生新的繡花布衣
        （obj/area/obj/embroidered_cloth.c）交給玩家，繡花結果在那個檔案裡擲。
      - 玩家中途走開，繡好的衣服就沒了；白甌被殺，製作中斷，錢與布衣都不補。
      - 每位玩家各自進行（進度記在白甌身上，不記在玩家身上）。
      - 繡袋子（使用者指示，2026-11-24）：工錢五兩以上、不到十兩是繡衣服，十兩以上（100000 文）是繡袋子。
        只收龍麟袋與太古塵包，袋子要先倒空；收下後原袋銷毀，給付錢者新的 *_bag_plus 包包（名稱、ID 不變，可題名）。
        付了繡衣服的錢給袋子、付了繡袋子的錢給布衣都不收，工錢留著；繡過的袋子不收。
---*/

#include <ansi.h>
#include <npc.h>
inherit F_VILLAGER;

#define FEE         50000                       // 五兩黃金（文）
#define TICK        2                           // 一個 tick 的秒數
#define EMBROIDER_TICKS 1                       // 收下布衣後幾個 tick 繡好
// 名稱叫「布衣」（id cloth）的三個物品檔都能繡（使用者指示，2026-11-16）。
#define CLOTH_FILES ({ "/obj/area/obj/cloth", "/obj/armor/cloth", "/obj/cloth" })
#define EMBROIDERED_FILE "/obj/area/obj/embroidered_cloth"
#define BAG_FEE     100000                      // 十兩黃金（文）：繡袋子
// 能繡的袋子 → 繡好後給的新包包（使用者指示，2026-11-24）。
#define BAG_FILES ([ "/custom/item/dragon_skin_bag" : "/custom/item/dragon_skin_bag_plus", \
                     "/custom/item/ancient_bag"     : "/custom/item/ancient_bag_plus" ])

#define PAID_CLOTH  1                           // 付的是繡衣服的工錢
#define PAID_BAG    2                           // 付的是繡袋子的工錢

mapping paid = ([]);                            // 已付工錢、等著交東西的玩家（值是 PAID_CLOTH 或 PAID_BAG）

void create()
{
    seteuid(getuid());
    set_name("白甌", ({ "bai ou", "bai", "ou" }));
    set("nickname", "鳳娘");
    set_race("human");
    set_class("commoner");
    set_level(5);
    set("gender", "female");
    set("age", 38);
    set("long", @LONG
一位身著月白繡裙的婦人，指尖拈著一縷細如蠶絲的絲線，眉間靜如止水。傳聞她昔年是宮裡最得寵的繡娘，龍袍鳳帔皆出其手，如今卻不知為何歸於五堂鎮，在這間布莊裡執針度日。蘇繡之細、湘繡之神、粵繡之華、蜀繡之嚴，到了她指下渾然一體，早已別開一派。
LONG
    );
    set_skill("unarmed", 10);
    set_skill("dodge", 10);
    set_skill("parry", 10);
    // 約 5～7 tick 說一句（每 tick 16% 機率）。
    set("chat_chance", 15);
    set("chat_msg", ({
        "白甌執針穿線，素指翻飛，繡繃上的花樣漸漸有了形狀。\n",
        "白甌將絲線湊近唇邊輕輕一抿，劈作更細的幾縷。\n",
        "白甌輕聲自語：「尋常的布衣，若肯繡花，也能別有一番風致。」\n",
        "白甌抬眼望向遠處，不知想起了什麼，半晌才又低下頭去，繼續手上的針線。\n",
    }));
    set_power("C");
    setup();
}

/* ---- 說話與給東西 ------------------------------------------------- */
// 白甌說的話照 say 的格式：「白甌說道﹕」加綠色內容（使用者指示，2026-11-13）；
// 動作的描述用表情的青色。

// 白甌說話：verb 是完整的說話動詞，例如「說道」「笑道」「接著說道」。
void talk(string verb, string text)
{
    message_vision("$N" + verb + "﹕" + HIG + text + NOR + "\n", this_object());
}

// pre 是「說道」前面的動作（可空），例如 "笑著" → 「白甌笑著說道﹕…」。
void speak(string pre, string text)
{
    talk(pre + "說道", text);
}

// 動作描述（青色，同表情）。
void act(string msg, object who)
{
    message_vision(CYN + msg + NOR + "\n", this_object(), who);
}

void invite(object who)
{
    if( !objectp(who) || environment(who) != environment() ) return;
    if( paid[who] == PAID_BAG ) {
        speak("", "工錢我已收下了，把袋子拿來吧 (give bag to bai ou)。");
        return;
    }
    if( paid[who] ) {
        speak("", "工錢我已收下了，把布衣拿來吧 (give cloth to bai ou)。");
        return;
    }
    act("$N擱下手中的繡繃，抬眸淡淡一笑。", who);
    // 一行放不下，分成幾句說（遊戲每行 70 格，綠色碼也佔格數）。
    speak("", "繡花嗎？難得有人識貨。");
    speak("接著", "只要工錢五兩黃金，我為你的布衣繡上幾針；");
    speak("又", "十兩黃金，便替你的袋子繡個記號。");
    talk("笑道", "記得先付工錢、後交衣裳，這是繡坊一直以來的規矩。");
}

void relay_say(object who, string msg)
{
    if( !userp(who) || !stringp(msg) || strsrch(msg, "繡花") == -1 ) return;
    call_out("invite", 1, who);
}

// 給東西：傳回 1 才算收下（收下有價值的東西，give 會把它銷毀）。
int accept_object(object who, object ob)
{
    if( !userp(who) ) return 0;

    if( ob->query("money_id") ) {
        if( paid[who] == PAID_BAG ) {
            speak("", "工錢已經付過了，袋子呢？");
            return 0;
        }
        if( paid[who] ) {
            speak("", "工錢已經付過了，是哪件布衣想刺繡呢？");
            return 0;
        }
        if( ob->value() < FEE ) {
            talk("笑道", "五兩黃金，少一文也不成。");
            return 0;
        }
        if( ob->value() >= BAG_FEE ) {
            paid[who] = PAID_BAG;
            call_out("speak", 0, "笑著", "十兩黃金……是要繡袋子吧？拿來讓我瞧瞧。");
            return 1;
        }
        paid[who] = PAID_CLOTH;
        call_out("speak", 0, "笑著", "衣裳呢？取來讓我瞧瞧");
        return 1;
    }

    // 繡過的袋子不收（使用者指示，2026-11-24）。
    if( ob->query("bag_embroidered") ) {
        speak("", "這我已經改過了。");
        return 0;
    }
    // 龍麟袋、太古塵包：要付繡袋子的工錢，袋子要倒空。
    if( !undefinedp(BAG_FILES[base_name(ob)]) ) {
        if( !paid[who] ) {
            act("$N愉快地對著$n微笑著。", who);
            return 0;
        }
        if( paid[who] != PAID_BAG ) {
            speak("", "繡袋子的工錢是十兩黃金，五兩只夠繡一件布衣。");
            return 0;
        }
        if( sizeof(all_inventory(ob)) ) {
            speak("", "袋裡還裝著東西，先騰空了再拿來。");
            return 0;
        }
        map_delete(paid, who);
        call_out("begin_bag", 0, who, ob, BAG_FILES[base_name(ob)]);
        return 1;
    }

    if( ob->query("embroidered") ) {
        speak("蹙眉", "這件已有人下過針了，我不願在別人的針腳上再添一筆。");
        return 0;
    }
    if( member_array(base_name(ob), CLOTH_FILES) < 0 ) {
        if( paid[who] == PAID_BAG )
            speak("", "這回收的是繡袋子的工錢，我只繡龍麟袋與太古塵包。");
        else
            speak("", "我的針只為布衣 (cloth) 而動，這東西，恕我不繡。");
        return 0;
    }
    if( !paid[who] ) {
        // 還沒付工錢就遞衣裳：不說話，只是微笑（衣裳退回）。
        act("$N愉快地對著$n微笑著。", who);
        return 0;
    }
    if( paid[who] == PAID_BAG ) {
        speak("", "這回收的是繡袋子的工錢，我只繡龍麟袋與太古塵包。");
        return 0;
    }

    map_delete(paid, who);
    call_out("begin", 0, who, ob);      // 等 give 把衣裳交到手上，再銷毀它
    return 1;
}

/* ---- 繡花 ---------------------------------------------------------- */

// 收下的布衣直接銷毀，不留在白甌身上（使用者指示，2026-11-14）。
// 布衣的 value() 查不到價錢，give 不會自動銷毀它，所以這裡自己銷毀。
void begin(object who, object cloth)
{
    if( objectp(cloth) ) destruct(cloth);
    act("$N接過$n遞來的布衣，銀針在布面上起落如蝶，轉眼已見雲紋隱隱。", who);
    call_out("finish", EMBROIDER_TICKS * TICK, who);
}

// 繡花結果對應的一句話（結果代號見 embroidered_cloth.c）。
private string result_line(int result)
{
    switch(result) {
    case 1: return "針腳裡藏了幾分靈氣，穿著它，人也精神些。";
    case 2: return "這一路針法帶著鋒芒，出手時自有幾分銳氣。";
    case 3: return "今日心緒有些浮，針腳走偏了鋒芒，莫怪於我。";
    case 4: return "密針織成屏障，尋常刀兵難近。";
    case 5: return "針腳鬆了幾分，守勢怕是弱了些，莫怪。";
    case 6: return "這一路針法難得，是我少有的得意之作。";
    case 7: return "針腳輕靈，穿上它，身形當更見靈動。";
    case 8: return "我在襟邊暗藏了一線機巧，風吹草動，你自會察覺。";
    }
    return "";
}

void finish(object who)
{
    object ob;

    // 玩家走開（或離線）就沒了，不補。
    if( !objectp(who) || environment(who) != environment() ) {
        message_vision(CYN "$N見人已走遠，輕嘆一聲，將繡好的衣裳收了起來。\n" NOR, this_object());
        return;
    }

    seteuid(getuid());
    ob = new(EMBROIDERED_FILE);
    ob->embroider();
    speak("", "成了，" + result_line(ob->query("embroidery_result")));

    // 這時候就把衣服交給玩家；拿不動就放在地上。
    if( !ob->move(who) ) ob->move(environment());
    message_vision("$N交給$n一" + ob->query("unit") + ob->name() + "。\n", this_object(), who);
}

/* ---- 繡袋子（使用者指示，2026-11-24） ------------------------------- */

// 收下的袋子直接銷毀；繡好後給一個新的包包（plus_file），名稱、ID 不變。
void begin_bag(object who, object bag, string plus_file)
{
    if( objectp(bag) ) destruct(bag);
    act("$N接過$n遞來的袋子，金線繞袋口一圈，在袋角繡下一方空白籤牌。", who);
    call_out("finish_bag", EMBROIDER_TICKS * TICK, who, plus_file);
}

void finish_bag(object who, string plus_file)
{
    object ob;

    // 玩家走開（或離線）就沒了，不補。
    if( !objectp(who) || environment(who) != environment() ) {
        message_vision(CYN "$N見人已走遠，輕嘆一聲，將繡好的袋子收了起來。\n" NOR, this_object());
        return;
    }

    seteuid(getuid());
    ob = new(plus_file);
    speak("", "成了，籤牌上還空著，想題什麼名字，你自己寫上去便是。");

    if( !ob->move(who) ) ob->move(environment());
    message_vision("$N交給$n一" + ob->query("unit") + ob->name() + "。\n", this_object(), who);
}
