// /d/swaylan/npc/kao_fon.c — 舊站 NPC：高風（Kao fon）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：黃家鏢局；房間：練功房。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("高風", ({ "kao fon", "kao", "fon" }));
    set("title", "黃家鏢局鏢頭");
    set_race("headless");
    set_class("fighter");
    set_level(20);
    set("gender", "male");
    set("age", 35);
    set("long",
        "高風乃是百花村的一位高手，因為其功夫高強，被黃天霸延攬為鏢頭，他一手\n"
        "槍法耍得虎虎生風，令綠林大盜聞風喪膽。他還可以負責幫忙打聽江湖人物的\n"
        "下落，只是可信度嘛 ... 嘿嘿嘿。\n");
    set_power("B");
    setup();
    carry_object("/d/swaylan/npc/obj/tiger_pike")->wield();   // 虎鳴槍
}
