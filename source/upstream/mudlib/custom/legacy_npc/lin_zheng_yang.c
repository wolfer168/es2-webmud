// /custom/legacy_npc/lin_zheng_yang.c — 舊站 NPC：林正陽（Lin zheng yang）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、裝備取自舊站畫面紀錄
（reference/es2_records/es2tips/2014-02-05-茅山道士-茅山派.txt）；
門派、師父、傳授技能依使用者指示（2026-11-22）。
位置：孟家莊小客棧（/d/mengjia/inn，使用者指示，2026-11-22）。
*/
#include <ansi.h>

inherit "/custom/legacy_npc/legacy_npc";

#define FACTION "mao-shan.cloud"

void create()
{
    seteuid(getuid());
    set_name("林正陽", ({ "lin zheng yang", "lin", "yang" }));
    set("title", "靈雲觀觀主");
    set_race("human");
    set_class("taoist");
    set_level(40);
    set("gender", "male");
    set("age", 85);
    set("long",
        "林正陽乃是茅山派靈雲觀第一代觀主﹐一生行走江湖﹐雖然沒留下太多俠義\n"
        "之事流傳江湖﹐但卻也是江湖中人人敬仰的一代宗師。相傳﹐四十年前﹐失\n"
        "傳的茅山劍法重現江湖﹐而當時的茅山掌門人﹐林遠﹐為了追查此事命喪人\n"
        "手﹐導致茅山上下一片大亂。當時對『幽冥三箭』造詣頗深的林正陽帶領一\n"
        "部份當時的茅山弟子憤然離去﹐自創靈雲觀。\n"
        "林正陽舉手投足間神色從容﹐頗有泰山崩於前而不改色的氣派﹐他看起來約\n"
        "八十多歲。\n");
    set("custom_faction", FACTION);   // 靈雲觀（docs/martial_arts/門派武功對照表.md）
    set_power("A");
    setup();
    carry_object("/custom/armor/cloth/green_robe")->wear();   // 青衣道袍
    carry_object("/custom/weapon/sword/peachwood_sword")->wield();   // 桃木劍
    carry_object("/custom/armor/finger/han_jade_ring")->wear();   // 漢玉戒指
}

// ------------------------------------------------------------------
// 靈雲觀師父（使用者指示，2026-11-22）：平民才能拜師，拜師後成為道士、靈雲觀弟子。
// 靈雲觀不收形天、焦僥、厭火、釘靈（舊文檔）。
// 傳授茅山共通法術（docs/martial_arts/茅山_法術.md），以及靈雲觀的幽冥三箭、五雷術
// （docs/martial_arts/靈雲觀_幽冥三箭與五雷術.md）。
// ------------------------------------------------------------------

int accept_info(object ob, string type)
{
    return type == "skills";
}

int accept_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        command("say 你已另有師承﹐貧道不便收你。");
        return 0;
    }
    if( member_array(me->query_race(), ({ "headless", "jiaojao", "yenhold", "dingling" })) >= 0 ) {
        command("say 你與本觀的道法無緣﹐還是另尋去處吧。");
        return 0;
    }
    return 1;
}

int init_apprentice(object me)
{
    if( ::init_apprentice(me) ) {
        me->set_class("taoist");
        me->set("title", "靈雲觀弟子");
        me->set("custom_faction", FACTION);
        do_chat(({
            "林正陽神色從容地點了點頭：好﹐從今以後你便是靈雲觀的弟子。\n",
            "林正陽說道：幽冥三箭貴在心定﹐心不亂﹐箭才不偏。\n",
        }));
    }
    return 1;
}

int acquire_skill(object me, string skill)
{
    if( me->query("custom_faction") != FACTION ) return 0;

    switch( skill ) {
    case "mao-shan magic":
    case "magic":
    case "taoism of purify":
    case "spells":
        break;
    case "mao-shan lightning":
        // 幽冥三箭 90 級（使用者定案，2026-11-22）。
        if( !SKILL_D(skill)->valid_learn(me) ) return 0;
        break;
    default:
        return 0;
    }

    if( me->query_learn(skill) >= me->skill_threshold(skill, 1) )
        return notify_fail("林正陽說道：入門的要訣已經傳給你了﹐往後全看你自己。\n");

    me->improve_skill_exact(skill, me->skill_threshold(skill, 1) - me->query_learn(skill));
    tell_object(me, CYN + "林正陽將「" + to_chinese(skill) + "」的入門要訣傳授給你。\n" NOR);
    return 1;
}
