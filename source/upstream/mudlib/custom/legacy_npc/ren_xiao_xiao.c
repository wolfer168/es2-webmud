// /custom/legacy_npc/ren_xiao_xiao.c — 舊站 NPC：任蕭蕭（Ren xiao-xiao）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：未能判定；房間：廂房。
尚未製作的裝備（先空著）：琥珀心鍊(Amber necklace)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("任蕭蕭", ({ "ren xiao-xiao", "ren", "xiao-xiao" }));
    set_race("human");
    set_class("commoner");
    set_level(10);
    set("gender", "female");
    set("age", 25);
    set("long",
        "她長的雖無沉魚落雁之容，卻也是風情萬種，讓人心生愛意。只是\n"
        "她看起來滿面愁容，似乎正在為什麼事發愁。\n");
    set_power("B");
    setup();
    carry_object("/d/oldpine/npc/obj/violet_shoes")->wear();   // 紫紗靴
    carry_object("/custom/armor/cloth/rainbow_gown")->wear();   // 霓虹采裳
}
