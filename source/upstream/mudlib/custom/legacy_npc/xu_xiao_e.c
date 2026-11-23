// /custom/legacy_npc/xu_xiao_e.c — 舊站 NPC：徐小惡（Xu xiao e）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：黃家鏢局；房間：—。
門派「要做」尚未列入門派武功對照表，先不設門派記號。
尚未製作的裝備（先空著）：精鋼短刀(Steel kris)、大斗笠(Big cap)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("徐小惡", ({ "xu xiao e", "xu" }));
    set("nickname", "太湖雙惡");
    set_race("human");
    set_class("thief");
    set_level(25);
    set("gender", "female");
    set("age", 55);
    set("long",
        "她正是江湖上最令人髮指的惡盜「太湖雙惡」中的「風騷徐娘」徐小惡。\n"
        "據江湖傳聞, 三十年前她與丈夫白常惡在太湖邊打劫犯案, 殺人越貨, 著\n"
        "實闖下不小的名號! 後來與當時黃家鏢局的總鏢頭黃彥發生衝突, 搶走黃\n"
        "彥保下的一支大鏢, 黃彥一怒之下於是下戰書約定太湖生死相鬥! 白徐夫\n"
        "婦與黃彥相鬥一天一夜, 雙方疲狽不堪, 勝負難分, 但最後黃彥竟出人意\n"
        "料的太皇弓起, 鳳頭箭搭, 一箭帶走白常惡一命,\n");
    set_power("B");
    setup();
    carry_object("/custom/weapon/blade/black_kris")->wield();   // 黑風刀
    carry_object("/d/npc/obj/water_dragon_girdle")->wear();   // 蛟龍帶
    carry_object("/d/lee/npc/obj/tight_cloth")->wear();   // 緊身衣
}
