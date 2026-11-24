/*---
description: 撼山鎚法（NEW 新版武功寫法）。共通鎚法，可用在單手鎚、左手鎚與雙手鎚：
             右手重、左手快、雙手合握另有一套蓄勁的打法。
             設計見 docs/martial_arts/共通_撼山鎚法.md。
---*/
#include <ansi.h>
#include "/std/martial_art.h"

inherit "/std/martial_art";

#define SKILL_ID     "quake hammer"
#define LEARN_STR    15     // 學習所需膂力（內部條件，文字不寫數字）
#define POINT_LEVEL  60     // 左點右落、蓄勁
#define QUAKE_LEVEL  90     // 雙鎚撼山、千鈞震地
#define POINT_PCT    130    // 左點右落：右手這一鎚的傷害 %
#define POINT_TIME   4      // 點位維持秒數（約兩回合）
#define CHARGE_PCT   15     // 蓄勁：每層加傷害 %
#define CHARGE_MAX   3      // 蓄勁最多幾層

/* 右手鎚（主手；只拿一柄單手鎚也用這四招）：重、慢。招名 HIY。 */
mapping *right_moves = ({
    ([ "name": "開山裂石", "attack": 5, "defense": 2, "force": 2, "bonus": 10, "damage_type": "瘀傷",
       "action": "$N沉腰坐馬﹐右手$w掄了個滿圓﹐一記「開山裂石」當頭砸向$n的$l" ]),
    ([ "name": "擂鼓驚雷", "attack": 6, "defense": 2, "force": 1, "bonus": 5, "damage_type": "瘀傷",
       "action": "$N踏步欺近使出「擂鼓驚雷」﹐$w呼的一聲擂向$n的$l" ]),
    ([ "name": "崩雲墜", "attack": 4, "defense": 1, "force": 2, "bonus": 15, "damage_type": "瘀傷",
       "action": "$N縱身躍起把$w高舉過頂﹐這一記「崩雲墜」居高臨下轟向$n的$l" ]),
    ([ "name": "撼岳", "attack": 5, "defense": 3, "force": 2, "bonus": 10, "damage_type": "瘀傷",
       "action": "$N擰腰轉胯把全身勁力送上右臂﹐正是「撼岳」﹐$w橫裏撞向$n的$l" ]),
});

/* 左手鎚（副手）：輕、快。招名 HIC。 */
mapping *left_moves = ({
    ([ "name": "叩關", "attack": 7, "defense": 3, "force": 1, "bonus": 0, "damage_type": "瘀傷",
       "action": "$N左手$w看似隨手一磕﹐這招「叩關」鎚頭已敲到$n的$l" ]),
    ([ "name": "點星", "attack": 8, "defense": 2, "force": 1, "bonus": 0, "damage_type": "瘀傷",
       "action": "$N左腕一抖使出「點星」﹐$w的鎚頭快如流星疾點$n的$l" ]),
    ([ "name": "截江", "attack": 6, "defense": 4, "force": 1, "bonus": 0, "damage_type": "瘀傷",
       "action": "$N側身讓開正面﹐「截江」左手$w斜裏一截﹐磕向$n的$l" ]),
    ([ "name": "回風", "attack": 7, "defense": 3, "force": 1, "bonus": 5, "damage_type": "瘀傷",
       "action": "$N左手$w順勢兜了個小圈﹐一式「回風」反手點向$n的$l" ]),
});

/* 雙手鎚（雙手合握）：沉、猛。招名 HIR。 */
mapping *two_moves = ({
    ([ "name": "千鈞壓頂", "attack": 5, "defense": 1, "force": 2, "bonus": 15, "damage_type": "瘀傷",
       "action": "$N雙手緊握$w高高掄起﹐「千鈞壓頂」挾著沉沉風聲砸向$n的$l" ]),
    ([ "name": "春雷搗臼", "attack": 5, "defense": 2, "force": 2, "bonus": 10, "damage_type": "瘀傷",
       "action": "$N雙臂一沉把$w當作石杵﹐使出「春雷搗臼」朝$n的$l直夯下去" ]),
    ([ "name": "捲地狂飆", "attack": 4, "defense": 2, "force": 2, "bonus": 15, "damage_type": "瘀傷",
       "action": "$N握住$w尾端甩開一個大圈﹐這招「捲地狂飆」貼地橫掃$n的$l" ]),
    ([ "name": "倒拔山根", "attack": 6, "defense": 1, "force": 2, "bonus": 10, "damage_type": "瘀傷",
       "action": "$N弓身沉膝﹐$w自下而上猛地一掀﹐正是「倒拔山根」﹐直衝$n的$l" ]),
});

