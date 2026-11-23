// /custom/legacy_npc/ou_yan_wu_ji.c — 舊站 NPC：歐陽無寂（Ou-yan wu ji）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：茅山；房間：客房內。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("歐陽無寂", ({ "ou-yan wu ji", "ou-yan", "ji" }));
    set("title", "隱風觀道士");
    set_race("human");
    set_class("taoist");
    set_level(30);
    set("gender", "male");
    set("age", 45);
    set("long",
        "歐陽無寂是隱風觀觀主歐陽無極的雙生弟弟，兩人同時拜在宇文太\n"
        "極門下。因為兩人面貌相似，名字發音又相同，觀中弟子都以「大\n"
        "師父」稱呼歐陽無極，而稱歐陽無寂為「二師父」。半個月前，他\n"
        "收到了歐陽無極的飛符傳書，連忙從宓縣北上，要趕在茅山三位觀\n"
        "主會面之前，先與歐陽無極會合。\n");
    set_power("B");
    setup();
    carry_object("/d/npc/obj/black_doli")->wear();   // 黑斗笠
    carry_object("/d/npc/obj/han_jade_ring")->wear();   // 漢玉戒指
    carry_object("/d/npc/obj/green_robe")->wear();   // 青衣道袍
    carry_object("/d/npc/obj/peachwood_sword")->wield();   // 桃木劍
}
