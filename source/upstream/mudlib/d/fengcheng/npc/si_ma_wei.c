// /d/fengcheng/npc/si_ma_wei.c — 舊站 NPC：司馬蔚（Si-ma wei）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：風城；房間：—。
尚未製作的裝備（先空著）：太陽巨神劍(Sun colosus sword)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("司馬蔚", ({ "si-ma wei", "si-ma", "wei" }));
    set("title", "風城大將軍");
    set_race("human");
    set_class("soldier");
    set_level(55);
    set("gender", "male");
    set("age", 25);
    set("long",
        "風城的大將軍。聽人說他兩年前還只是個小卒，也沒有什麼戰功，不知\n"
        "為什麼會被提升為大將軍。\n");
    set_power("A");
    setup();
    carry_object("/d/npc/obj/ring_of_mighty_lord")->wear();   // 霸王指環
    carry_object("/d/npc/obj/steel_armor")->wear();   // 精鋼戰甲
}
