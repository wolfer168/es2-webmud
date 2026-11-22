/*---
description: 茅山【五雷術】（mao-shan lightning）。靈雲觀法術，enable 在法術（magic）上，以 conjure 施展。
             bless 五雷加持：一次提昇屬性、元素抗性、元素傷害、護甲，另依目標職業提昇一項技能。
             每次消耗精、氣、神各 15 和一張先天符，需持劍，只能對人形生物施放；
             再施展時覆蓋並重算時間。
             設計見 docs/martial_arts/靈雲觀_幽冥三箭與五雷術.md。
---*/
#include <ansi.h>

inherit SKILL;

#define SCROLL  "/custom/item/scroll/nature"
#define FACTION "mao-shan.cloud"
#define COST    15

string type() { return "magic"; }
int valid_enable(string usage) { return usage == "magic"; }

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("mao-shan lightning");
    setup();
}

/* 學習條件：靈雲觀弟子、幽冥三箭 90 級。 */
int valid_learn(object me)
{
    if( me->query("custom_faction") != FACTION )
        return notify_fail("你不是靈雲觀弟子﹐無緣參習五雷術。\n");
    if( me->query_skill("taoism of purify", 1) < 90 )
        return notify_fail("你的幽冥三箭尚未大成﹐參不透五雷術的玄機。\n");
    return 1;
}

/* 練成 20 級（使用者定案，2026-11-22）。 */
int query_entry_level() { return 20; }

void skill_completed(object me, string skill)
{
    tell_object(me, HIW "你默念雷訣﹐耳畔隱隱響起一陣悶雷﹐五雷術總算入了門。\n" NOR);
}

// ------------------------------------------------------------------
// 五雷加持資料（使用者定案，2026-11-22）
// ------------------------------------------------------------------

/* 提昇的屬性：膽識、定力、悟性、慧根、膂力。 */
#define ATTRS    ({ "cor", "cps", "int", "wis", "str" })
/* 元素：火、冰、風、雷。 */
#define ELEMENTS ({ "fire", "ice", "wind", "lightning" })

/* 依目標職業提昇的技能（平民沒有）。 */
mapping CLASS_SKILL = ([
    "thief":     "sneak",
    "scholar":   "mysticism",
    "fighter":   "force",
    "soldier":   "powerblow",
    "taoist":    "spells",
    "alchemist": "magic",
    "monk":      "absorption",
]);

/* 施法點數（照茅山法術）：
 * 基本法術：((random(靈性)+1) × (random(靈性)+1) + random(靈性)) × (random(層級)+1)
 * 五雷術：  ((random(悟性)+1) × (random(靈性)+1) + random(靈性)) × (random(層級)+1)
 * 層級 3。 */
void magic_gain(object me)
{
    int spi, intel;

    if( !userp(me) ) return;
    spi = me->query_attr("spi");
    intel = me->query_attr("int");
    if( spi < 1 ) spi = 1;
    if( intel < 1 ) intel = 1;
    me->improve_skill_exact("magic",
        ((random(spi) + 1) * (random(spi) + 1) + random(spi)) * (random(3) + 1));
    me->improve_skill_exact("mao-shan lightning",
        ((random(intel) + 1) * (random(spi) + 1) + random(spi)) * (random(3) + 1));
}

object find_scroll(object me)
{
    foreach(object ob in all_inventory(me))
        if( base_name(ob) == SCROLL ) return ob;
    return 0;
}

// ------------------------------------------------------------------
// 加持：雷咒強度 T = 魔力 + 幽冥三箭 ÷ 2 + 五雷術；
// 屬性 + T÷50、元素抗性 + T÷4（風抗加倍，因為風抗只減半傷害）、元素傷害 + T÷5、
// 職業技能 + T÷20、護甲 + T÷10；持續 五雷術 ÷ 2 個 tick（1 tick = 2 秒）。
// 再施展：先撤掉舊的再重新計算。
// ------------------------------------------------------------------

