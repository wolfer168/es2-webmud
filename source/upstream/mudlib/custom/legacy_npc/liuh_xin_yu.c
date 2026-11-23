// /custom/legacy_npc/liuh_xin_yu.c — 舊站 NPC：柳新雨（Liuh xin yu）。
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
    set_name("柳新雨", ({ "liuh xin yu", "liuh", "yu" }));
    set("title", "封山派弟子");
    set("nickname", "風雨雙俠");
    set_race("human");
    set_class("fighter");
    set_level(30);
    set("gender", "male");
    set("age", 25);
    set("long",
        "柳新雨是前武林盟主─封山劍派掌門柳東蘆的次子，近年來武功、聲望都\n"
        "漸漸在武林中嶄露頭角，和他的哥哥柳淳風合稱「風雨雙劍」，但是因為\n"
        "他們為人正派，行俠仗義，所以大家都尊稱這兩個人為「風雨雙俠」。\n");
    set("custom_faction", "fighter.fonxan");   // 封山派（docs/martial_arts/門派武功對照表.md）
    set_power("A");
    setup();
    carry_object("/d/npc/obj/cloud_boots")->wear();   // 流雲靴
    carry_object("/d/npc/obj/lion_belt")->wear();   // 獅蠻帶
    carry_object("/d/wutang/npc/obj/blue_cloth")->wear();   // 青布衣
    carry_object("/d/shuiyue/npc/obj/colosus_sword")->wield();   // 巨劍
}
