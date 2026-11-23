// /custom/legacy_npc/sun_yi.c — 舊站 NPC：孫漪（Sun yi）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：虎刀門；房間：比武場。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("孫漪", ({ "sun yi", "sun", "yi" }));
    set("title", "虎刀門護衛");
    set_race("ashura");
    set_class("fighter");
    set_level(40);
    set("gender", "female");
    set("age", 15);
    set("long",
        "孫漪是韓笑十年前在山下遇到的一個修羅族女孩，後來韓笑成為虎刀門掌\n"
        "門便收她為義女。別被她嬌滴滴的樣子迷惑了，她在十三歲時就力克群雄\n"
        "成為虎刀門比武大會的武狀元。\n");
    set("custom_faction", "fighter.tiger");   // 虎刀門（docs/martial_arts/門派武功對照表.md）
    set_power("A");
    setup();
    carry_object("/custom/armor/finger/beast_ring")->wear();   // 獸面玉戒
    carry_object("/custom/armor/armor/shapeless_heartguard")->wear();   // 無形心鏡
    carry_object("/custom/armor/waist/girl_girth")->wear();   // 束腰帶
    carry_object("/custom/armor/feet/embroidery_boots")->wear();   // 繡花鞋
    carry_object("/d/npc/obj/white_dress")->wear();   // 白綢羽衫
    carry_object("/custom/weapon/blade/snow_blade")->wield();   // 啐雪大刀
}
