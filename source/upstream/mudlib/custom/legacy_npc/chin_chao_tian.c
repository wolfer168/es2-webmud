// /custom/legacy_npc/chin_chao_tian.c — 舊站 NPC：秦朝天（Chin chao tian）。
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
    set_name("秦朝天", ({ "chin chao tian", "chin", "tian" }));
    set_race("human");
    set_class("fighter");
    set_level(20);
    set("gender", "male");
    set("age", 45);
    set("long",
        "一身草繩繫綁厚皮裘衣的高瘦大漢﹐由他一臉瘡疤褐黃的麻子臉看來﹐\n"
        "此人約莫四十來歲。\n");
    set_power("B");
    setup();
    carry_object("/d/baihua/npc/obj/straw_boots")->wear();   // 草鞋
    carry_object("/obj/area/obj/robe")->wear();   // 布袍
    carry_object("/obj/armor/fur_hat")->wear();   // 毛皮帽
    carry_object("/obj/area/obj/broadaxe")->wield();   // 板斧
}
