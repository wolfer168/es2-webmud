// /custom/legacy_npc/liu_shang_min.c — 舊站 NPC：劉尚民（Liu shang min）。
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
    set_name("劉尚民", ({ "liu shang min", "liu", "min" }));
    set_race("human");
    set_class("fighter");
    set_level(10);
    set("gender", "male");
    set("age", 15);
    set("long",
        "一位年約二十的魁武青年﹐高顴短髮蓄鬍﹐雙眼圓猙如銅鈴﹐身著黃麻\n"
        "短掛鹿皮靴。手上一根齊眉長棍撈在肩背正不時低聲嘆息著。\n");
    set_power("C");
    setup();
    carry_object("/obj/cloth")->wear();   // 布衣
    carry_object("/d/baihua/npc/obj/straw_boots")->wear();   // 草鞋
    carry_object("/d/lee/npc/obj/brow_staff")->wield();   // 齊眉棍
}
