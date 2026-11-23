// /custom/legacy_npc/madam_han.c — 舊站 NPC：韓夫人（Madam han）。
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
    set_name("韓夫人", ({ "madam han", "madam", "han" }));
    set_race("yaksa");
    set_class("commoner");
    set_level(1);
    set("gender", "female");
    set("age", 45);
    set("long",
        "韓夫人是韓龍從小青梅竹馬的玩伴，他們結褵已經有二十年的光\n"
        "景。讓韓夫人一直很苦惱的，就是到現在他們還沒有生下一兒半\n"
        "女。\n");
    set_power("C");
    setup();
    carry_object("/d/npc/obj/white_dress")->wear();   // 白綢羽衫
    carry_object("/custom/armor/neck/ruby_necklace")->wear();   // 紅寶石項鍊
}
