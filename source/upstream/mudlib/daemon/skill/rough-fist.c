/*---
description: 粗野拳法（NEW 新版武功寫法）。野羊山三當家無師自通的空手拳腳，招名取自十三靈的名號，
             出手卻東一拳西一腳；打中時有機會大吼震住對手。目前只有 NPC 會。
             設計見 docs/martial_arts/共通_粗野拳法.md。
---*/
#include <ansi.h>
#include "/std/martial_art.h"

inherit "/std/martial_art";

private void create()
{
    seteuid(getuid());

    art_id    = "rough-fist";
    art_name  = "粗野拳法";
    art_usage = "unarmed";
    art_desc  = "野羊山三當家無師自通的拳腳功夫。招名取自十三靈的名號，"
                + "聽來像是名門正派的絕學，可真動起手來卻是東一拳西一腳，"
                + "沙土、頭槌、巴掌什麼都往人身上招呼。";
    art_bonus = 0;

    moves = ({
        ([ "name": "金烏墜地", "lvl": 0, "attack": 7, "defense": 4, "force": 0, "bonus": 0, "damage_type": "瘀傷",
           "action": "$N左拳朝東虛打一記﹐人卻轉身往西﹐「金烏墜地」一頭撞向$n的$l" ]),
        ([ "name": "青蛛結網", "lvl": 0, "attack": 6, "defense": 5, "force": 0, "bonus": 0, "damage_type": "瘀傷",
           "action": "$N十指亂抓亂撈﹐「青蛛結網」似的纏上身來﹐一膝頂向$n的$l" ]),
        ([ "name": "濁魚攪水", "lvl": 5, "attack": 7, "defense": 3, "force": 1, "bonus": 0, "damage_type": "瘀傷",
           "action": "$N抓起地上一把沙土﹐「濁魚攪水」往$n臉上一揚﹐跟著一腳踹向$n的$l" ]),
        ([ "name": "大鵬展翅", "lvl": 10, "attack": 8, "defense": 1, "force": 2, "bonus": 10, "damage_type": "瘀傷",
           "action": "$N兩臂亂揮像隻瘋雞﹐「大鵬展翅」整個人撲上去﹐雙肘亂搗$n的$l" ]),
        ([ "name": "赤魈攀樹", "lvl": 20, "attack": 6, "defense": 6, "force": 1, "bonus": 5, "damage_type": "割傷",
           "action": "$N抓耳撓腮蹦上蹦下﹐「赤魈攀樹」猴兒似的竄到跟前﹐一爪抓向$n的$l" ]),
        ([ "name": "旱魃出世", "lvl": 30, "attack": 7, "defense": 4, "force": 1, "bonus": 5, "damage_type": "瘀傷",
           "action": "$N閉著眼大吼一聲﹐使出「旱魃出世」﹐不管不顧地雙拳亂掄砸向$n的$l" ]),
    });

    art_entry     = 10;
    art_entry_msg = "你把這套野路子拳腳翻來覆去地練熟了﹐招名雖然取得氣派﹐實際使出來照樣亂七八糟。\n";

    ma_coef  = 10;
    mm_start = 30;
    mm_minus = 29;
    mm_coef  = 10;

    DAEMON_D->register_skill_daemon("rough-fist");
    setup();
}

/* 目前只有 NPC 會；玩家沒有人肯傳授（使用者指示，2026-11-24）。 */
int valid_learn(object me)
{
    return notify_fail("這套野路子沒有師父，沒人能教你。\n");
}

/* 澤獸驚雷：打中並造成傷害後，機率 20% × 粗野拳法等級 ÷ 200，大吼震住對手，對手停頓 2 回合。 */
void after_strike(object me, object opponent, object weapon, mapping m, int damage)
{
    if( !objectp(opponent) || damage <= 0 ) return;
    if( random(100) >= scaled_chance(me, 20) ) return;
    message_vision(HIW "$N忽然仰頭大吼一聲﹐一聲「澤獸驚雷」震得$n兩耳嗡嗡作響﹐一時愣在當場。\n" NOR,
        me, opponent, 1);
    opponent->start_busy(2);
}
