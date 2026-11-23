// /custom/legacy_npc/rong_shi_guo.c — 舊站 NPC：榮世國（Rong shi guo）。
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
    set_name("榮世國", ({ "rong shi guo", "rong", "guo" }));
    set_race("human");
    set_class("fighter");
    set_level(40);
    set("gender", "male");
    set("age", 65);
    set("long",
        "你面前的這位老者身材魁梧﹐雙目有神﹐三縷白鬚整齊的落在胸前。\n"
        "榮家世代在朝為官且身居要職﹐尤其是最近幾年﹐榮家的勢利迅速\n"
        "成長﹐對天朝的軍界政界都有不小的影響。\n");
    set_power("B");
    setup();
    carry_object("/d/npc/obj/han_jade_ring")->wear();   // 漢玉戒指
    carry_object("/custom/armor/cloth/dragon_cloth")->wear();   // 蟠龍朝服
    carry_object("/custom/armor/head/jade_hat")->wear();   // 綠玉頂戴
    carry_object("/custom/weapon/staff/serpent_cane")->wield();   // 冥魔杖
}
