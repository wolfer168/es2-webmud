// /custom/legacy_npc/ghost_lord.c — 舊站 NPC：噬魂（Ghost lord）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：文國縣；房間：清水鄉。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("噬魂", ({ "ghost lord", "ghost", "lord" }));
    set("title", "鬼王");
    set_race("human");
    set_class("soldier");
    set_level(35);
    set("gender", "male");
    set("age", 1665);
    set("long",
        "噬魂，嗜吃魂，原是鬼王「顝蛪」一員魔將，論能力比十二鬼將更為強\n"
        "悍。但當鬼王「顝蛪」被封，噬魂異心即起！自立為鬼王，四處吞噬靈\n"
        "魂已增其法力。在一次跟地府鬼將的戰鬥中，戰敗被擒，給困在地獄十\n"
        "八層盡受苦刑。\n");
    set("legacy_aggressive", 1);   // 看到玩家就下殺手
    set_power("B");
    setup();
    carry_object("/custom/weapon/axe/eight_ghost_axe")->wield();   // 八鬼牙斧
    carry_object("/d/npc/obj/blood_stained_cloth")->wear();   // 征衣「血染」
    carry_object("/custom/armor/armor/soul_lapis_lazuli_plate")->wear();   // 靈中樞甲
}
