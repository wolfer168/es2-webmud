// /custom/legacy_npc/zhang_jun_ren.c — 舊站 NPC：張俊仁（Zhang jun ren）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：鬼洞；房間：—。
尚未製作的裝備（先空著）：太陽大鵬巨神劍(Sun colosus sword of eagle)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("張俊仁", ({ "zhang jun ren", "zhang", "ren" }));
    set("title", "封山派弟子");
    set_race("human");
    set_class("fighter");
    set_level(40);
    set("gender", "male");
    set("age", 45);
    set("long",
        "張俊仁是封山劍派掌門人柳東蘆的得意門生，雖然有些大器晚成，但是\n"
        "近年來行走江湖之中嚴守封山劍派門規，也算得上是一位大俠了。\n");
    set("custom_faction", "fighter.fonxan");   // 封山派（docs/martial_arts/門派武功對照表.md）
    set_power("B");
    setup();
    carry_object("/d/mengjia/npc/obj/red_dust_legs")->wear();   // 風塵腿護
    carry_object("/d/wutang/npc/obj/blue_cloth")->wear();   // 青布衣
    carry_object("/d/ziyan/npc/obj/steel_chain_armor")->wear();   // 鋼戰甲
}