private void create()
{
    seteuid(getuid());

    art_id    = SKILL_ID;
    art_name  = "撼山鎚法";
    art_usage = "blunt";
    art_desc  = "一套從打鐵功夫化出來的鎚法：左鎚輕點、右鎚重落，雙鎚齊中時能震住對手；"
                + "雙手合握重鎚時則蓄勁待發，一鎚重似一鎚。";
    art_bonus = 0;
    art_name_color = HIY;
    moves = right_moves;

    /* 練成 20 級（同迅雷斧法：累積到門檻時 gain，學成那一級起給獎勵）。 */
    art_entry        = 20;
    art_entry_reward = 1;
    art_entry_msg    = "你終於練成了撼山鎚法﹐無論雙鎚分持還是重鎚合握﹐揮動之間都隱隱有開山裂石之勢。\n";
    level_msgs = ([
        POINT_LEVEL: "你漸漸摸清了左鎚點、右鎚落的訣竅﹐單掄重鎚時也懂得蓄勁待發了。\n",
        QUAKE_LEVEL: "你終於悟出撼山鎚法中的【雙鎚撼山】與【千鈞震地】﹗\n",
    ]);

    /* 每級武術造詣 等級 × 10；41 級起武學之道 (等級 - 40) × 10（同迅雷斧法）。 */
    ma_coef  = 10;
    mm_start = 41;
    mm_minus = 40;
    mm_coef  = 10;

    DAEMON_D->register_skill_daemon(SKILL_ID);
    setup();
}

/* 單手鎚、左手鎚、雙手鎚都可以。 */
int valid_enable(string usage)
{
    return usage == "blunt" || usage == "secondhand blunt" || usage == "twohanded blunt";
}

/* 學習條件：膂力要夠（種族、職業、性別不限）。 */
int valid_learn(object me)
{
    if( me->query_attr("str") < LEARN_STR )
        return notify_fail("你的膂力不足﹐掄不動這兩柄鎚。\n");
    return 1;
}

/* 這一下是哪隻手出的："right"、"left"、"two"。 */
string hand_of(object weapon)
{
    string eq;

    if( !objectp(weapon) ) return "right";
    eq = weapon->query("equipped");
    if( eq == "weapon/secondhand blunt" ) return "left";
    if( eq == "weapon/twohanded blunt" ) return "two";
    return "right";
}

/* 右手單手鎚、左手左手鎚，兩邊都用撼山鎚法。 */
int dual_hammers(object me)
{
    return objectp(me->query_temp("weapon/blunt"))
        && objectp(me->query_temp("weapon/secondhand blunt"))
        && me->skill_mapped("blunt") == SKILL_ID
        && me->skill_mapped("secondhand blunt") == SKILL_ID;
}

mapping *moves_of(string hand)
{
    if( hand == "left" ) return left_moves;
    if( hand == "two" ) return two_moves;
    return right_moves;
}

/* 招名顏色左右手不同：右手 HIY、左手 HIC、雙手 HIR。 */
mapping make_hand_action(mapping m, int pct, string hand)
{
    mapping act;

    art_name_color = hand == "left" ? HIC : (hand == "two" ? HIR : HIY);
    act = make_action(m, pct);
    art_name_color = HIY;
    return act;
}

/* 特效用的一擊（招式從該手的招式表隨機挑）。 */
private int hand_hit(object me, object victim, object weapon, string hand, int pct, int gin_pct, int flags)
{
    mapping *list = moves_of(hand), act;

    act = make_hand_action(list[random(sizeof(list))], pct, hand);
    act["gin_pct"] = gin_pct;
    if( flags & HIT_MUST ) act["must_hit"] = 1;
    if( flags & HIT_SILENT ) act["silent"] = 1;
    return COMBAT_D->fight(me, victim, SKILL_ID, act, weapon);
}

/* 對手停頓 1；練武假人是死物，只換敘述不停頓（同傲梅暗劍訣）。 */
private void stagger(object me, object victim, string msg)
{
    if( !objectp(victim) ) return;
    if( victim->query("training_dummy") )
        message_vision("$N這一鎚震得$n連同底座嗡嗡直響。\n", me, victim, 1);
    else {
        message_vision(msg, me, victim, 1);
        victim->start_busy(1);
    }
}

/* 雙鎚撼山：同一回合左右兩鎚都命中時，機率 膂力÷2 %（最高 30%）。
 * 不可防禦（防具照樣減傷），傷害 150%，耗精 120%；對手停頓 1。 */
private void double_quake(object me, object victim)
{
    int chance = me->query_attr("str") / 2;

    if( chance > 30 ) chance = 30;
    if( random(100) >= chance ) return;
    message_vision("\n" HIY "$N雙鎚當胸一合﹐噹的一聲巨響震耳欲聾﹐鎚勢跟著直撞向$n﹗\n\n" NOR,
        me, victim, 1);
    if( hand_hit(me, victim, me->query_temp("weapon/blunt"), "right", 150, 120, HIT_MUST) > 0 )
        stagger(me, victim, "$n只覺氣血翻湧﹐一時竟提不起手來。\n");
}

