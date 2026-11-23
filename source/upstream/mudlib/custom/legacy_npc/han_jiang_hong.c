// /custom/legacy_npc/han_jiang_hong.c — 舊站 NPC：韓江洪（Han jiang hong）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：尚書府；房間：西廂房。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("韓江洪", ({ "han jiang hong", "han", "hong" }));
    set("title", "史部尚書");
    set_race("human");
    set_class("scholar");
    set_level(20);
    set("gender", "male");
    set("age", 85);
    set("long",
        "你面前的這位精神不振，一身是病的老者就是史部尚書韓江洪了，他不\n"
        "僅通曉天文地理，正史野傳，而且他的書法字畫也都是當今一絕，可謂\n"
        "是千金難求。近年來他的身體每況日下，若不是聖上屢次挽留，他可能\n"
        "早就告老還鄉，過著逗鵝戲竹的生活啦。\n");
    set_power("B");
    setup();
    carry_object("/d/wutang/npc/obj/jeweled_shortsword")->wield();   // 鑲玉短劍
    carry_object("/custom/weapon/sword/jade_sword")->wield("secondhand sword");   // 冷玉寶劍
    carry_object("/d/lee/npc/obj/crystal_ring")->wear();   // 水晶戒指
    carry_object("/d/swaylan/buxuan/npc/obj/snakeskin_boots")->wear();   // 青蟒靴
    carry_object("/custom/armor/cloth/dragon_cloth")->wear();   // 蟠龍朝服
    carry_object("/custom/armor/head/jade_hat")->wear();   // 綠玉頂戴
}
