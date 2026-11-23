// /custom/legacy_npc/zuo_guo_yi.c — 舊站 NPC：左國益（Zuo guo yi）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：未能判定；房間：—。
尚未製作的裝備（先空著）：鑌鐵頭盔(Iron helm)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("左國益", ({ "zuo guo yi", "zuo", "yi" }));
    set("title", "地氣塔守衛");
    set_race("human");
    set_class("soldier");
    set_level(30);
    set("gender", "male");
    set("age", 30);
    set("long",
        "左國益是地氣塔塔頂的守衛主將﹐他身長九尺﹐站在你面前有如鐵塔\n"
        "一般﹐讓人望而生畏﹐即使是已經死了的人也不敢輕易惹他。\n");
    set_power("B");
    setup();
    carry_object("/d/npc/obj/blood_stained_cloth")->wear();   // 征衣「血染」
    carry_object("/custom/armor/armor/iron_torso")->wear();   // 鑌鐵胸鎧
    carry_object("/custom/weapon/axe/grandaxe")->wield();   // 十石大斧
}
