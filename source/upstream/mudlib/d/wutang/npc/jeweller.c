// /d/wutang/npc/jeweller.c — 五堂鎮 NPC：珍寶商人（依五堂鎮設計表）。

#include <ansi.h>
#include <npc.h>
inherit F_VILLAGER;
inherit F_VENDOR;

void init()
{
    ::init();
    add_action("do_vendor_list", "list");
}

/* 河魚腹珠抽獎（設計見 docs/FISHING_DESIGN.md）。機率合計 100%（單位：%）。
 * 欄位：獎品檔案, 數量, 機率, 類別（類別決定商人說的話與取得敘述）。 */
#define K_MONEY   0
#define K_BOOK    1
#define K_SCROLL  2
#define K_DUST    3
#define K_BAG     4
#define K_WEAPON  5

private mixed *PRIZES = ({
    ({ "/obj/money/gold",                                   10, 14, K_MONEY  }),
    ({ "/obj/books/book_of_five_meridians",                  1, 10, K_BOOK   }),
    ({ "/custom/item/scroll/blank",                       3000, 10, K_SCROLL }),
    ({ "/obj/dust",                                          1, 10, K_DUST   }),
    ({ "/custom/item/dragon_skin_bag",                       1,  5, K_BAG    }),
    ({ "/obj/books/canon_of_true_words",                     1,  5, K_BOOK   }),
    ({ "/custom/item/scroll/nature",                      1000,  5, K_SCROLL }),
    ({ "/custom/item/scroll/yang",                        1000,  5, K_SCROLL }),
    ({ "/custom/item/scroll/yin",                         1000,  5, K_SCROLL }),
    ({ "/custom/weapon/sword/fishy_sword",                   1,  5, K_WEAPON }),
    ({ "/custom/weapon/needle/dragon_needle",                1,  5, K_WEAPON }),
    ({ "/custom/weapon/blade/warlord_blade",                 1,  5, K_WEAPON }),
    ({ "/custom/weapon/staff/staff_of_wisdom",               1,  5, K_WEAPON }),
    ({ "/custom/weapon/axe/short_axe_of_bloodmoon",          1,  5, K_WEAPON }),
    ({ "/obj/money/sycee",                                   1,  1, K_MONEY  }),
    ({ "/custom/item/super_skin",                            1,  5, K_BAG    }),
});

private string *PRIZE_SAY = ({
    "好運道﹗這點小意思﹐拿去喝杯茶。",
    "這本舊書放著也是蒙塵﹐與你有緣就送你吧。",
    "這批符紙是道士寄放的﹐你拿去也許用得上。",
    "這東西可不是什麼好貨﹐收好別亂灑。",
    "這只袋子是寶貝﹐容得下不少東西。",
    "這件兵器有些來歷﹐好好珍惜。",
});

// $n 是珍寶商人、$N 是拿到獎品的玩家（用 message_vision，本人看到「你」）。
private string *PRIZE_EMOTE = ({
    "$n從錢箱裡數出一堆沉甸甸的錢財﹐遞到$N手中。",
    "$n從櫃底翻出一本泛黃的舊書﹐吹去灰塵遞給$N。",
    "$n從木匣取出一疊符紙﹐綁好放進$N手裡。",
    "$n神色古怪地遞過一個小紙包﹐叮嚀$N小心保管。",
    "$n解下腰間的布包﹐鄭重其事地放進$N手裡。",
    "$n從背後的暗格抽出一件兵器﹐雙手遞給$N。",
});

void do_draw(object who, object pearl);

/* 收下河魚腹珠就抽一次獎；別的東西不收。 */
int accept_object(object who, object ob)
{
    if( !ob->id("fish pearl") ) {
        command("say 這個我不收。");
        return 0;
    }
    call_out("do_draw", 1, who, ob);
    return 1;
}

/* 抽獎前先確認珠子真的交到商人手上（give 搬不進來就不抽），確認後立刻銷毀，
 * 不留在商人身上。玩家這時已經離開：珠子照樣銷毀、不抽獎（使用者定案，2026-11-22）。 */
void do_draw(object who, object pearl)
{
    int r, i, kind;
    string file;

    if( !objectp(pearl) || environment(pearl) != this_object() ) return;
    destruct(pearl);
    if( !who || environment(who) != environment() ) return;

    command("emote 接過腹珠﹐湊到窗邊對著光細細端詳。");
    command("say 嗯﹐珠子成色不錯﹐讓我看看今天的運氣。");

    r = random(100);
    for( i = 0; i < sizeof(PRIZES); i++ ) {
        r -= PRIZES[i][2];
        if( r < 0 ) break;
    }
    if( i >= sizeof(PRIZES) ) i = 0;
    file = PRIZES[i][0];
    kind = PRIZES[i][3];

    call_out("give_prize", 1, who, file, PRIZES[i][1], kind);
}

void give_prize(object who, string file, int amount, int kind)
{
    object prize;

    if( !who || environment(who) != environment() ) return;
    prize = new(file);
    if( !prize ) return;
    if( amount > 1 ) prize->set_amount(amount);

    command("say " + PRIZE_SAY[kind]);
    message_vision(CYN + PRIZE_EMOTE[kind] + "\n" NOR, who, this_object());
    if( !prize->move(who) ) {
        prize->move(environment());
        command("say 你身上放不下﹐東西我替你擱在地上了。");
    }
}

void create()
{
    seteuid(getuid());
    set_name("珍寶商人", ({ "jeweller", "merchant" }));
    set_race("human");
    set_class("commoner");
    set_level(10);
    set("age", 40);
    set("long", @LONG
在天朝各處收集珍寶的商人，不僅身懷異寶還頗有歷練。你可以用 list 看他賣些什麼，用 buy 購買。
LONG
    );
    set_skill("unarmed", 20);
    set_skill("dodge", 20);
    set_skill("parry", 20);
    // merchandise 的數字是庫存份數，價錢是各物品自己的 value。
    set("merchandise", ([
        "/custom/armor/finger/han_jade_ring" : 5,
        "/custom/armor/finger/white_jade_ring" : 5,
        "/d/lee/obj/yellow_jade_ring" : 5,
    ]));
    set_power("C");
    setup();
}
