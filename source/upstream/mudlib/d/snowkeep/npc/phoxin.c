// /d/snowkeep/npc/phoxin.c — 舊站 NPC：佛心（Phoxin）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：雪吟莊；房間：天井。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("佛心", ({ "phoxin" }));
    set("title", "殺手");
    set_race("human");
    set_class("thief");
    set_level(50);
    set("gender", "male");
    set("age", 55);
    set("long",
        "殺手佛心是個四十多歲的中年僧人，一身金線僧袍纖塵不染。佛心少年時\n"
        "就是個殺人無數的冷血殺手，後來因為發生了一件慘事而出家為僧，立誓\n"
        "從此不殺一人，但是他仍然是江湖上聞名喪膽的可怕殺手，他只替金主將\n"
        "敵人打倒廢去武功，並不殺死對方，據他的說法是盼望金主看到仇家的慘\n"
        "狀能夠忽發善心，就此了結一樁血海深仇。\n"
        "佛心的武功深不可測，尤其擅長短兵刃與擒拿格鬥之術，據說和江湖上武\n"
        "功最高的六賢只在伯仲之間，連當今武林盟主都曾有「一丈之外，我不如\n"
        "金籟，一丈之內，我不如佛心」之嘆，由此可見此人之驚人藝業。\n");
    set_power("S");
    setup();
    carry_object("/d/snowkeep/npc/obj/gold_robe")->wear();   // 金線僧袍
    carry_object("/d/snowkeep/npc/obj/bamboo_legs")->wear();   // 青竹腿護
    carry_object("/d/snowkeep/npc/obj/dark_armor")->wear();   // 闇之絲甲
    carry_object("/d/npc/obj/psakaml")->wear();   // 金剛念珠
    carry_object("/d/snowkeep/npc/obj/cool_iron_dagger")->wield();   // 寒鐵匕首
    carry_object("/d/snowkeep/npc/obj/wicked_dagger")->wield("secondhand dagger");   // 「雨毒」
}
