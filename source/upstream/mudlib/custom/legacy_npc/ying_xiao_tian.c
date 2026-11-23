// /custom/legacy_npc/ying_xiao_tian.c — 舊站 NPC：應曉天（Ying xiao tian）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：冷梅莊；房間：客房。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("應曉天", ({ "ying xiao tian", "ying", "tian" }));
    set("title", "落花劍");
    set_race("human");
    set_class("fighter");
    set_level(40);
    set("gender", "male");
    set("age", 35);
    set("long",
        "一名長相俊逸的青年，這人一襲白衣，手上拿把描金折扇，瞧來甚是瀟灑\n"
        "不凡。但仔細一看，臉色蒼白、腳步浮虛，一副被酒色淘空了身子的模樣，\n"
        "兩顆眼睛逕盯著來往的女人，還掛滿了一臉的淫笑，腰上繫著一把雪白的\n"
        "長劍。\n");
    set("custom_faction", "fighter.fonxan");   // 封山派（docs/martial_arts/門派武功對照表.md）
    set_power("A");
    setup();
    carry_object("/custom/weapon/sword/sword_of_holy_frost")->wield();   // 凝霜
    carry_object("/d/npc/obj/white_scholar_dress")->wear();   // 白色長衫
    carry_object("/d/mengjia/npc/obj/red_dust_legs")->wear();   // 風塵腿護
    carry_object("/custom/armor/armor/shoulder_armor")->wear();   // 藍鋼肩甲
}
