// /custom/legacy_npc/yu_wen.c — 舊站 NPC：宇文嵐胥（Yu wen）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：未能判定；房間：畫室內堂。
尚未製作的裝備（先空著）：青鐵棍筆(Iron pen)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("宇文嵐胥", ({ "yu wen", "yu", "wen" }));
    set_race("human");
    set_class("scholar");
    set_level(20);
    set("gender", "male");
    set("age", 45);
    set("long",
        "一個身材高瘦的中年畫師, 他的臉孔清瞿, 眉間隱隱有憂色, 不時發出\n"
        "幾聲低沉的嘆氣聲 ...。\n");
    set_power("B");
    setup();
    carry_object("/d/wutang/npc/obj/black_mandarin_jacket")->wear();   // 黑醬色馬褂
}
