// /custom/legacy_npc/ling_yun_yu.c — 舊站 NPC：淩筠語（Ling yun-yu）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：未能判定；房間：—。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("淩筠語", ({ "ling yun-yu", "ling", "yun-yu" }));
    set_race("human");
    set_class("commoner");
    set_level(20);
    set("gender", "female");
    set("age", 25);
    set("long",
        "她穿著一身藍，衣物上還有玫瑰的\n"
        "刺繡。她的臉透出淡淡的紅潤，\n"
        "那只有到到肩膀的短髮也有著淡淡的紅棕色。她曾經是位傑出的藥\n"
        "師，可是卻一直醫不好母親的怪病，說也奇怪，他母親當初從森林\n"
        "裡回來後的隔天身上就發出黑斑，在森林裡沒受傷也沒吃過不知名\n"
        "草藥，過了一週便去世了。此後便前往天朝學習各種藥品，曾跟著\n"
        "聶晟學習過。\n");
    set_power("B");
    setup();
    carry_object("/d/baihua/npc/obj/shennong_dagger")->wield();   // 神農匕
}
