/*---
description: 青邪杖法（NEW 新版武功寫法）。哭笑門的看家杖法，可用單手杖、雙手杖，也可 enable 在招架上。
             招式與招架敘述取自「劉乙忘玄 vs 韓笑」對戰紀錄，設計見 docs/martial_arts/哭笑門_青邪杖法.md。
---*/
#include <ansi.h>
#include "/std/martial_art.h"

inherit "/std/martial_art";

private void create()
{
    seteuid(getuid());

    art_id    = "chin_staff";
    art_name  = "青邪杖法";
    art_usage = "twohanded staff";
    art_desc  = "哭笑門的看家杖法，攻守兼備而偏重防守；招式看似瘋癲無章，"
                + "杖頭所向卻處處暗藏殺機。單手杖、雙手杖皆可施展，也能用來招架。";
    art_bonus = 0;

    /* lvl 是解鎖等級：學成時就是 20 級，所以前四招一開始就會，殺招要練到 50 級。 */
    moves = ({
        ([ "name": "雲散獨不笑", "lvl": 0, "attack": 7, "defense": 5, "force": 2, "bonus": 0, "damage_type": "瘀傷",
           "action": "$N手中$w一轉﹐杖頭突然一招『雲散獨不笑』直直朝$n$l撞去" ]),
        ([ "name": "擺頭嘲月老", "lvl": 0, "attack": 7, "defense": 6, "force": 2, "bonus": 0, "damage_type": "瘀傷",
           "action": "$N一杖橫掃﹐正是一招『擺頭嘲月老』重重掄向$n$l" ]),
        ([ "name": "一怒摧山倒", "lvl": 0, "attack": 6, "defense": 2, "force": 4, "bonus": 10, "damage_type": "瘀傷",
           "action": "$N提起蠻力﹐一招『一怒摧山倒』朝$n$l狠狠擊了下去" ]),
        ([ "name": "傲佔青天腰", "lvl": 20, "attack": 8, "defense": 4, "force": 3, "bonus": 5, "damage_type": "瘀傷",
           "action": "$N將$w一頂﹐單手橫甩﹐一招『傲佔青天腰』$w甩向$n$l" ]),
        ([ "name": "亂杖碎天山", "lvl": 50, "attack": 9, "defense": 3, "force": 4, "bonus": 15, "damage_type": "瘀傷",
           "weight": 3,
           "action": "$N一聲清嘯﹐殺招『亂杖碎天山』﹐十二招錯綜杖法連續擊向$n$l" ]),
    });

    art_entry     = 20;
    art_entry_msg = "你終於練成了青邪杖法。\n";

    ma_coef  = 10;
    mm_start = 30;
    mm_minus = 29;
    mm_coef  = 10;

    DAEMON_D->register_skill_daemon("chin_staff");
    setup();
}

#define REFLECT_ART_LEVEL 90    // 反震：青邪杖法幾級起
#define REFLECT_FORCE_LEVEL 100 // 反震：大邪心法幾級起
#define TICK_SECS 2             // 1 tick = 2 秒
#define PERFORM_MIN 200         // perform 需要的精或氣（目前值）
/* 單手杖、雙手杖、招架。 */
int valid_enable(string usage)
{
    return usage == "staff" || usage == "twohanded staff" || usage == "parry";
}

/* 學習條件：哭笑門弟子。 */
int valid_learn(object me)
{
    if( !is_faction(me, "fighter.huge") )
        return notify_fail("你不是哭笑門弟子﹐青邪杖法的路數你學不來。\n");
    return 1;
}

/* 招架：拆招敘述（$n 是招架者，$N 是攻擊者）。沒有拿杖時用系統預設敘述。 */
string parry_message(object me, object attacker, int full)
{
    object w;
    string wn;

    w = me->query_temp("weapon/twohanded staff");
    if( !objectp(w) ) w = me->query_temp("weapon/staff");
    if( !objectp(w) ) return 0;
    wn = w->name();
    return ({
        "$n口中喃喃有聲﹐將手中的" + wn + "舞得密不透風﹐狠狠震開$N的兵刃",
        "$n連聲怪叫﹐勢若瘋癲﹐揮舞著" + wn + "擊開$N的兵刃",
        "$n眼露兇光﹐手中" + wn + "狂砸亂掃﹐竟打散了$N的攻勢",
        "$n一聲虎吼﹐手中" + wn + "猛擊而下﹐撞開$N手中兵刃",
        "$n在生死存亡之際﹐陡然暴起一股蠻力﹐將$N的兵刃打偏",
    })[random(5)];
}

