// /custom/legacy_npc/lu_fei.c — 舊站 NPC：魯飛（Lu fei）。
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
    set_name("魯飛", ({ "lu fei", "lu", "fei" }));
    set_race("yenhold");
    set_class("soldier");
    set_level(50);
    set("gender", "male");
    set("age", 45);
    set("long",
        "魯飛曾經是征西大將軍神將帳下的第一猛將，後來由於臨時出征\n"
        "沒有跟隨神將去征討黑風山，至今仍為此事耿耿於懷，屢次上書\n"
        "請命再次發兵征討黑風山，為神將復仇。\n");
    set_power("A");
    setup();
    carry_object("/d/npc/obj/water_dragon_girdle")->wear();   // 蛟龍帶
    carry_object("/d/npc/obj/ring_of_mighty_lord")->wear();   // 霸王指環
    carry_object("/d/baobao/npc/obj/royal_helmet")->wear();   // 霸王銅冠
    carry_object("/d/baobao/npc/obj/royal_armor")->wear();   // 霸王鎧
    carry_object("/custom/weapon/blunt/whirlwind_blunt")->wield();   // 旋風流星槌
}
