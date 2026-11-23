// /custom/legacy_npc/lu_jing.c — 舊站 NPC：魯驚（Lu jing）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：銅佛寺；房間：客房。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("魯驚", ({ "lu jing", "lu", "jing" }));
    set_race("human");
    set_class("soldier");
    set_level(25);
    set("gender", "male");
    set("age", 45);
    set("long",
        "一股冷到骨子里的殺氣讓你忍不住打起哆嗦來，眼前的漢子，寬胸闊背，\n"
        "手臉都是紫銅一般的顏色，像是長在日頭下曝曬，粗糙如砂礫的臉上透\n"
        "著股剽悍之氣，殺氣的來源卻是漢子身後的哪把巨槌，古樸的外型，已\n"
        "染成一片血黑色的槌頭。\n");
    set_power("B");
    setup();
    carry_object("/d/qiaoyin/npc/obj/battle_helm")->wear();   // 步軍戰盔
    carry_object("/d/qiaoyin/npc/obj/battle_armor")->wear();   // 步軍戰鎧
    carry_object("/custom/weapon/blunt/crasher_maul")->wield();   // 碎腦鎚
    carry_object("/d/npc/obj/clothboot")->wear();   // 皂步靴
    carry_object("/d/qiaoyin/npc/obj/cyan_cloth")->wear();   // 青布官服
}
