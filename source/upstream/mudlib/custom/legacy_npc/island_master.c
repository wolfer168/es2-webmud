// /custom/legacy_npc/island_master.c — 舊站 NPC：邯逸山（Island master）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：陷空島；房間：賓客室側房。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("邯逸山", ({ "island master", "island", "master" }));
    set("title", "陷空島島主");
    set_race("human");
    set_class("fighter");
    set_level(40);
    set("gender", "male");
    set("age", 35);
    set("long",
        "你眼前這位正是當初名震江湖劍斬神猿的陷空島島主, 他正對你微笑著!\n");
    set_power("B");
    setup();
    carry_object("/d/npc/obj/flying_boots")->wear();   // 飛天靴
    carry_object("/d/wutang/npc/obj/blue_cloth")->wear();   // 青布衣
    carry_object("/custom/armor/armor/monkey_armor")->wear();   // 猿仙絲冑
    carry_object("/custom/weapon/sword/white_dragon_fang")->wield();   // 白龍牙
}
