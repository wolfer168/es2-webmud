/*---
description: 茅山【五雷術】（mao-shan lightning）。靈雲觀法術，enable 在法術（magic）上，以 conjure 施展。
             cleanse 凝靈、bless 加持、consume 歸元；靈力只有一股，用掉要重新凝聚。
             設計見 docs/martial_arts/靈雲觀_幽冥三箭與五雷術.md。
---*/
#include <ansi.h>

inherit SKILL;

#define SCROLL  "/custom/item/scroll/nature"
#define FACTION "mao-shan.cloud"

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

void skill_completed(object me, string skill)
{
    tell_object(me, HIW "你默念雷訣﹐耳畔隱隱響起一陣悶雷﹐五雷術總算入了門。\n" NOR);
}

// ------------------------------------------------------------------
// 法術資料（使用者定案，2026-11-22）
// ------------------------------------------------------------------

/* 法術：耗神、停頓、層級（算點數用）、名稱。 */
mapping SPELLS = ([
    "cleanse": ({ 20, 1, 1, "凝靈之術" }),
    "bless":   ({ 50, 2, 3, "五雷加持" }),
    "consume": ({ 20, 1, 2, "五雷歸元" }),
]);

/* 加持加上的屬性、元素（元素傷害、元素抗性用同一組）。 */
#define ATTRS    ({ "str", "cor", "int", "cps", "wis" })
#define ELEMENTS ({ "fire", "ice", "wind", "lightning" })

/* 施法點數（照茅山法術）：
 * 基本法術：((random(靈性)+1) × (random(靈性)+1) + random(靈性)) × (random(層級)+1)
 * 五雷術：  ((random(悟性)+1) × (random(靈性)+1) + random(靈性)) × (random(層級)+1) */
void magic_gain(object me, int tier)
{
    int spi, intel;

    if( !userp(me) ) return;
    spi = me->query_attr("spi");
    intel = me->query_attr("int");
    if( spi < 1 ) spi = 1;
    if( intel < 1 ) intel = 1;
    me->improve_skill_exact("magic",
        ((random(spi) + 1) * (random(spi) + 1) + random(spi)) * (random(tier) + 1));
    me->improve_skill_exact("mao-shan lightning",
        ((random(intel) + 1) * (random(spi) + 1) + random(spi)) * (random(tier) + 1));
}

object find_scroll(object me)
{
    foreach(object ob in all_inventory(me))
        if( base_name(ob) == SCROLL ) return ob;
    return 0;
}

// ------------------------------------------------------------------
// 靈力：只有一股，時效 = 五雷術 tick（1 tick = 2 秒），bless、consume 用掉就要重新凝聚。
// ------------------------------------------------------------------

int has_mana(object me)
{
    return me->query_temp("lightning/mana") > time();
}

// ------------------------------------------------------------------
// 加持：屬性 + (五雷術 + 靈性) ÷ 20，元素抗性 + 靈性 × 4，元素傷害 + 五雷術 ÷ 3；
// 持續 五雷術 ÷ 2 個 tick。同一個人同時只吃一份加持。
// ------------------------------------------------------------------

void remove_bless(object who)
{
    mapping b;

    if( !objectp(who) || !mapp(b = who->query_temp("lightning/bless")) ) return;
    foreach(string a in ATTRS)
        who->add_temp("apply/" + a, -b["attr"]);
    foreach(string e in ELEMENTS) {
        who->add_temp("apply/damage_vs_" + e, -b["damage"]);
        who->add_temp("apply/armor_vs_" + e, -b["resist"]);
    }
    who->delete_temp("lightning/bless");
    tell_object(who, HIK "你身上纏繞的雷光漸漸黯淡﹐終於散去了。\n" NOR);
}

