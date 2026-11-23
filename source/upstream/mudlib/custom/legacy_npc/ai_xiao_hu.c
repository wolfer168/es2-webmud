// /custom/legacy_npc/ai_xiao_hu.c — 舊站 NPC：艾小虎（Ai xiao-hu）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：焱硝山；房間：山腳下。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("艾小虎", ({ "ai xiao-hu", "ai", "xiao-hu" }));
    set("title", "殺手");
    set_race("blackteeth");
    set_class("fighter");
    set_level(45);
    set("gender", "male");
    set("age", 35);
    set("long",
        "這位黑衣漢子正是黑道上號稱「六大殺手」之一的艾小虎，一手霸絕、狠絕的刀法\n"
        "曾讓追殺他的人死傷無數。\n");
    set("custom_faction", "fighter.tiger");   // 虎刀門（docs/martial_arts/門派武功對照表.md）
    set_power("A");
    setup();
    carry_object("/d/swaylan/lunmay/npc/obj/chain_shirt")->wear();   // 鎖鏈背心
    carry_object("/custom/armor/cloth/gray_robe")->wear();   // 灰袍
    carry_object("/custom/weapon/blade/poison_wind_blade")->wield();   // 酖風刀
}
