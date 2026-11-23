// /custom/legacy_npc/liu_feng.c — 舊站 NPC：柳風（Liu feng）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：天寒村；房間：『域水客棧』。
尚未製作的裝備（先空著）：錦袍(Expensive cloth)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("柳風", ({ "liu feng", "liu", "feng" }));
    set("title", "幻霧觀道士");
    set_race("malik");
    set_class("taoist");
    set_level(20);
    set("gender", "male");
    set("age", 335);
    set("long",
        "柳風是來自西部的幻霧觀道士，據說，他此番跟隨師父來到天朝是\n"
        "奉了巫首王的特命，也難怪他對天朝的書籍會感興趣。\n");
    set_power("B");
    setup();
    carry_object("/d/npc/obj/peachwood_sword")->wield();   // 桃木劍
    carry_object("/d/npc/obj/copper_hat")->wear();   // 青銅道冠
}
