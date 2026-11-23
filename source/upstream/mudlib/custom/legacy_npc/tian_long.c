// /custom/legacy_npc/tian_long.c — 舊站 NPC：田龍（Tian long）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：虎刀門；房間：客房。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("田龍", ({ "tian long", "tian", "long" }));
    set("title", "虎刀門護衛");
    set_race("human");
    set_class("fighter");
    set_level(30);
    set("gender", "male");
    set("age", 45);
    set("long",
        "田龍是虎刀門新一代弟子中的佼佼者，據說他不僅內功刀法出神入化，就\n"
        "連虎刀門不很出名的輕功也練到了爐火純青的境界。\n");
    set("custom_faction", "fighter.tiger");   // 虎刀門（docs/martial_arts/門派武功對照表.md）
    set_power("B");
    setup();
    carry_object("/d/npc/obj/lion_belt")->wear();   // 獅蠻帶
    carry_object("/custom/armor/armor/iron_armor")->wear();   // 鐵戰甲
    carry_object("/custom/armor/finger/beast_ring")->wear();   // 獸面玉戒
    carry_object("/d/mengjia/npc/obj/red_dust_legs")->wear();   // 風塵腿護
    carry_object("/custom/weapon/blade/ceremonial_moon")->wield();   // 井中月
}
