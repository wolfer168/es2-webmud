// /custom/legacy_npc/taoist_master.c — 舊站 NPC：正閒道長（Taoist master）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：上清觀；房間：賓客室側房。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    object sword;

    seteuid(getuid());
    set_name("正閒道長", ({ "taoist master", "taoist", "master" }));
    set("title", "上清觀觀主");
    set("nickname", "乾坤一道");
    set_race("human");
    set_class("taoist");
    set_level(50);
    set("gender", "male");
    set("age", 65);
    set("long",
        "他正是上清觀觀主, 人稱渡盡劫者的正閒道長。據說此人在\n"
        "十九歲時因觀粉蝶撲戲而有所開悟, 首創上清觀劍法, 更在\n"
        "四十中旬突領鬼眾道經, 開始修行引神道篇。他的外表看起\n"
        "來有點肥短, 但聲如洪鐘, 臉似初嬰, 一點也不像個快要七\n"
        "十的老頭。\n");
    set_power("B");
    setup();
    carry_object("/custom/armor/cloth/taoist_robe")->wear();   // 道袍
    carry_object("/custom/armor/finger/clear_ring")->wear();   // 淨身戒
    // 儀陽劍是唯一的一把；被玩家打走（還在世上）時，正閒道長重生才改帶長劍（2026-11-20）。
    sword = carry_object("/custom/weapon/sword/yiyoung_sword");   // 儀陽劍
    if( !objectp(sword) || environment(sword) != this_object() )
        sword = carry_object("/obj/area/obj/longsword");   // 長劍
    if( objectp(sword) ) sword->wield();
}
