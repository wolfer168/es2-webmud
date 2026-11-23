// /custom/legacy_npc/zhong_chu.c — 舊站 NPC：鍾貙（Zhong chu）。
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
    set_name("鍾貙", ({ "zhong chu", "zhong", "chu" }));
    set("title", "神武軍營提督");
    set("nickname", "活閻羅");
    set_race("blackteeth");
    set_class("soldier");
    set_level(40);
    set("gender", "male");
    set("age", 55);
    set("long",
        "鍾貙是目前神武軍營最高指揮官，神武軍營鎮守志縣，牽制泰武定國，是天\n"
        "朝東南隅最重要防線，泰武定國雖然已歸順天朝十餘年，但其內部還是時有\n"
        "反天朝人士活動，所以神武軍營的重要性就更顯重要了，鍾貙是軒轅軍中的\n"
        "重要將領，天生神力，善使大槌，與其交鋒敗在其手下的對手常常總是慘死\n"
        "的血肉模糊難以辯別的，所以有的人會稱呼他為 \"活閻羅\" ，而這個名號也\n"
        "確確實實令許多對手聞風喪膽。\n");
    set_power("A");
    setup();
    carry_object("/d/npc/obj/steel_boots")->wear();   // 精鋼戰靴
    carry_object("/custom/armor/armor/dragon_plate_of_knights")->wear();   // 龍騎戰甲
    carry_object("/d/baobao/npc/obj/steel_bracers")->wear();   // 精鋼護腕
    carry_object("/custom/weapon/blunt/crasher_maul")->wield();   // 碎腦鎚
}
