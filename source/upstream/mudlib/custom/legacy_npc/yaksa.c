// /custom/legacy_npc/yaksa.c — 舊站 NPC：夜羅剎（Yaksa）。
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
    set_name("夜羅剎", ({ "yaksa" }));
    set_race("yaksa");
    set_class("fighter");
    set_level(30);
    set("gender", "female");
    set("age", 295);
    set("long",
        "妖艷的女性惡魔戰士﹐雖然看起來十分溫柔﹐可是她們驚人的戰鬥力\n"
        "以及獨特的戰鬥技巧是十分恐怖的。\n");
    set("legacy_patrol", 1);       // 在同一區域內巡邏
    set_power("B");
    setup();
    carry_object("/custom/armor/feet/embroidery_boots")->wear();   // 繡花鞋
    carry_object("/custom/armor/waist/girl_girth")->wear();   // 束腰帶
    carry_object("/d/npc/obj/green_cloth")->wear();   // 翠綠短杉
}
