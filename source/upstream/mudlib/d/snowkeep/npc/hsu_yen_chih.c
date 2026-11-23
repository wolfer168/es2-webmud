// /d/snowkeep/npc/hsu_yen_chih.c — 舊站 NPC：許彥之（Hsu yen-chih）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：季縣；房間：—。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("許彥之", ({ "hsu yen-chih", "hsu", "yen-chih" }));
    set_race("human");
    set_class("fighter");
    set_level(20);
    set("gender", "male");
    set("age", 45);
    set("long",
        "許彥之是季縣虎刀門的弟子﹐虎刀門以善使刀聞名﹐這次來到雪\n"
        "吟山莊﹐倒不是為了參加英雄大會﹐而是想來打探一下消失了多\n"
        "年的軒轅龍骨刀是否真的被藏在了雪吟山莊。\n");
    set("custom_faction", "fighter.tiger");   // 虎刀門（docs/martial_arts/門派武功對照表.md）
    set_power("B");
    setup();
    carry_object("/obj/area/obj/leather_boot")->wear();   // 皮短靴
    carry_object("/d/npc/obj/lion_belt")->wear();   // 獅蠻帶
    carry_object("/d/snowkeep/npc/obj/heart_armor")->wear();   // 掩心甲
    carry_object("/obj/area/obj/kris")->wield();   // 短刀
}
