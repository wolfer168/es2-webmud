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

/* 江湖歷練（score: survive）：捕魚技巧每升到第 n 級給 n×30。
 * 江湖歷練還有打鬥等其他來源，不能拿總數來比，所以另外記下「已經領過到第幾級」
 * （skill_bonus/halieutics_survive），升級時把沒領過的等級一併補上：
 * 領過 done 級、現在 lv 級，補 30 × (done+1 到 lv 的等級總和) = 15 × (lv(lv+1) - done(done+1))。 */
void skill_advanced(object me, string skill)
{
    int lv, done, gain;

    if( !userp(me) ) return;
    lv = me->query_skill("halieutics", 1);
    done = me->query("skill_bonus/halieutics_survive");
    if( lv <= done ) return;

    gain = 15 * (lv * (lv + 1) - done * (done + 1));
    me->set("skill_bonus/halieutics_survive", lv);
    me->gain_score("survive", gain);
}