void attack_using(object me, object opponent, object weapon)
{
    string hand;
    mapping *list, m;
    int lv, pct, damage, charge, dual, t, bit, seen, hits;

    if( !opponent ) return;
    if( !objectp(weapon) ) weapon = 0;

    lv   = me->query_skill(SKILL_ID, 1);
    hand = hand_of(weapon);
    dual = hand != "two" && dual_hammers(me);
    list = moves_of(hand);
    m    = list[random(sizeof(list))];
    pct  = 100;

    /* 左點右落：左鎚剛點中這個對手，右手這一鎚加重。 */
    if( hand == "right" && dual && lv >= POINT_LEVEL
    &&  me->query_temp("quake_hammer/mark") == opponent
    &&  time() - me->query_temp("quake_hammer/mark_time") <= POINT_TIME ) {
        me->delete_temp("quake_hammer/mark");
        message_vision(HIY "$N右手" + (weapon ? weapon->name() : "鎚") + HIY
            "循著左鎚點下的位置﹐不偏不倚地落了下去﹗\n" NOR, me, opponent, 1);
        pct = POINT_PCT;
    }

    /* 蓄勁：雙手合握時，先前落空積下的勁力這一鎚全數送出。 */
    if( hand == "two" && lv >= POINT_LEVEL
    &&  (charge = me->query_temp("quake_hammer/charge")) > 0 ) {
        if( me->query_temp("quake_hammer/charge_target") != opponent ) charge = 0;
        else {
            message_vision(HIR "$N鎚勢越壓越沉﹐把積蓄已久的勁力全送上了" + (weapon ? weapon->name() : "鎚")
                + HIR "﹗\n" NOR, me, opponent, 1);
            pct += charge * CHARGE_PCT;
        }
    }

    damage = COMBAT_D->fight(me, opponent, SKILL_ID, make_hand_action(m, pct, hand), weapon);
    if( !objectp(opponent) || !objectp(me) || !living(me) ) return;
    if( environment(me) != environment(opponent) ) return;

    if( hand == "two" ) {
        if( lv < POINT_LEVEL ) return;
        if( damage > 0 ) {
            me->delete_temp("quake_hammer/charge");
            /* 千鈞震地：蓄滿三層的這一鎚命中，對手停頓 1。 */
            if( charge >= CHARGE_MAX && lv >= QUAKE_LEVEL )
                stagger(me, opponent, HIR "這一鎚勁力沉雄﹐$n只覺腳下一震﹐氣血翻湧﹐一時竟站不穩身子。\n" NOR);
        } else {
            charge = me->query_temp("quake_hammer/charge_target") == opponent
                ? me->query_temp("quake_hammer/charge") : 0;
            if( charge < CHARGE_MAX ) charge++;
            me->set_temp("quake_hammer/charge", charge);
            me->set_temp("quake_hammer/charge_target", opponent);
        }
        return;
    }

    if( !dual ) return;

    /* 左鎚點中：記下點位，給右手下一鎚用。 */
    if( hand == "left" && damage > 0 && lv >= POINT_LEVEL ) {
        me->set_temp("quake_hammer/mark", opponent);
        me->set_temp("quake_hammer/mark_time", time());
    }

    /* 雙鎚撼山：同一回合兩手都出過鎚後判定一次。 */
    if( lv < QUAKE_LEVEL ) return;
    t   = time();
    bit = hand == "left" ? 2 : 1;
    if( me->query_temp("quake_hammer/round") != t ) {
        me->set_temp("quake_hammer/round", t);
        me->set_temp("quake_hammer/seen", 0);
        me->set_temp("quake_hammer/hits", 0);
    }
    seen = me->query_temp("quake_hammer/seen") | bit;
    hits = me->query_temp("quake_hammer/hits") | (damage > 0 ? bit : 0);
    me->set_temp("quake_hammer/seen", seen);
    me->set_temp("quake_hammer/hits", hits);
    if( seen != 3 ) return;
    me->delete_temp("quake_hammer/round");
    if( hits == 3 ) double_quake(me, opponent);
}

/* 練成的屬性提昇（使用者定案，2026-11-24）：練成時膂力 +1，100 級根骨 +1；各只給一次。 */
void skill_advanced(object me, string skill)
{
    int lv;

    ::skill_advanced(me, skill);
    if( !userp(me) ) return;
    lv = me->query_skill(SKILL_ID, 1);

    if( lv >= 20 && !me->query("martial_art/quake hammer/bonus_20") ) {
        me->set("martial_art/quake hammer/bonus_20", 1);
        me->set_attr("str", me->query_attr("str", 1) + 1);
        tell_object(me, HIY "你掄了這許多日子的鎚﹐只覺雙臂比從前有力多了。\n" NOR);
    }
    if( lv >= 100 && !me->query("martial_art/quake hammer/bonus_100") ) {
        me->set("martial_art/quake hammer/bonus_100", 1);
        me->set_attr("con", me->query_attr("con", 1) + 1);
        tell_object(me, HIY "鎚勁在筋骨間來回激盪﹐你的筋骨又結實了幾分。\n" NOR);
    }
}
