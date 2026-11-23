// /custom/legacy_npc/su_xiao.c — 舊站 NPC：蘇瀟（Su xiao）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：未能判定；房間：書房。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("蘇瀟", ({ "su xiao", "su", "xiao" }));
    set_race("human");
    set_class("fighter");
    set_level(15);
    set("gender", "male");
    set("age", 45);
    set("long",
        "你眼前是一名相貌堂堂的中年男子，全身散發著一股內斂的英氣，他\n"
        "正是蘇家莊主蘇瀟，蘇家三代經營賭場，到蘇瀟手上創了十一家分號\n"
        "，家業可謂如日中天，加上為人慷慨豪氣，平日就為地方百姓貢獻不\n"
        "少心力，在市井小民之間也頗具人望。但是他現在看起來卻愁眉不展\n"
        "，似乎有什麼心事....。\n");
    set_power("A");
    setup();
    carry_object("/d/npc/obj/water_dragon_girdle")->wear();   // 蛟龍帶
    carry_object("/d/mengjia/npc/obj/red_dust_legs")->wear();   // 風塵腿護
    carry_object("/d/npc/obj/silk_cloth")->wear();   // 天蠶寶衣
    carry_object("/d/shuiyue/npc/obj/colosus_sword")->wield();   // 巨劍
}
