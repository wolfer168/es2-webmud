// /custom/legacy_npc/guard.c — 舊站 NPC：衛兵（Guard）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：白虎堂；房間：白虎堂內院。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("衛兵", ({ "guard" }));
    set_race("yaksa");
    set_class("soldier");
    set_level(20);
    set("gender", "male");
    set("age", 35);
    set("long",
        "他是看守軍情庫的衛兵，從他身上的裝備以及眼睛裡不時流露出\n"
        "的精芒看來，你還是不要隨便惹他的好。\n");
    set_power("B");
    setup();
    carry_object("/custom/armor/feet/buskins")->wear();   // 短靴
    carry_object("/d/npc/obj/iron_girth")->wear();   // 精鐵環扣
    carry_object("/custom/weapon/pike/huge_halberd")->wield();   // 方天畫戟
    carry_object("/d/npc/obj/iron_helmet")->wear();   // 鐵盔
    carry_object("/d/swaylan/npc/obj/ring_mail")->wear();   // 鎖子鎧
}
