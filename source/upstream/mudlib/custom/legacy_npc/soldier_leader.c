// /custom/legacy_npc/soldier_leader.c — 舊站 NPC：兵部軍官（Soldier leader）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：未能判定；房間：—。
尚未製作的裝備（先空著）：鐵鱗腿護(Iron scale legs)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("兵部軍官", ({ "soldier leader", "soldier", "leader" }));
    set_race("headless");
    set_class("soldier");
    set_level(20);
    set("gender", "male");
    set("age", 45);
    set("long",
        "這是一位對兵部尚書司馬成都忠心不二的兵部軍官。\n");
    set_power("B");
    setup();
    carry_object("/custom/armor/feet/bull_boots")->wear();   // 蠻牛靴
    carry_object("/d/npc/obj/iron_girth")->wear();   // 精鐵環扣
}
