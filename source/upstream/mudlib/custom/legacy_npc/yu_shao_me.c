// /custom/legacy_npc/yu_shao_me.c — 舊站 NPC：語小梅（Yu shao me）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：未能判定；房間：—。
尚未製作的裝備（先空著）：虹綢帶(Rainbow belt)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("語小梅", ({ "yu shao me", "yu", "me" }));
    set_race("human");
    set_class("thief");
    set_level(25);
    set("gender", "female");
    set("age", 15);
    set("long",
        "她擦了擦從額頭上流下的汗水, 一臉焦急地望著草原的彼端... 一張鵝蛋瓜子\n"
        "臉, 透著些許的緋紅, 兩顆可愛的小虎牙咬著下唇, 你見到她苦惱的模樣, 不\n"
        "禁有些心疼...。\n");
    set_power("B");
    setup();
    carry_object("/d/npc/obj/white_dress")->wear();   // 白綢羽衫
    carry_object("/d/npc/obj/black_iron_dagger")->wield();   // 黑鋼短刃
}
