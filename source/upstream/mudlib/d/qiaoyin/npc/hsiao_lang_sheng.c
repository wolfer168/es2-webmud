// /d/qiaoyin/npc/hsiao_lang_sheng.c — 舊站 NPC：蕭朗生（Hsiao lang-sheng）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：天邪國；房間：—。
門派「天邪派」尚未列入門派武功對照表，先不設門派記號。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("蕭朗生", ({ "hsiao lang-sheng", "hsiao", "lang-sheng" }));
    set_race("human");
    set_class("fighter");
    set_level(50);
    set("gender", "male");
    set("age", 45);
    set("long",
        "蕭朗生是天邪國小有名氣的劍客﹐一手追魂劍法輕靈狠辣﹐算得是武林\n"
        "中一個人物﹐但是自從半年前在一次仇家的突襲中失去了妻子﹐就變得\n"
        "性情十分乖戾﹐和從前判若兩人﹐如果你不想惹禍上身的話﹐最好離他\n"
        "遠一點。\n"
        "——\n"
        "蕭朗生是天邪國小有名氣的劍客﹐一手平波劍法輕靈狠辣﹐算得是武林\n"
        "中一個人物﹐但是自從半年前在一次仇家的突襲中失去了妻子﹐就變得\n"
        "性情十分乖戾﹐和從前判若兩人﹐如果你不想惹禍上身的話﹐最好離他\n"
        "遠一點。\n");
    set_power("A");
    setup();
    carry_object("/d/qiaoyin/npc/obj/white_helmet")->wear();   // 白馬盔
    carry_object("/d/qiaoyin/npc/obj/snake_bracers")->wear();   // 纏蛇護手
    carry_object("/d/npc/obj/padded_armor")->wear();   // 軟櫬甲
    carry_object("/d/qiaoyin/npc/obj/sword_of_black_justice")->wield();   // 烏讎劍
}
