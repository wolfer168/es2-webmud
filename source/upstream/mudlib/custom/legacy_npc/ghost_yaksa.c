// /custom/legacy_npc/ghost_yaksa.c — 舊站 NPC：鬼夜叉（Ghost yaksa）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：古墓場；房間：—。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("鬼夜叉", ({ "ghost yaksa", "ghost", "yaksa" }));
    set_race("yaksa");
    set_class("fighter");
    set_level(30);
    set("gender", "male");
    set("age", 205);
    set("long",
        "最低級的惡魔戰士﹐主要的任務是保衛夜神殿的安全。\n");
    set("legacy_aggressive", 1);   // 看到玩家就下殺手
    set("legacy_patrol", 1);       // 在同一區域內巡邏
    set_power("B");
    setup();
    carry_object("/custom/weapon/blade/colosus_blade")->wield();   // 巨刀
    carry_object("/d/npc/obj/water_dragon_girdle")->wear();   // 蛟龍帶
    carry_object("/d/snowkeep/npc/obj/bamboo_legs")->wear();   // 青竹腿護
}
