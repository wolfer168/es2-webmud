/*---
description: 茅山【五雷術】（mao-shan lightning）。靈雲觀法術，enable 在法術（magic）上，以 conjure 施展。
             五卦雷咒：lightning-gold 金、lightning-wood 木、lightning-water 水、
             lightning-fire 火、lightning-earth 土。每道消耗精、氣、神各 15 和一張先天符，
             需持劍，只能對人形生物施放；五道可同時存在，同一道再施展會覆蓋並重算時間。
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
// 五卦雷咒資料（舊站 2008 靈雲觀文章；數值使用者定案，2026-11-22）
// ------------------------------------------------------------------

/* 卦：可用等級、名稱、名稱顏色、光色、提昇的屬性、元素抗性（apply 名稱，空字串為沒有）、
 *     提昇的技能、層級（算點數用）。金卦另加護甲。 */
mapping SPELLS = ([
    "lightning-gold":  ({  0, "金卦雷咒", HIY, "金光", "cor", "",                  "spells",         1 }),
    "lightning-wood":  ({ 20, "木卦雷咒", HIG, "青光", "cps", "armor_vs_wind",     "sneak",          2 }),
    "lightning-water": ({ 40, "水卦雷咒", HIC, "清光", "int", "armor_vs_fire",     "mysticism",      3 }),
    "lightning-fire":  ({ 60, "火卦雷咒", HIR, "赤光", "wis", "armor_vs_lightning", "kee anatomy",   4 }),
    "lightning-earth": ({ 80, "土卦雷咒", YEL, "黃光", "str", "armor_vs_ice",      "powerblow",      5 }),
]);

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
// 加持：雷咒強度 T = 魔力 + 幽冥三箭 ÷ 2 + 五雷術；
// 屬性 + T÷50、元素抗性 + T÷4（木卦風抗加倍，因為風抗只減半傷害）、
// 技能 + T÷20、護甲（金卦）+ T÷10；持續 五雷術 ÷ 2 個 tick（1 tick = 2 秒）。
// 同一卦再施展：先撤掉舊的再重新計算。
// ------------------------------------------------------------------

/* 加成記在目標身上（lightning/<卦>），sign 1 加上、-1 撤掉。 */
void apply_bonus(object who, string spell, mapping b, int sign)
{
    mixed *s = SPELLS[spell];

    who->add_temp("apply/" + s[4], sign * b["attr"]);
    who->add_temp("apply/" + s[6], sign * b["skill"]);
    if( s[5] != "" ) who->add_temp("apply/" + s[5], sign * b["resist"]);
    if( spell == "lightning-gold" ) who->add_temp("apply/armor", sign * b["armor"]);
}

void expire(object who, string spell, int serial)
{
    mapping b;

    if( !objectp(who) || !mapp(b = who->query_temp("lightning/" + spell))
    ||  b["serial"] != serial ) return;
    apply_bonus(who, spell, b, -1);
    who->delete_temp("lightning/" + spell);
    tell_object(who, CYN "你身上的" + SPELLS[spell][3] + "漸漸黯淡﹐終於散去。\n" NOR);
}

/* 效果敘述（對別人用 $n，對自己把 $n 換成「自己」）。 */
string effect_line(string spell, int self)
{
    string msg;

    switch( spell ) {
    case "lightning-gold":
        return self ? "$N劍訣一領﹐先天符化作一道金光﹐當頭罩了下來。"
                    : "$N劍訣一領﹐先天符化作一道金光﹐直落$n頭頂。";
    case "lightning-wood":  msg = "$N長劍橫胸一引﹐先天符化作一縷青光﹐繞著$n緩緩盤旋。"; break;
    case "lightning-water": msg = "$N劍尖在地上輕輕一點﹐先天符化作一汪清光﹐漫向$n的腳邊。"; break;
    case "lightning-fire":  msg = "$N劍鋒一抖﹐先天符化作一團赤光﹐旋入$n的眉心。"; break;
    default:                msg = "$N劍柄頓地﹐先天符化作一團黃光﹐自腳下升起罩住$n。"; break;
    }
    return self ? replace_string(msg, "$n", "自己") : msg;
}

string result_line(string spell)
{
    switch( spell ) {
    case "lightning-gold":  return "金光裹住$n全身﹐$n只覺膽氣大壯﹐周身如披薄甲。";
    case "lightning-wood":  return "青光沒入$n體內﹐$n心神一定﹐身邊的風也似繞著走了。";
    case "lightning-water": return "清光漫上$n全身﹐$n頭腦一清﹐炎熱之氣不得近身。";
    case "lightning-fire":  return "赤光融入$n身子﹐$n靈光乍現﹐耳畔隱隱有雷聲滾過。";
    }
    return "黃光凝在$n身上﹐$n膂力一沉﹐寒意再也侵不進來。";
}

int do_lightning(object me, object target, string spell)
{
    mapping b, old;
    mixed *s = SPELLS[spell];
    int sk, strength, ticks, serial, self;

    sk = me->query_skill("mao-shan lightning");
    strength = me->query_ability("magic") + me->query_skill("taoism of purify") / 2 + sk;
    b = ([ "attr": strength / 50, "resist": strength / 4, "skill": strength / 20,
           "armor": strength / 10 ]);
    if( spell == "lightning-wood" ) b["resist"] *= 2;   // 風抗只減半傷害，加倍補回
    self = (target == me);

    // 已有同一卦：撤掉舊的，覆蓋並重算時間。
    if( mapp(old = target->query_temp("lightning/" + spell)) ) {
        apply_bonus(target, spell, old, -1);
        target->delete_temp("lightning/" + spell);
    }
    serial = random(1000000) + 1;
    b["serial"] = serial;
    apply_bonus(target, spell, b, 1);
    target->set_temp("lightning/" + spell, b);
    ticks = me->query_skill("mao-shan lightning") / 2;
    if( ticks < 1 ) ticks = 1;
    call_out("expire", ticks * 2, target, spell, serial);

    message_vision(CYN "$N拈起一張先天符﹐劍尖斜指﹐開始施展" + s[2] + "「" + s[1] + "」" NOR CYN " ...." NOR "\n",
        me, target, 1);
    message_vision("\n", me, 0, 1);
    message_vision(CYN + effect_line(spell, self) + NOR "\n", me, target, 1);
    message_vision("\n", me, 0, 1);
    if( mapp(old) )
        message_vision(CYN + (self ? "$N" : "$n") + "身上的" + s[3] + "一閃﹐又旺盛了幾分。\n" NOR, me, target, 1);
    else {
        string msg = result_line(spell);
        if( self ) msg = replace_string(msg, "$n", "$N");
        message_vision(CYN + msg + NOR "\n", me, target, 1);
    }
    return 1;
}

int conjure_magic(object me, string spell, object target)
{
    object scroll;
    mapping w;
    int sk;

    if( !me->query_skill("mao-shan lightning", 1) && !me->query_learn("mao-shan lightning") )
        return notify_fail("你還沒學會五雷術。\n");
    if( !stringp(spell) || undefinedp(SPELLS[spell]) )
        return notify_fail("指令格式﹕conjure <雷咒名稱> [on <對象>]\n");
    sk = me->query_skill("mao-shan lightning", 1);
    if( sk < SPELLS[spell][0] )
        return notify_fail("你的五雷術火候未到﹐還驅使不了這道雷咒。\n");

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

    do_lightning(me, target, spell);
    me->start_busy(1);
    magic_gain(me, SPELLS[spell][7]);
    return 1;
}
