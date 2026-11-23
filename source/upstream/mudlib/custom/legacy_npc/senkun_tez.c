// /custom/legacy_npc/senkun_tez.c — 舊站 NPC：上官小翠（Senkun tez）。
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
    set_name("上官小翠", ({ "senkun tez", "senkun", "tez" }));
    set("title", "老劍山徑第十三代弟子");
    set_race("human");
    set_class("fighter");
    set_level(10);
    set("gender", "female");
    set("age", 15);
    set("long",
        "上官小翠是老劍山徑執法上官笑夢的獨生女兒, 別看她弱不禁風的樣子,\n"
        "她的劍法在巾幗輩中算是蠻突出的一位。\n");
    set_power("B");
    setup();
    carry_object("/custom/armor/feet/flower_boots")->wear();   // 小繡花鞋
    carry_object("/custom/armor/head/jade_hairpin")->wear();   // 翠玉髮簪
    carry_object("/custom/armor/cloth/tender_cloth")->wear();   // 絲綢小服
    carry_object("/d/fengcheng/npc/obj/steel_longsword")->wield();   // 精鋼長劍
}
