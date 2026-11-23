// /d/ziyan/npc/lin_yu_lun.c — 舊站 NPC：林育崙（Lin yu lun）。
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
    set_name("林育崙", ({ "lin yu lun", "lin", "lun" }));
    set("title", "酉縣總捕頭");
    set_race("human");
    set_class("soldier");
    set_level(30);
    set("gender", "male");
    set("age", 45);
    set("long",
        "酉縣的總捕頭「林育崙」, 據說他曾經是某個著名山寨的大頭目, 後\n"
        "後來歸順了朝廷, 於是朝廷便封了他這總捕頭的職位, 不過由於他是\n"
        "綠林出身, 再加上辦案的態度十分強硬, 所以大家對他都是盡量迴避\n"
        ", 不與他有任何衝突, 以免惹禍上身.\n");
    set_power("A");
    setup();
    carry_object("/d/ziyan/npc/obj/steel_chain_armor")->wear();   // 鋼戰甲
    carry_object("/d/ziyan/npc/obj/silkworm_tunic")->wear();   // 烏蠶寶衣
    carry_object("/d/ziyan/npc/obj/iron_rosary")->wear();   // 鐵佛珠
    carry_object("/d/ziyan/npc/obj/moon_blade")->wield();   // 偃月刀
}
