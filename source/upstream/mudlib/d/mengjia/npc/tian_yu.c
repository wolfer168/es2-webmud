// /d/mengjia/npc/tian_yu.c — 舊站 NPC：田由（Tian yu）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：孟家祖墳；房間：—。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("田由", ({ "tian yu", "tian", "yu" }));
    set("title", "塞北雙熊");
    set_race("headless");
    set_class("fighter");
    set_level(30);
    set("gender", "male");
    set("age", 35);
    set("long",
        "田由是塞北雙熊中的老二，長得又高又大，打人全靠一身蠻力。偏偏卻\n"
        "又自認為武功高強，自從見過孟憶柔一面之後，就死皮賴臉的呆在孟家\n"
        "莊不走，要不是孟家現在正有事，早就把他殺了。\n");
    set_power("B");
    setup();
    carry_object("/d/npc/obj/cloud_boots")->wear();   // 流雲靴
    carry_object("/d/mengjia/npc/obj/star_studded_legs")->wear();   // 星雲腿護
    carry_object("/d/mengjia/npc/obj/copper_sword")->wield();   // 古銅重劍
}
