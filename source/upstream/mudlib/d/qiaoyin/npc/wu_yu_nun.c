// /d/qiaoyin/npc/wu_yu_nun.c — 舊站 NPC：無慾師太（Wu-yu nun）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：哭笑門；房間：—。
尚未製作的裝備（先空著）：僧衣(Robe)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("無慾師太", ({ "wu-yu nun", "wu-yu", "nun" }));
    set("title", "太陰門弟子");
    set_race("human");
    set_class("monk");
    set_level(30);
    set("gender", "female");
    set("age", 85);
    set("long",
        "無慾師太是太陰門慘招滅門之災時的唯一的幸存者，然而，太陰門的大部份武\n"
        "功都失傳了，她也在被哭笑門追殺，幸而得到柳東蘆的保護才得以在喬陰縣安\n"
        "身。\n");
    set_power("B");
    setup();
    carry_object("/d/npc/obj/psakaml")->wear();   // 金剛念珠
    carry_object("/d/qiaoyin/npc/obj/golden_buddha_duster")->wield();   // 金絲拂塵
}
