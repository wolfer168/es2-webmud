// /d/fengcheng/npc/li_ru.c — 舊站 NPC：李儒（Li ru）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：柳家；房間：民宅。
尚未製作的裝備（先空著）：錦袍(Expensive cloth)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("李儒", ({ "li ru", "li", "ru" }));
    set_race("human");
    set_class("scholar");
    set_level(20);
    set("gender", "male");
    set("age", 85);
    set("long",
        "李儒乃是當地的名士，雖然曾是縣官，可是卻結識了不少江\n"
        "湖中人。相傳他的輕功獨步江湖，只可惜歲月不饒人，人到\n"
        "晚年身子是一天不如一天了。兩年前辭官回家養病。\n");
    set_power("B");
    setup();
    carry_object("/d/npc/obj/black_doli")->wear();   // 黑斗笠
    carry_object("/d/fengcheng/npc/obj/steel_longsword")->wield();   // 精鋼長劍
}
