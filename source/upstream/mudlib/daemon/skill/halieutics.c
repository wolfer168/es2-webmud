/*---
description: 捕魚技巧（halieutics）。共通技能，在水邊用 fish 垂釣河魚時練習。
             設計見 docs/FISHING_DESIGN.md。
---*/
inherit SKILL;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("halieutics");
    setup();
}

/* 升級所需點數打一折（釣魚一次拿到的點數不多）。 */
int query_threshold_percent() { return 10; }

void skill_improved(object me, string skill)
{
    me->apply_restored_skill_progression(skill);
}

/* 江湖歷練（score: survive）：捕魚技巧每升到第 n 級給 n×30，
 * 以「累計應得 = 15 × 等級 × (等級 + 1)」補足差額，練過的等級也會一併補上。
 */
void skill_advanced(object me, string skill)
{
    int lv, target, cur;

    if( !userp(me) ) return;
    lv = me->query_skill("halieutics", 1);
    target = 15 * lv * (lv + 1);
    cur = me->query_score("survive");
    if( target > cur ) me->gain_score("survive", target - cur);
}