int do_bless(object me, object target, int sk)
{
    mapping b;
    int spi, ticks;

    spi = me->query_attr("spi");
    b = ([ "attr": (sk + spi) / 20, "damage": sk / 3, "resist": spi * 4 ]);
    foreach(string a in ATTRS)
        target->add_temp("apply/" + a, b["attr"]);
    foreach(string e in ELEMENTS) {
        target->add_temp("apply/damage_vs_" + e, b["damage"]);
        target->add_temp("apply/armor_vs_" + e, b["resist"]);
    }
    target->set_temp("lightning/bless", b);
    ticks = sk / 2;
    if( ticks < 1 ) ticks = 1;
    call_out("remove_bless", ticks * 2, target);

    message_vision(HIK "$N將先天符往空中一拋﹐雙手結印﹐低喝一聲" HIY "「雷來」" NOR HIK "﹗\n" NOR, me, target, 1);
    message_vision("\n", me, 0, 1);
    if( target == me )
        message_vision(HIW "半空中雷光一閃﹐五道細細的電蛇盤旋而下﹐繞著$N的身子遊走不去。\n" NOR, me, 0, 1);
    else
        message_vision(HIW "半空中雷光一閃﹐五道細細的電蛇盤旋而下﹐繞著$n的身子遊走不去。\n" NOR, me, target, 1);
    return 1;
}

int do_consume(object me, object target, int sk)
{
    int gin, sen;

    gin = sk / 2 + random(sk * 2 / 3 - sk / 2 + 1);
    sen = sk / 3 + random(sk * 2 / 3 - sk / 3 + 1);
    target->supplement_stat("gin", gin);
    target->supplement_stat("sen", sen);

    message_vision(HIK "$N將先天符按在掌心﹐引體內靈力化作一縷電光﹐輕輕點向$n的眉心。\n" NOR, me, target, 1);
    message_vision("\n", me, 0, 1);
    message_vision(HIW "那縷電光沒入$n的眉心﹐$n只覺神清氣爽﹐疲憊一掃而空。\n" NOR, me, target, 1);
    return 1;
}

int do_cleanse(object me, int sk)
{
    me->set_temp("lightning/mana", time() + (sk > 0 ? sk : 1) * 2);
    message_vision(HIK "$N盤膝而坐﹐吐納幾口﹐將散落全身的靈力一絲絲收攏到丹田之中。\n" NOR, me, 0, 1);
    return 1;
}

int conjure_magic(object me, string spell, object target)
{
    object scroll;
    int sk;

    if( !me->query_skill("mao-shan lightning", 1) && !me->query_learn("mao-shan lightning") )
        return notify_fail("你還沒學會五雷術。\n");
    if( !stringp(spell) || undefinedp(SPELLS[spell]) )
        return notify_fail("指令格式﹕conjure <法術名稱> [on <對象>]\n");
    sk = me->query_skill("mao-shan lightning", 1);

    if( spell == "cleanse" ) {
        if( has_mana(me) ) return notify_fail("你體內的靈力還凝聚著﹐不必再收攏了。\n");
    } else {
        if( !has_mana(me) )
            return notify_fail("你體內靈力渙散﹐施展不了五雷術。\n");
        if( !objectp(target) ) target = me;
        if( !living(target) || environment(target) != environment(me) )
            return notify_fail("這裡沒有可施法的對象。\n");
        if( spell == "bless" && target->query_temp("lightning/bless") )
            return notify_fail((target == me ? "你" : target->name()) + "身上已經纏著五雷的加持了。\n");
        if( !(scroll = find_scroll(me)) )
            return notify_fail("你身上沒有先天符﹐無從施展五雷術。\n");
    }
    if( me->query_stat("sen") < SPELLS[spell][0] )
        return notify_fail("你心神渙散﹐無法施展五雷術。\n");

    me->consume_stat("sen", SPELLS[spell][0]);
    if( scroll ) {
        scroll->add_amount(-1);
        me->delete_temp("lightning/mana");   // 靈力用掉了，要重新凝聚
    }

    switch( spell ) {
    case "cleanse": do_cleanse(me, sk); break;
    case "bless":   do_bless(me, target, sk); break;
    case "consume": do_consume(me, target, sk); break;
    }

    me->start_busy(SPELLS[spell][1]);
    magic_gain(me, SPELLS[spell][2]);
    return 1;
}
