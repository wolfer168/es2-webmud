// /d/baihua/npc/gong_sun_zhi.c — 舊站 NPC：公孫志（Gong-sun zhi）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：茅山、丱天樹；房間：紅燈客棧。
尚未製作的裝備（先空著）：大斗笠(Big cap)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("公孫志", ({ "gong-sun zhi", "gong-sun", "zhi" }));
    set("title", "靈雲觀道士");
    set_race("human");
    set_class("taoist");
    set_level(20);
    set("gender", "male");
    set("age", 55);
    set("long",
        "公孫志是一個在江湖上沒甚麼名氣的老道。這並不是因為他的法力\n"
        "不及他人，而是由於他太過醉心與詩詞歌賦，以至於無瑕顧及江湖\n"
        "中的是是非非。\n");
    set_power("B");
    setup();
    carry_object("/d/baihua/npc/obj/straw_boots")->wear();   // 草鞋
    carry_object("/d/npc/obj/hemp_cloth")->wear();   // 麻布衣
}
