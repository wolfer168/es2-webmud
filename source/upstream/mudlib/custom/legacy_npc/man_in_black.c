// /custom/legacy_npc/man_in_black.c — 舊站 NPC：黑衣人（Man in black）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：雲棧市集；房間：客房。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("黑衣人", ({ "man in black", "man", "black" }));
    set_race("yenhold");
    set_class("thief");
    set_level(20);
    set("gender", "male");
    set("age", 8);
    set("long",
        "一個一身黑衣的神秘男子，那雙充滿殺氣的眼睛讓人不敢直視。\n");
    set_power("B");
    setup();
    carry_object("/d/ziyan/npc/obj/iron_rosary")->wear();   // 鐵佛珠
    carry_object("/d/npc/obj/black_doli")->wear();   // 黑斗笠
    carry_object("/d/qiaoyin/npc/obj/snake_bracers")->wear();   // 纏蛇護手
    carry_object("/d/lee/npc/obj/tight_cloth")->wear();   // 緊身衣
    carry_object("/custom/weapon/blade/blood_blade")->wield();   // 靈刀祭血
}
