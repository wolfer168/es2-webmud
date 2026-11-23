// /custom/legacy_npc/stone_ghost.c — 舊站 NPC：八臂石妖（Stone ghost）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：未能判定；房間：雷神宮殿。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("八臂石妖", ({ "stone ghost", "stone", "ghost" }));
    set_race("headless");
    set_class("soldier");
    set_level(40);
    set("gender", "male");
    set("age", 735);
    set("long",
        "這！這是一個甚麼東西？怎麼看都是一座巨大的八臂無頭石像！\n"
        "他胸口的一塊石牌上刻著「雷神禁地」四個字。\n");
    set("legacy_aggressive", 1);   // 看到玩家就下殺手
    set_power("A");
    setup();
    carry_object("/d/npc/obj/forgod_boots")->wear();   // 封神靴
    carry_object("/custom/weapon/blunt/crasher_maul")->wield();   // 碎腦鎚
}
