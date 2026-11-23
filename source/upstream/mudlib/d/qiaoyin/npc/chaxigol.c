// /d/qiaoyin/npc/chaxigol.c — 舊站 NPC：查思古禮（Chaxigol）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：茅山；房間：大街。
尚未製作的裝備（先空著）：寬襟長衫(Long robe)、大蠻刀(Heavy blade)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("查思古禮", ({ "chaxigol" }));
    set_race("human");
    set_class("fighter");
    set_level(25);
    set("gender", "male");
    set("age", 35);
    set("long",
        "查思古禮是個留著大鬍子的外國人，身材相當高大，加上體型又胖\n"
        "，站在街上任何人都會忍不住多瞧幾眼。不過你不要小看他，查思\n"
        "古禮在天朝旅行多年，其武藝在南方一代也小有名氣。\n");
    set_power("B");
    setup();
    carry_object("/d/npc/obj/side_armor")->wear();   // 肩鎧
}