/* 反震（使用者定案，2026-11-17）：青邪杖法 90 級起，內功 enable 大邪心法且大邪心法 100 級起，
 * 格擋成功（含完全擋下）有 青邪杖法/400 的機會反震，
 * 對手損失 大邪心法/4 ～ 大邪心法/3 點氣。等對方這一擊的訊息顯示完再反震。 */
void do_reflect(object me, object attacker)
{
    int f, dmg;

    if( !objectp(me) || !objectp(attacker) || !living(me) || !attacker->is_character() ) return;
    if( environment(me) != environment(attacker) ) return;

    f = me->query_skill("huge force", 1);
    dmg = f / 4 + random(f / 3 - f / 4 + 1);
    message_vision(HIW "$N受到$n霸道的大邪真氣反震！\n" NOR, attacker, me);
    attacker->receive_damage(dmg, me, me);
    if( objectp(attacker) ) show_status(attacker, kee_ratio(attacker));
}

void parry_success(object me, object attacker, int full)
{
    int sk;

    if( !objectp(attacker) || !attacker->is_character() ) return;
    sk = me->query_skill(art_id, 1);
    if( sk < REFLECT_ART_LEVEL ) return;
    if( me->skill_mapped("force") != "huge force" ) return;
    if( me->query_skill("huge force", 1) < REFLECT_FORCE_LEVEL ) return;
    if( random(400) >= sk ) return;
    call_out("do_reflect", 0, me, attacker);
}

/* ------------------------------------------------------------------
 * perform（使用者定案，2026-11-19）：perform staff:<招> [on 目標]，雙手杖用 perform twohanded staff:<招>。
 *   crazy  殘蟻瘋魔杖：連出 1 + 青邪杖法/50 招，每招都是一般出手（由戰鬥系統判定閃躲格擋，照常耗精）；
 *          發動時消耗目前精的 1/10；冷卻 2 tick。
 *   stun   哭笑不得也：必中，對手停頓 2 tick；消耗氣上限的 1/20；冷卻 1 tick。
 *   hide   殘蟻逐食杖：必中，當下 青邪杖法/2 的傷害；2～4 tick 後依雙方膂力決定是否爆發
 *          青邪杖法 ～ 青邪杖法×1.5 ＋ 自己膂力 的傷害（不可閃躲、格擋，可被護甲值抵抗，
 *          護甲值只算天生與法術等附加的、不含裝備）；消耗氣上限的 1/20；冷卻 1 tick。
 * crazy 要精（目前值）至少 200，stun、hide 要氣（目前值）至少 200；都要手持杖、正在戰鬥。
 * 指令：perform chin_staff:crazy（單手杖、雙手杖都適用；cmds/std/perform.c 使用者同意，2026-11-19）。
 * ------------------------------------------------------------------ */

private object pick_target(object me, object target)
{
    object ob, *enemies;

    enemies = filter(me->query_enemy(), (: objectp($1) :));
    if( !sizeof(enemies) ) return 0;
    if( !objectp(target) ) return enemies[0];
    foreach(ob in enemies)
        if( ob == target ) return target;
    return 0;
}

private object staff_in_hand(object me)
{
    object w;

    if( objectp(w = me->query_temp("weapon/twohanded staff")) ) return w;
    return me->query_temp("weapon/staff");
}

private int can_follow(object me, object victim)
{
    return objectp(me) && objectp(victim) && living(me) && living(victim)
        && environment(me) == environment(victim);
}

/* 天生與法術等附加的護甲值：目前的護甲值扣掉穿戴的防具、手持武器提供的部分。 */
private int natural_armor(object ob)
{
    int a, part_armor;
    mapping eq, prop;
    string key;
    object item;

    a = ob->query_temp("apply/armor");
    if( mapp(eq = ob->query_temp("armor")) )
        foreach( key, item in eq )
            if( objectp(item) && mapp(prop = item->query("apply_armor/" + key)) )
                a -= prop["armor"];
    if( mapp(eq = ob->query_temp("weapon")) )
        foreach( key, item in eq )
            if( objectp(item) && mapp(prop = item->query("apply_weapon/" + key)) )
                a -= prop["armor"];
    return a > 0 ? a : 0;
}

