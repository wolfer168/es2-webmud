// /d/kangping/npc/liuh_chuen_fon.c — 舊站 NPC：柳淳風（Liuh chuen-fon）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：康平村；房間：小客店。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("柳淳風", ({ "liuh chuen-fon", "liuh", "chuen-fon" }));
    set("nickname", "風雨雙俠");
    set_race("human");
    set_class("fighter");
    set_level(30);
    set("gender", "male");
    set("age", 25);
    set("long",
        "柳淳風是前武林盟主─封山劍派掌門柳東蘆的長子，同時也是封山劍派的\n"
        "大弟子，柳淳風近年來武功、聲望都漸漸在武林中嶄露頭角，和他的弟弟\n"
        "柳新雨合稱「風雨雙劍」，但是因為他們為人正派，行俠仗義，所以大家\n"
        "都尊稱這兩個人為「風雨雙俠」。\n");
    set("custom_faction", "fighter.fonxan");   // 封山派（docs/martial_arts/門派武功對照表.md）
    set_power("A");
    setup();
    carry_object("/obj/cloth")->wear();   // 布衣
    carry_object("/obj/area/obj/broadsword")->wield();   // 闊劍
}
