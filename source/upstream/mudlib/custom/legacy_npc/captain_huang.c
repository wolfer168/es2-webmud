// /custom/legacy_npc/captain_huang.c — 舊站 NPC：黃靖國（Captain Huang）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：未能判定；房間：—。
尚未製作的裝備（先空著）：青衣(Green cloth)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("黃靖國", ({ "captain huang", "captain", "huang" }));
    set("title", "總兵");
    set_race("human");
    set_class("soldier");
    set_level(30);
    set("gender", "male");
    set("age", 35);
    set("long",
        "黃靖國近年來轉戰各地，積功無數，以勇猛及鐵槍威震四方，年僅三\n"
        "十而能榮膺總兵官要職，可說是少年有成。\n");
    set_power("A");
    setup();
    carry_object("/custom/weapon/pike/iron_pike")->wield();   // 渾鐵龍蛇槍
    carry_object("/d/baobao/npc/obj/steel_bracers")->wear();   // 精鋼護腕
    carry_object("/d/npc/obj/steel_armor")->wear();   // 精鋼戰甲
}