/* 加成記在目標身上（lightning/bless），sign 1 加上、-1 撤掉。 */
void apply_bonus(object who, mapping b, int sign)
{
    foreach(string a in ATTRS)
        who->add_temp("apply/" + a, sign * b["attr"]);
    foreach(string e in ELEMENTS) {
        who->add_temp("apply/armor_vs_" + e, sign * (e == "wind" ? b["resist"] * 2 : b["resist"]));
        who->add_temp("apply/damage_vs_" + e, sign * b["damage"]);
    }
    who->add_temp("apply/armor", sign * b["armor"]);
    if( stringp(b["skill_id"]) )
        who->add_temp("apply/" + b["skill_id"], sign * b["skill"]);
}

void expire(object who, int serial)
{
    mapping b;

    if( !objectp(who) || !mapp(b = who->query_temp("lightning/bless"))
    ||  b["serial"] != serial ) return;
    apply_bonus(who, b, -1);
    who->delete_temp("lightning/bless");
    tell_object(who, CYN "你身上的雷光漸漸黯淡﹐終於散去。\n" NOR);
}

int do_bless(object me, object target)
{
    mapping b, old;
    int strength, ticks, serial;
    string cls;

    strength = me->query_ability("magic") + me->query_skill("taoism of purify") / 2
        + me->query_skill("mao-shan lightning");
    b = ([ "attr": strength / 50, "resist": strength / 4, "damage": strength / 5,
           "skill": strength / 20, "armor": strength / 10 ]);
    cls = target->query_class();
    if( stringp(cls) && !undefinedp(CLASS_SKILL[cls]) ) b["skill_id"] = CLASS_SKILL[cls];

    // 已有加持：撤掉舊的，覆蓋並重算時間。
    if( mapp(old = target->query_temp("lightning/bless")) ) {
        apply_bonus(target, old, -1);
        target->delete_temp("lightning/bless");
    }
    serial = random(1000000) + 1;
    b["serial"] = serial;
    apply_bonus(target, b, 1);
    target->set_temp("lightning/bless", b);
    ticks = me->query_skill("mao-shan lightning") / 2;
    if( ticks < 1 ) ticks = 1;
    call_out("expire", ticks * 2, target, serial);

    if( mapp(old) )
        message_vision(CYN + (target == me ? "$N" : "$n") + "身上的雷光一閃﹐又旺盛了幾分。\n" NOR, me, target, 1);
    else if( target == me )
        message_vision(CYN "$N將先天符往空中一拋﹐低喝一聲" HIY "「雷來」" NOR CYN "﹐五道電蛇盤旋而下繞著自己遊走不去。\n" NOR,
            me, target, 1);
    else
        message_vision(CYN "$N將先天符往空中一拋﹐低喝一聲" HIY "「雷來」" NOR CYN "﹐五道電蛇盤旋而下繞著$n遊走不去。\n" NOR,
            me, target, 1);
    return 1;
}

int conjure_magic(object me, string spell, object target)
{
    object scroll;
    mapping w;

    if( !me->query_skill("mao-shan lightning", 1) && !me->query_learn("mao-shan lightning") )
        return notify_fail("你還沒學會五雷術。\n");
    if( spell != "bless" )
        return notify_fail("指令格式﹕conjure bless [on <對象>]\n");

    if( !mapp(w = me->query_temp("weapon")) || !objectp(w["sword"]) )
        return notify_fail("你手中沒有劍﹐施展不了五雷術。\n");

    if( !objectp(target) ) target = me;
    if( !living(target) || environment(target) != environment(me) )
        return notify_fail("這裡沒有可施法的對象。\n");
    if( !target->query("humanoid") || target->query("training_dummy") )
        return notify_fail("對方不是人形﹐雷咒附不上去。\n");

    if( !(scroll = find_scroll(me)) )
        return notify_fail("你身上沒有先天符﹐無從施展五雷術。\n");
    if( me->query_stat("gin") < COST || me->query_stat("kee") < COST
    ||  me->query_stat("sen") < COST )
        return notify_fail("你精神不濟﹐無法施展五雷術。\n");

    foreach(string st in ({ "gin", "kee", "sen" }))
        me->consume_stat(st, COST);
    scroll->add_amount(-1);

    do_bless(me, target);
    me->start_busy(1);
    magic_gain(me);
    return 1;
}
