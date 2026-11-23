// /custom/legacy_npc/si_ma_cheng_du.c — 舊站 NPC：司馬成都（Si-ma cheng du）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：未能判定；房間：—。
尚未製作的裝備（先空著）：鐵鱗腿護(Iron scale legs)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("司馬成都", ({ "si-ma cheng du", "si-ma", "du" }));
    set("title", "兵部尚書");
    set_race("human");
    set_class("soldier");
    set_level(70);
    set("gender", "male");
    set("age", 65);
    set("long",
        "你面前這位年已花甲的白髮老人就是天朝軍界的第一人，兵部尚書\n"
        "司馬成都。不僅是司馬成都本人，其實整個司馬家族幾乎都在天朝\n"
        "軍中效力。這雖然引來一些人的猜疑，但是司馬成都憑借其一身正\n"
        "氣和纍纍戰功依舊深得祐聖帝信賴。\n");
    set_power("A");
    setup();
    carry_object("/d/baobao/npc/obj/tiger_plate")->wear();   // 虎嘯旭日鎧
    carry_object("/custom/zhenwu/obj/fire_gauntlets")->wear();   // 冶磺套
    carry_object("/custom/weapon/blunt/black_iron_hammer")->wield();   // 黑鐵大槌
    carry_object("/custom/armor/cloth/dragon_cloth")->wear();   // 蟠龍朝服
    carry_object("/d/baobao/npc/obj/royal_helmet")->wear();   // 霸王銅冠
}
