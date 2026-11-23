// /custom/legacy_npc/jen_commando.c — 舊站 NPC：任常恩（Jen commando）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：青邪宮；房間：上山小路。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("任常恩", ({ "jen commando", "jen", "commando" }));
    set("title", "振武軍營校尉");
    set_race("human");
    set_class("soldier");
    set_level(25);
    set("gender", "male");
    set("age", 35);
    set("long",
        "任常恩是振武軍營的校尉，這次因為青邪宮聚集了許多江湖武人朝廷擔心發\n"
        "生事故，因此命他選派幾名好手前來，表面上是朝廷重視這次聚會，但是所\n"
        "有與會的人都知道他是朝廷暗中監視此間武人的密使。\n");
    set_power("B");
    setup();
    carry_object("/custom/weapon/blade/snow_blade")->wield();   // 啐雪大刀
    carry_object("/d/npc/obj/ring_of_mighty_lord")->wear();   // 霸王指環
    carry_object("/d/baobao/npc/obj/royal_helmet")->wear();   // 霸王銅冠
    carry_object("/custom/armor/armor/iron_armor")->wear();   // 鐵戰甲
    carry_object("/d/qiaoyin/npc/obj/cyan_cloth")->wear();   // 青布官服
    carry_object("/d/baobao/npc/obj/steel_bracers")->wear();   // 精鋼護腕
}
