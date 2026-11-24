/*---
description: 粗野刀法（NEW 新版武功寫法）。野羊山山賊自己東拼西湊的野路子刀法，招名全是亂搭的
             市井成語；可 enable 在刀法、左手刀法、雙握刀法與招架，格擋成功後有機會反劈一刀。
             目前只有 NPC 會，玩家無從學起。設計見 docs/martial_arts/共通_粗野刀法.md。
---*/
#include <ansi.h>
#include "/std/martial_art.h"

inherit "/std/martial_art";

private mapping counter_move;   // 格擋反擊專用的一招（不在一般招式裡）

private void create()
{
    seteuid(getuid());

    art_id    = "rough-blade";
    art_name  = "粗野刀法";
    art_usage = "blade";
    art_desc  = "野羊山草莽之輩胡亂偷學、東拼西湊出來的刀法。招式沒有半點章法，"
                + "名字更是信口亂謅，一股腦全是柴米油鹽的市井成語；"
                + "可是出手又狠又野，專往人意想不到的地方招呼。";
    art_bonus = 0;

    moves = ({
        ([ "name": "雞飛狗跳", "lvl": 0, "attack": 7, "defense": 4, "force": 0, "bonus": 0,
           "action": "$N兩腳亂蹦亂跳﹐東晃西竄﹐冷不防一招「雞飛狗跳」﹐$w橫劈$n的$l" ]),
        ([ "name": "三更半夜", "lvl": 0, "attack": 6, "defense": 5, "force": 0, "bonus": 0,
           "action": "$N悶不吭聲欺到近前﹐使出「三更半夜」﹐$w自暗裏悄悄抹向$n的$l" ]),
        ([ "name": "七上八下", "lvl": 5, "attack": 7, "defense": 2, "force": 1, "bonus": 5,
           "action": "$N$w高舉猛落﹐一刀快似一刀﹐「七上八下」亂砍一氣﹐總有一刀剁向$n的$l" ]),
        ([ "name": "柴米油鹽", "lvl": 10, "attack": 8, "defense": 3, "force": 1, "bonus": 5,
           "action": "$N掄起$w當柴火劈﹐「柴米油鹽」四刀連環﹐刀刀不離$n的$l" ]),
        ([ "name": "手忙腳亂", "lvl": 20, "attack": 6, "defense": 6, "force": 1, "bonus": 0,
           "action": "$N腳下一個踉蹌﹐似乎要摔﹐「手忙腳亂」中$w反手一撩﹐竟撩向$n的$l" ]),
        ([ "name": "狗急跳牆", "lvl": 30, "attack": 9, "defense": 1, "force": 2, "bonus": 15,
           "action": "$N怒吼一聲縱身躍起﹐一招「狗急跳牆」居高臨下﹐$w砸向$n的$l" ]),
    });

    counter_move = ([ "name": "吹鬍子瞪眼", "attack": 7, "defense": 3, "force": 1, "bonus": 0,
        "action": "$N格開來招﹐順勢一個「吹鬍子瞪眼」﹐$w劈頭反砍$n的$l" ]);

    art_entry     = 10;
    art_entry_msg = "你終於把這套東拼西湊的野路子刀法練得有模有樣﹐出刀雖亂﹐卻亂中帶狠。\n";

    ma_coef  = 10;
    mm_start = 30;
    mm_minus = 29;
    mm_coef  = 10;

    DAEMON_D->register_skill_daemon("rough-blade");
    setup();
}

/* 刀法、左手刀法、雙握刀法與招架都能用。 */
int valid_enable(string usage)
{
    return usage == "blade" || usage == "secondhand blade"
        || usage == "twohanded blade" || usage == "parry";
}

/* 目前只有 NPC 會；玩家沒有人肯傳授（使用者指示，2026-11-24）。 */
int valid_learn(object me)
{
    return notify_fail("這套野路子沒有師父，沒人能教你。\n");
}

/* 手上拿著哪一把刀（右手、左手、雙握）；沒有刀傳回 0。 */
private object blade_in_hand(object me)
{
    object w;
    string k;

    foreach(k in ({ "blade", "twohanded blade", "secondhand blade" }))
        if( objectp(w = me->query_temp("weapon/" + k)) ) return w;
    return 0;
}

/* 招架：拆招卸力敘述（$n 是招架者，$N 是攻擊者）。 */
string parry_message(object me, object attacker, int full)
{
    object w = blade_in_hand(me);
    string wn = objectp(w) ? w->name() : "雙手";

    if( full )
        return ({
            "$n手中" + wn + "胡亂一通亂揮﹐「七手八腳」竟把$N的攻勢全數擋了下來",
            "$n兩眼一閉大吼一聲﹐「三長兩短」地將" + wn + "橫在身前﹐硬生生擋住$N的攻勢",
            "$n扯開嗓門大罵﹐" + wn + "掄得風車也似﹐「雞零狗碎」地把$N的攻勢攪得七零八落",
        })[random(3)];
    return ({
        "$n手忙腳亂地舉起" + wn + "格擋﹐勉強架開了$N的攻勢",
        "$n怪叫一聲﹐" + wn + "胡亂往上一架﹐擋住了$N的部分攻勢",
        "$n縮頭縮腦地以" + wn + "硬架﹐總算化解了$N的一部分攻勢",
    })[random(3)];
}

/* 反擊：立即反劈一刀，傷害為普攻 80%，防具照樣減傷。 */
void counter_attack(object me, object attacker, object weapon)
{
    int ratio;

    if( !objectp(me) || !objectp(attacker) || !living(me) ) return;
    if( environment(me) != environment(attacker) ) return;
    if( blade_in_hand(me) != weapon ) return;

    special_hit(me, attacker, weapon, counter_move, 80, 100, 0);
}

/* 格擋成功（含完全擋下）後，機率 30% × 粗野刀法等級 ÷ 200 反擊一刀。 */
void parry_success(object me, object attacker, int full)
{
    object weapon;

    if( !objectp(attacker) ) return;
    if( !objectp(weapon = blade_in_hand(me)) ) return;
    if( random(100) >= scaled_chance(me, 30) ) return;
    // 等對方這一擊的訊息顯示完再反擊。
    call_out("counter_attack", 0, me, attacker, weapon);
}
