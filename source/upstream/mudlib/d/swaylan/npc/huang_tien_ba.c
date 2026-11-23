// /d/swaylan/npc/huang_tien_ba.c — 舊站 NPC：黃天霸（Huang tien-ba）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：黃家鏢局、茅山、文國縣；房間：外廳、山林、清水鄉。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("黃天霸", ({ "huang tien-ba", "huang", "tien-ba" }));
    set("title", "黃家鏢局總鏢頭");
    set("nickname", "霸王刀");
    set_race("yaksa");
    set_class("fighter");
    set_level(30);
    set("gender", "male");
    set("age", 45);
    set("long",
        "黃天霸是江南有名的鏢頭，保過很多趟大鏢，從來沒有出過什麼岔子。一手\n"
        "七七四十九路霸王刀招獨豎一格，人家都尊稱他為【霸王刀】，平時為人非\n"
        "常豪爽，有困難的話可以來他這，他會盡力去幫你解決。\n");
    set("custom_faction", "fighter.tiger");   // 虎刀門（docs/martial_arts/門派武功對照表.md）
    set_power("A");
    setup();
    carry_object("/d/swaylan/npc/obj/golden_ring")->wear();   // 黃金指環
    carry_object("/d/swaylan/npc/obj/studded_armor")->wear();   // 鑲釘皮鎧
    carry_object("/d/npc/obj/golden_feather_helm")->wear();   // 金羽神盔
    carry_object("/d/npc/obj/golden_robe")->wear();   // 金絲長袍
    carry_object("/d/swaylan/npc/obj/blade_of_nine_rings")->wield();   // 九環霸王刀
}
