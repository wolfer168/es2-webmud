// /d/qiaoyin/npc/yin_euyen.c — 舊站 NPC：陰雨巖（Yin euyen）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：喬陰縣；房間：—。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("陰雨巖", ({ "yin euyen", "yin", "euyen" }));
    set_race("human");
    set_class("fighter");
    set_level(20);
    set("gender", "male");
    set("age", 45);
    set("long",
        "陰雨巖是個相貌溫和的中年儒生，曾經中過舉人，但是做官不到半年就因為\n"
        "得罪長官而辭官回鄉，他後來棄文從武，在喬陰縣一帶的武林算得上是個人\n"
        "物。\n");
    set_power("C");
    setup();
    carry_object("/obj/cloth")->wear();   // 布衣
    carry_object("/obj/area/obj/leather_whip")->wield();   // 皮鞭
}
