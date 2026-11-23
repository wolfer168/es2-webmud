// /d/swaylan/lunmay/npc/may_lan_wu.c — 舊站 NPC：梅嵐武（May lan-wu）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：冷梅莊、文國縣；房間：冷梅莊前院、清水鄉。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("梅嵐武", ({ "may lan-wu", "may", "lan-wu" }));
    set("nickname", "追風劍");
    set_race("human");
    set_class("fighter");
    set_level(30);
    set("gender", "male");
    set("age", 25);
    set("long",
        "梅嵐武是冷梅莊莊主梅影風的長子，雖然只有二十多歲，但一手冷梅劍法已經\n"
        "盡得乃父真傳，江湖上的朋友送他一個外號叫做「追風劍」。梅嵐武相貌十分\n"
        "俊美，平常也頗為倜儻自喜，縣城裡不少姑娘都為他著迷，一聽說梅大公子進\n"
        "城，都會忍不住躲在樓上偷偷瞧上幾眼。\n");
    set("custom_faction", "fighter.lunmay");   // 冷梅莊（docs/martial_arts/門派武功對照表.md）
    set_power("B");
    setup();
    carry_object("/d/swaylan/lunmay/npc/obj/umber_robe")->wear();   // 繭綢長袍
    carry_object("/d/swaylan/lunmay/npc/obj/chain_shirt")->wear();   // 鎖鏈背心
    carry_object("/obj/area/obj/shortsword")->wield();   // 短劍
    carry_object("/obj/area/obj/longsword");   // 長劍
}
