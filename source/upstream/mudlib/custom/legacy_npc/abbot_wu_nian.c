// /custom/legacy_npc/abbot_wu_nian.c — 舊站 NPC：無念大師（Abbot wu-nian）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：白象寺；房間：—。
門派「白象寺」尚未列入門派武功對照表，先不設門派記號。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("無念大師", ({ "abbot wu-nian", "abbot", "wu-nian" }));
    set("title", "白象寺住持");
    set_race("human");
    set_class("monk");
    set_level(65);
    set("gender", "male");
    set("age", 85);
    set("long",
        "這位瘦小的老人就是天朝境內備受推崇的武學大師，白象寺的方丈\n"
        "無念大師。他自幼在白象寺內演習佛法修練武功，時至今日，其佛\n"
        "學修養和武學修為均以達登峰造極的境界，實在是讓人敬佩啊。\n");
    set_power("A");
    setup();
    carry_object("/custom/armor/feet/wonder_boots")->wear();   // 六合玲瓏靴
    carry_object("/d/npc/obj/black_doli")->wear();   // 黑斗笠
    carry_object("/d/npc/obj/psakaml")->wear();   // 金剛念珠
    carry_object("/custom/weapon/staff/flower_cane")->wield();   // 蓮花禪杖
    carry_object("/d/snowkeep/npc/obj/gold_robe")->wear();   // 金線僧袍
}
