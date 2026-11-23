// /custom/legacy_npc/yaksa_king.c — 舊站 NPC：羅剎王（Yaksa King）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：古墓場；房間：—。
尚未製作的裝備（先空著）：太陽巨神劍(Sun colosus sword)、襯甲(Padded armor)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("羅剎王", ({ "yaksa king", "yaksa", "king" }));
    set_race("yaksa");
    set_class("fighter");
    set_level(35);
    set("gender", "male");
    set("age", 295);
    set("long",
        "羅剎王雙目如烈火般散發著讓人窒息的紅光﹐週身上下結實的肌肉更\n"
        "釋放出無窮的殺氣。\n");
    set("legacy_aggressive", 1);   // 看到玩家就下殺手
    set("legacy_patrol", 1);       // 在同一區域內巡邏
    set_power("A");
    setup();
    carry_object("/d/wutang/npc/obj/blue_cloth")->wear();   // 青布衣
    carry_object("/d/npc/obj/forgod_boots")->wear();   // 封神靴
}
