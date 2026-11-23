// /d/snowkeep/npc/yu_pingyin.c — 舊站 NPC：魚平胤（Yu pingyin）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：雪吟莊；房間：後花園。
尚未製作的裝備（先空著）：牛皮短靴(Leather boots)、軟綢長袍(Silk robe)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("魚平胤", ({ "yu pingyin", "yu", "pingyin" }));
    set_race("human");
    set_class("fighter");
    set_level(20);
    set("gender", "male");
    set("age", 25);
    set("long",
        "魚平胤是雪吟山莊的少莊主﹐雖然生在雪吟山莊這樣的武林世家﹐但\n"
        "是他卻對學武不感興趣﹐因此在武學上的造詣遠不如魚鐵山的大弟子\n"
        "褚商魂﹐但是魚平胤天資極高﹐讀書時過目不忘﹐練武也是一點就通\n"
        "﹐許多武林中的高人都十分羨慕魚鐵山有這樣一個兒子。\n"
        "魚平胤對學武不感興趣﹐對道家長生之術卻十分著迷﹐若不是因為身\n"
        "為魚家唯一的獨子﹐可能早就入山尋仙去了。\n");
    set("custom_faction", "fighter.snow");   // 雪吟莊（docs/martial_arts/門派武功對照表.md）
    set_power("B");
    setup();
    carry_object("/d/snowkeep/npc/obj/purple_cloud_mail")->wear();   // 紫雲戰甲
    carry_object("/d/snowkeep/npc/obj/ironsword")->wield();   // 雛鐵劍
    carry_object("/obj/area/obj/leather_boot")->wear();   // 皮短靴
}
