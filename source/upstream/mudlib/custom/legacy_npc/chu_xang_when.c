// /custom/legacy_npc/chu_xang_when.c — 舊站 NPC：褚商魂（Chu xang-when）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：雪吟莊；房間：雪吟莊大廳。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    object blade;

    seteuid(getuid());
    set_name("褚商魂", ({ "chu xang-when", "chu", "xang-when" }));
    set("title", "雪吟莊大弟子");
    set_race("human");
    set_class("fighter");
    set_level(25);
    set("gender", "male");
    set("age", 35);
    set("long",
        "褚商魂是雪吟莊莊主的大弟子﹐也是他的養子﹐不但武藝出眾﹐而且\n"
        "寫得一手好字。雪吟莊作為當今的武林盟主，也有出售一些供江湖中\n"
        "各個幫會使用的物品，你可以用 list 指令查看。\n"
        "——\n"
        "褚商魂是雪吟莊莊主的大弟子﹐也是他的養子﹐不但武藝出眾﹐而且\n"
        "寫得一手好字。\n");
    set("custom_faction", "fighter.snow");   // 雪吟莊（docs/martial_arts/門派武功對照表.md）
    set_power("B");
    setup();
    carry_object("/d/lee/obj/yellow_jade_ring")->wear();   // 黃玉戒指
    carry_object("/custom/armor/feet/flying_boots")->wear();   // 飛天靴
    carry_object("/custom/armor/armor/white_rainbow_armor")->wear();   // 素虹軟甲
    carry_object("/custom/armor/cloth/silk_cloth")->wear();   // 天蠶寶衣
    // 長刀僉白是唯一的一把；被玩家打走（還在世上）時，褚商魂重生才改帶百鬼刀（2026-11-20）。
    blade = carry_object("/custom/weapon/blade/white_blade");   // 長刀僉白
    if( !objectp(blade) || environment(blade) != this_object() )
        blade = carry_object("/custom/weapon/blade/ghosts_blade");   // 百鬼刀
    if( objectp(blade) ) blade->wield();
}
