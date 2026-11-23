// /custom/legacy_npc/tiger_trainer.c — 舊站 NPC：虎刀門教頭（Tiger trainer）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：虎刀門；房間：操練場。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("虎刀門教頭", ({ "tiger trainer", "tiger", "trainer" }));
    set_race("human");
    set_class("fighter");
    set_level(20);
    set("gender", "male");
    set("age", 55);
    set("long",
        "他是虎刀門的一位老教頭，負責傳授新弟子武功。\n");
    set("custom_faction", "fighter.tiger");   // 虎刀門（docs/martial_arts/門派武功對照表.md）
    set_power("B");
    setup();
    carry_object("/d/baihua/npc/obj/ringmail")->wear();   // 鎖子甲
    carry_object("/custom/armor/feet/bull_boots")->wear();   // 蠻牛靴
    carry_object("/custom/armor/cloth/tiger_coat")->wear();   // 斑斕虎氅
    carry_object("/custom/weapon/blade/colosus_blade")->wield();   // 巨刀
}
