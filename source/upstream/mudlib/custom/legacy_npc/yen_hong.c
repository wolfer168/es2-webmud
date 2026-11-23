// /custom/legacy_npc/yen_hong.c — 舊站 NPC：晏訌（Yen hong）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：老劍山；房間：客房。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("晏訌", ({ "yen hong", "yen", "hong" }));
    set("title", "老劍山徑第十二代弟子");
    set_race("human");
    set_class("fighter");
    set_level(20);
    set("gender", "male");
    set("age", 25);
    set("long",
        "晏訌是老劍山徑莊主晏勢苔的獨生子, 和山徑執法上官笑夢之女\n"
        "上官小翠從小就是青梅竹馬..晏訌生性耿直, 木訥寡言, 但一身\n"
        "橫練鐵打功夫, 和單手能劈巨石的狂大膂力, 再加上晏勢苔親傳\n"
        "老劍山徑的漫雨刀法, 使得他在武林的名號已是響亮異常!。\n");
    set_power("B");
    setup();
    carry_object("/custom/armor/armor/shoulder_armor")->wear();   // 藍鋼肩甲
    carry_object("/custom/armor/feet/flycloud_boots")->wear();   // 流雲鐵靴
    carry_object("/custom/armor/cloth/broken_iron_cloth")->wear();   // 殘鐵衣
    carry_object("/d/npc/obj/ghosts_blade")->wield();   // 百鬼刀
}
