// /custom/legacy_npc/lee_hon_yun.c — 舊站 NPC：李洪雲（Lee hon_yun）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：未能判定；房間：—。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("李洪雲", ({ "lee hon_yun", "lee", "hon_yun" }));
    set("title", "黑風山總管");
    set_race("yaksa");
    set_class("fighter");
    set_level(30);
    set("gender", "male");
    set("age", 35);
    set("long",
        "李洪雲是山寨的總管, 許多大大小小的事都必須經過他的允許, 他長得\n"
        "眉清目秀, 讓人覺得毫無防備之心, 但是他性情卻相當兇殘, 每次掠奪\n"
        "時絕對不留活口 。\n");
    set("custom_faction", "fighter.fonxan");   // 封山派（docs/martial_arts/門派武功對照表.md）
    set("legacy_aggressive", 1);   // 看到玩家就下殺手
    set_power("B");
    setup();
    carry_object("/custom/weapon/sword/snake_sword")->wield();   // 金蛇劍
    carry_object("/custom/armor/hand/black_gauntlets")->wear();   // 黑鐵護手
    carry_object("/custom/armor/armor/iron_armor")->wear();   // 鐵戰甲
    carry_object("/d/npc/obj/iron_cloth")->wear();   // 鐵布衫
}
