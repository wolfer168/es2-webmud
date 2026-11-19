/*---
description: 瘋虎刀法（NEW 新版武功寫法）。虎刀門雙手刀法；招式與追擊訊息取自
             「劉乙忘玄 vs 韓笑」對戰紀錄，設計見 docs/martial_arts/虎刀門_瘋虎刀法.md。
---*/
#include <ansi.h>
#include "/std/martial_art.h"

inherit "/std/martial_art";

private void create()
{
    seteuid(getuid());

    art_id    = "tiger-blade";
    art_name  = "瘋虎刀法";
    art_usage = "twohanded blade";
    art_desc  = "虎刀門的看家刀法，刀勢霸道、殺氣濃重，只攻不守；"
                + "功力催到十成時刀勢連綿不絕，一擊得手更會瘋狂追擊。";
    art_bonus = 0;

    moves = ({
        ([ "name": "平地生雷", "attack": 9, "defense": -3, "force": 8, "bonus": 10, "damage_type": "割傷",
           "action": "$N踏上一步﹐手中$w後發先至﹐一招平地生雷刀風掃出" ]),
        ([ "name": "百獸懾服", "attack": 10, "defense": -5, "force": 9, "bonus": 15, "damage_type": "割傷",
           "action": "$N一聲暴喝﹐手中$w一招百獸懾服直劈而出" ]),
        ([ "name": "乘風破浪", "attack": 11, "defense": -4, "force": 7, "bonus": 10, "damage_type": "割傷",
           "action": "$N步法疾行﹐狂轉﹐轉身間蓄勁於刃﹐忽地手中$w藉迴轉之勢一招乘風破浪迅捷無倫側砍而至" ]),
        ([ "name": "巨吼劈下", "attack": 8, "defense": -6, "force": 12, "bonus": 20, "damage_type": "割傷",
           "action": "$N一聲巨吼高舉手中$w狠命劈下﹐$n急忙回身一擋﹐不料一格之下$w竟脫手急旋﹐"
                     + "挾風雷之聲朝$n$l狠狠斬下" ]),
        ([ "name": "餓虎攔路", "attack": 8, "defense": 0, "force": 8, "bonus": 10, "damage_type": "割傷",
           "action": "$N將$w一立﹐使出餓虎攔路往$n$l斬下" ]),
        ([ "name": "風從虎勢", "attack": 9, "defense": -7, "force": 11, "bonus": 20, "damage_type": "割傷",
           "action": "$N突然拔起數丈﹐藉下墜力道加強刀勢﹐人在半空刀勢如風﹐風從虎勢一刀挾重勁朝$n當頭劈下" ]),
        ([ "name": "雷霆萬鈞", "attack": 7, "defense": -2, "force": 12, "bonus": 15, "damage_type": "割傷",
           "action": "$N待$n出招一瞬間﹐堆運內力灌刀身﹐刀光閃爍吼聲暴﹐雷霆萬鈞一式猛然朝$n的招式正面迎上" ]),
        ([ "name": "霧裡藏刀", "attack": 12, "defense": -3, "force": 8, "bonus": 15, "damage_type": "割傷",
           "action": "$N猛然一刃劈地﹐塵土飛揚霧朦朧﹐迷濛中$w無聲無息朝$n欺身而至竟是瘋虎刀招至陰一式霧裡藏刀" ]),
    });

    art_entry     = 30;
    art_entry_threshold = 50000;
    art_entry_msg = "你對瘋虎刀法已經有初步掌握。\n";

    ma_coef  = 10;
    mm_start = 30;
    mm_minus = 30;
    mm_coef  = 10;

    DAEMON_D->register_skill_daemon("tiger-blade");
    setup();
}

/* 學習條件：瘋虎功 30 級。 */
int valid_learn(object me)
{
    if( me->query_skill("tiger force", 1) < 30 )
        return notify_fail("你的瘋虎功火候未足﹐還駕馭不了瘋虎刀法的霸道刀勁。\n");
    return 1;
}

private int strike(object me, object opponent, object weapon)
{
    return COMBAT_D->fight(me, opponent, art_id, make_action(pick_move(me), 100), weapon);
}

/* 追擊：瘋虎刀法 90 級以上、出手功力十成，第一追必出；
 * 第一追打中並造成傷害，再出第二追。功力沒有設定時以遊戲預設的七成半計算（不會追擊）。 */
void attack_using(object me, object opponent, object weapon)
{
    int ratio, first_follow;

    if( !opponent ) return;
    strike(me, opponent, weapon);

    if( !(ratio = me->query("force_ratio")) ) ratio = 75;
    if( me->query_skill("tiger-blade", 1) < 90 || ratio < 100 ) return;
    if( !objectp(opponent) || !living(opponent) || environment(me) != environment(opponent) ) return;

    message_vision(HIR "$N一聲怒吼﹐勢如瘋虎般揮刀進擊！\n" NOR, me, opponent, 1);
    first_follow = strike(me, opponent, weapon);

    if( first_follow <= 0 || !objectp(opponent) || !living(opponent)
    ||  environment(me) != environment(opponent) ) return;
    message_vision(HIR "$N一擊得手威勢更不可當﹐雙眼血紅﹐瘋狂追擊！\n" NOR, me, opponent, 1);
    strike(me, opponent, weapon);
}
