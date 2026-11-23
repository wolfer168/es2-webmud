// /custom/legacy_npc/chang_ba.c — 舊站 NPC：張霸（Chang ba）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：黑風寨；房間：山谷中。
尚未製作的裝備（先空著）：虎紋斬馬刀(Reckless blade)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("張霸", ({ "chang ba", "chang", "ba" }));
    set("title", "黑風寨五頭目");
    set_race("human");
    set_class("fighter");
    set_level(50);
    set("gender", "male");
    set("age", 65);
    set("long",
        "張霸乃是黑風寨的五頭目, 原為虎刀門中的好手, 平素行止不端\n"
        ", 於十數年前遭武林正道圍攻後消聲匿跡, 數個月後重現師門,\n"
        "盜走師門寶刀「虎紋刀」後投入黑風寨中, 目前是黑風寨的刀術\n"
        "教頭, 他仗恃著一手爐火純青的瘋虎刀法已是一流高手, 如今寶\n"
        "刀在手更如虎添翼, 近年來不少高手魂飛虎紋刀下, 在武林中已\n"
        "是惡名昭彰, 他正滿臉邪氣惡狠狠地盯著你。\n");
    set("custom_faction", "fighter.tiger");   // 虎刀門（docs/martial_arts/門派武功對照表.md）
    set_power("A");
    setup();
    carry_object("/custom/armor/armor/shoulder_armor")->wear();   // 藍鋼肩甲
    carry_object("/d/snowkeep/npc/obj/skin_gloves")->wear();   // 鹿皮手套
    carry_object("/custom/armor/cloth/yellow_suit")->wear();   // 黃短衫
    carry_object("/custom/weapon/sword/daoist_sword");   // 指南劍
}
