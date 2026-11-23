// /custom/legacy_npc/lieutenant.c — 舊站 NPC：武官（Lieutenant）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：兆隱縣、青邪宮；房間：老王燒烤、上山小路。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("武官", ({ "lieutenant" }));
    set_race("human");
    set_class("soldier");
    set_level(25);
    set("gender", "male");
    set("age", 35);
    set("long",
        "這是一名指揮官兵的武官﹐他們通常是軍人中出類拔萃的佼佼者。\n");
    set_power("B");
    setup();
    carry_object("/obj/area/obj/bastardsword")->wield();   // 大劍
    carry_object("/d/npc/obj/clothboot")->wear();   // 皂步靴
    carry_object("/d/npc/obj/helmet")->wear();   // 銅盔
    carry_object("/d/qiaoyin/npc/obj/cyan_cloth")->wear();   // 青布官服
    carry_object("/d/npc/obj/iron_girth")->wear();   // 精鐵環扣
    carry_object("/d/npc/obj/ring_armor")->wear();   // 連身鎖子甲
}
