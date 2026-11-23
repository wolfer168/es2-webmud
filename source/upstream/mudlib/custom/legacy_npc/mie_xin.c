// /custom/legacy_npc/mie_xin.c — 舊站 NPC：滅心（Mie xin）。
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
    set_name("滅心", ({ "mie xin", "mie", "xin" }));
    set_race("avatar");
    set_class("soldier");
    set_level(40);
    set("gender", "male");
    set("age", 505);
    set("long",
        "守護神之遺跡的護衛﹐經受了神明對其心智體力的考驗和鍛煉﹐永生\n"
        "守衛神之遺跡的密寶不受凡人的侵犯。\n");
    set("legacy_aggressive", 1);   // 看到玩家就下殺手
    set_power("A");
    setup();
    carry_object("/d/baobao/npc/obj/steel_bracers")->wear();   // 精鋼護腕
    carry_object("/d/npc/obj/blood_stained_cloth")->wear();   // 征衣「血染」
    carry_object("/d/npc/obj/steel_armor")->wear();   // 精鋼戰甲
    carry_object("/custom/weapon/pike/huge_halberd")->wield();   // 方天畫戟
}
