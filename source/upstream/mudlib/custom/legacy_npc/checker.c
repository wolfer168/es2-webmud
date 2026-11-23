// /custom/legacy_npc/checker.c — 舊站 NPC：考核官（Checker）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：京畿；房間：考選室。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("考核官", ({ "checker" }));
    set_race("human");
    set_class("soldier");
    set_level(20);
    set("gender", "male");
    set("age", 45);
    set("long",
        "考核官坐在桌前，拿著硃砂筆評點著送來的奏摺。\n");
    set_power("B");
    setup();
    carry_object("/obj/area/obj/pen")->wield();   // 判官筆
    carry_object("/d/qiaoyin/npc/obj/cyan_cloth")->wear();   // 青布官服
}