/* crazy：殘蟻瘋魔杖。 */
private int do_crazy(object me, object victim, object weapon)
{
    int i, n;

    message_vision(BLU "$N一式" HIR "【殘蟻瘋魔杖】" NOR BLU "﹐雙臂肌肉暴起﹐向$n發起瘋狂的攻擊！\n" NOR, me, victim);
    n = 1 + me->query_skill(art_id, 1) / 50;
    for( i = 0; i < n; i++ ) {
        if( !can_follow(me, victim) ) break;
        special_hit(me, victim, weapon, pick_move(me), 100, 100, 0);   // 隨機一招，照一般出手耗精
    }
    return 1;
}

/* stun：哭笑不得也。 */
private int do_stun(object me, object victim, object weapon)
{
    message_vision("$N怪叫一聲豎起手中杖使出" HIY "【哭笑不得也】" NOR "﹐凝聚週身氣力向地面狠狠一砸！\n", me, victim);
    message_vision(CYN "$n下盤不穩﹐被震了個正著﹐一屁股坐倒在地上。\n" NOR, me, victim);
    victim->start_busy(2);
    return 1;
}

/* hide 的爆發：2～4 tick 後依雙方膂力決定。 */
void hide_burst(object me, object victim)
{
    int sk, dmg, armor;

    if( !can_follow(me, victim) ) return;
    if( random(me->query_attr("str")) <= random(victim->query_attr("str")) ) {
        tell_object(victim, BLU "你壓制了體內的大邪氣勁。\n" NOR);   // 只有目標看得到
        return;
    }

    sk = me->query_skill(art_id, 1);
    dmg = sk + random(sk / 2 + 1) + me->query_attr("str");
    armor = natural_armor(victim);
    dmg -= armor;
    message_vision(BLU "$N先前打入$n體內的大邪真氣忽然爆發開來﹐$n只覺周身氣血翻騰！\n" NOR, me, victim);
    if( dmg > 0 ) victim->receive_damage(dmg, me, me);
    if( objectp(victim) ) show_status(victim, kee_ratio(victim));
}

/* hide：殘蟻逐食杖。 */
private int do_hide(object me, object victim, object weapon)
{
    int sk;

    sk = me->query_skill(art_id, 1);
    message_vision(BLU "$N擬聚大邪真氣使出" HIW "【殘蟻逐食杖】" NOR BLU "﹐連擊$n周身大穴！\n" NOR, me, victim);
    victim->receive_damage(sk / 2, me, me);   // 必中
    if( objectp(victim) ) show_status(victim, kee_ratio(victim));
    if( can_follow(me, victim) )
        call_out("hide_burst", (2 + random(3)) * TICK_SECS, me, victim);
    return 1;
}

int perform_action(object me, string act, object target)
{
    object victim, weapon;
    int cost, cd;
    string name, res, label;

    switch( act ) {
    case "crazy": name = "殘蟻瘋魔杖"; break;
    case "stun":  name = "哭笑不得也"; break;
    case "hide":  name = "殘蟻逐食杖"; break;
    default:
        return notify_fail("青邪杖法沒有這種絕招。\n");
    }

    if( !objectp(weapon = staff_in_hand(me)) )
        return notify_fail("你必須手持杖才能施展" + name + "。\n");
    victim = pick_target(me, target);
    if( !objectp(victim) )
        return notify_fail("你並未與這個人交手。\n");

    if( me->query_temp("chin_staff/cd/" + act) > time() )
        return notify_fail("你的氣勁尚未平復﹐還施展不出" + name + "。\n");
    if( act == "crazy" ) {
        res = "gin"; label = "精";
        cost = me->query_stat("gin") / 10; cd = 2;
    }
    else {
        res = "kee"; label = "氣";
        cost = me->query_stat_maximum("kee") / 20; cd = 1;
    }
    if( me->query_stat(res) < PERFORM_MIN || me->query_stat(res) <= cost )
        return notify_fail("你的" + label + "不足﹐施展不出" + name + "。\n");

    me->consume_stat(res, cost);
    me->set_temp("chin_staff/cd/" + act, time() + cd * TICK_SECS);

    switch( act ) {
    case "crazy": return do_crazy(me, victim, weapon);
    case "stun":  return do_stun(me, victim, weapon);
    default:      return do_hide(me, victim, weapon);
    }
}
