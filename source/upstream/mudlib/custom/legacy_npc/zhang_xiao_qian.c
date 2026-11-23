// /custom/legacy_npc/zhang_xiao_qian.c — 舊站 NPC：張小簽（Zhang xiao qian）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：水嵐縣；房間：街道。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("張小簽", ({ "zhang xiao qian", "zhang", "qian" }));
    set("title", "江湖藝人");
    set_race("human");
    set_class("commoner");
    set_level(1);
    set("gender", "male");
    set("age", 25);
    set("long",
        "你面前這個雲遊四海的江湖藝人叫張小簽，他最擅長的就是變戲法，有時能把\n"
        "東西變沒，有時又能再變一個出來。你要是不相信的話，不妨給他點甚麼讓他\n"
        "變變看。\n");
    set_power("C");
    setup();
    carry_object("/d/lee/npc/obj/leather_boots")->wear();   // 皮靴
    carry_object("/d/npc/obj/white_scholar_dress")->wear();   // 白色長衫
}
