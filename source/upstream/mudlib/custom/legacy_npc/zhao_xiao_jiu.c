// /custom/legacy_npc/zhao_xiao_jiu.c — 舊站 NPC：趙曉九（Zhao xiao jiu）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：茅山、巫山；房間：巫山客棧。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("趙曉九", ({ "zhao xiao jiu", "zhao", "jiu" }));
    set("title", "隱風觀道士");
    set_race("human");
    set_class("taoist");
    set_level(20);
    set("gender", "male");
    set("age", 35);
    set("long",
        "趙曉九自由喜愛神秘的東西，所以才會當了道士，一天到晚玩弄著\n"
        "別人看不懂的把戲，畫著讓人莫名奇妙的道符。他最大的嗜好就是\n"
        "收集古籍，從中找尋失傳的法術。\n");
    set_power("B");
    setup();
    carry_object("/d/npc/obj/peachwood_sword")->wield();   // 桃木劍
    carry_object("/d/taiyi/npc/obj/black_cloth_boots")->wear();   // 黑布鞋
    carry_object("/d/npc/obj/copper_hat")->wear();   // 青銅道冠
    carry_object("/custom/armor/cloth/gray_taoist_robe")->wear();   // 灰衣道袍
}
