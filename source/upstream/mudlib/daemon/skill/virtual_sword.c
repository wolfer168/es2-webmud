/*---
description: 幻劍術（virtual sword）。道士張齡自創的咒術，enable 在咒術（spells）上，以 cast 施展；
             ten 十面埋伏、thirty-six 六陰六陽劍、forty-nine 四九歸元、sixty-four 六十四爻誅殺訣、
             eighty-one 九九陽極幻劍、ninety-nine 無極幻影。
             傷害 = 人物附加傷害（apply/damage）＋ 該招的數字；消耗神為總傷害的一半，施咒後自身停頓 1 回合。
             設計見 docs/martial_arts/道士共通_幻劍術.md。
---*/
#include <ansi.h>

inherit SKILL;

#define SPELLS_D "/daemon/skill/taoism-spells"

string type() { return "spell"; }
int valid_enable(string usage) { return usage == "spells"; }

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("virtual sword");
    setup();
}

/* 學習條件：道士、人物等級 5、咒術 90、劍術 30、殺業小於 3000（說出口的敘述不提數字）。 */
int valid_learn(object me)
{
    if( me->query("class") != "taoist" )
        return notify_fail("幻劍術是道士的咒術﹐你無法修練。\n");
    if( me->query_level() < 5 )
        return notify_fail("你的根基尚淺﹐還參不透幻劍術的門道。\n");
    if( me->query_skill("spells", 1) < 90 )
        return notify_fail("你的咒術根基不夠深厚﹐還參不透幻劍術的咒訣。\n");
    if( me->query_skill("sword", 1) < 30 )
        return notify_fail("你的劍術火候未到﹐還使不出幻劍術的運劍法門。\n");
    if( me->query_score("kills") >= 3000 )
        return notify_fail("你身上殺氣太重﹐幻劍術的咒訣在你手裡只會走偏。\n");
    return 1;
}

/* 練成 10 級，比照幽冥三箭：求教後還沒學成的 0 級也算學會，可以施展十面埋伏。 */
int query_entry_level() { return 10; }

void skill_completed(object me, string skill)
{
    tell_object(me, HIY "你默運真氣﹐劍訣一領﹐眼前竟隱隱浮出一口虛實難辨的幻劍﹐幻劍術總算入了門。\n" NOR);
}

// ------------------------------------------------------------------
// 招式資料
// ------------------------------------------------------------------

/* 咒文：可用技能等級、傷害加成（數字）、名稱、名稱顏色、乘數（練功點數用）。 */
mapping SPELLS = ([
    "ten":          ({  0, 10, "十面埋伏",       HIW, 1 }),
    "thirty-six":   ({ 36, 36, "六陰六陽劍",     HIY, 2 }),
    "forty-nine":   ({ 49, 49, "四九歸元",       HIY, 3 }),
    "sixty-four":   ({ 64, 64, "六十四爻誅殺訣", HIY, 4 }),
    "eighty-one":   ({ 81, 81, "九九陽極幻劍",   HIY, 5 }),
    "ninety-nine":  ({ 99, 99, "無極幻影",       HIR, 6 }),
]);

string spell_title(string spell)
{
    return SPELLS[spell][3] + "「" + SPELLS[spell][2] + "」" NOR CYN;
}

/* 起手：有持劍就揮劍招架，沒持劍就以劍訣代劍。 */
string start_line(object me, string spell)
{
    string how;

    how = objectp(me->query_temp("weapon")) ? "揮劍招架" : "以劍訣招架";
    return "$N一邊" + how + "，一邊口中喃喃地念著咒文，對著$n施展" + spell_title(spell) + " ....";
}

string effect_line(string spell)
{
    if( spell == "ten" )
        return "$N劍訣一引，十口幻劍自四面八方悄然浮現，無聲無息地埋伏在$n身周，只待一聲令下。";
    if( spell == "thirty-six" )
        return "$N左手捏陰訣、右手捏陽訣，三十六口幻劍分作陰陽兩路，一冷一熱，交錯盤旋著罩向$n。";
    if( spell == "forty-nine" )
        return "$N放出七七四十九口修羅幻劍，同時攻向$n。";
    if( spell == "sixty-four" )
        return "$N腳踏八卦方位，六十四口幻劍依六十四爻的卦象凌空排開，劍氣森然，殺機盡鎖$n週身。";
    if( spell == "eighty-one" )
        return "$N雙手劍訣一合，八十一口赤金幻劍沖天而起，陽氣至極，劍身所過之處空氣都燙得扭曲起來。";
    return "$N劍意一放，一劍化百，九十九道幻影鋪天蓋地而來，真假難辨，竟看不出哪一口才是真劍。";
}

string hit_line(string spell)
{
    if( spell == "ten" )
        return "十口幻劍同時發難，自四面刺入$n身上，留下數道血痕！";
    if( spell == "thirty-six" )
        return "陰劍透骨生寒、陽劍灼肉如焚，$n一時冷熱交攻，慘哼一聲連連後退！";
    if( spell == "forty-nine" )
        return "四十九口幻劍從四面八方貫入，$n只覺渾身劇痛，閃避不及！";
    if( spell == "sixty-four" )
        return "六十四口幻劍依卦象層層落下，$n避得了這一爻、躲不過那一爻，被劍氣割得遍體鱗傷！";
    if( spell == "eighty-one" )
        return "八十一口赤金幻劍轟然落下，陽勁炸開，燒得$n皮焦肉裂、慘呼不已！";
    return "九十九道幻影同時沒入$n的身軀，$n這才驚覺每一道竟都是真劍，傷勢慘不忍睹！";
}

/* 練武假人是死物：命中敘述只寫外觀留下的痕跡。 */
string dummy_hit_line(string spell)
{
    if( spell == "ten" ) return "十口幻劍自四面刺入，在$n身上留下數道劍痕！";
    if( spell == "thirty-six" ) return "陰陽兩路幻劍交錯劃過，$n身上多了一片縱橫的劍痕！";
    if( spell == "forty-nine" ) return "四十九口幻劍貫入$n，劍痕密密麻麻佈滿全身！";
    if( spell == "sixty-four" ) return "六十四口幻劍依卦象落下，在$n身上刻出一幅縱橫交錯的劍痕！";
    if( spell == "eighty-one" ) return "八十一口赤金幻劍轟然落下，$n身上一片焦黑，劍痕累累！";
    return "九十九道幻影沒入$n，轉眼間$n身上已是千瘡百孔！";
}

string miss_line(string spell)
{
    if( spell == "ten" ) return "$n察覺殺機，縱身躍出劍圍，十口幻劍刺了個空，散成點點銀光。";
    if( spell == "thirty-six" ) return "$n運氣護住週身，陰陽幻劍撞上護體氣勁，紛紛化作輕煙。";
    if( spell == "forty-nine" ) return "$n身形急轉，在劍雨中尋出一條空隙閃了過去，四十九口幻劍盡數落空。";
    if( spell == "sixty-four" ) return "$n看準卦象的生門一步跨出，六十四口幻劍的殺局竟被破去。";
    if( spell == "eighty-one" ) return "$n凝神抵擋，勉強擋住赤金幻劍的陽勁，劍影轟在空處散作火星。";
    return "$n閉目不看那些幻影，單憑聽風辨位，九十九道幻影擦身而過，盡成虛影。";
}

// ------------------------------------------------------------------
// 顯示：敘述青色、招名黃色（比照天師咒術：起手、空行、效果、空行、結果）。
// ------------------------------------------------------------------

void say_line(object me, object target, string msg)
{
    message_vision(CYN + msg + NOR "\n", me, target, 1);
}

void blank(object me)
{
    message_vision("\n", me, 0, 1);
}

/* 施咒的技能點數（比照幽冥三箭）：沒打中只給 1/4、至少 1 點。 */
void spell_gain(object me, int rank, int hit)
{
    int wis, intel, exp;

    if( !userp(me) ) return;
    wis = me->query_attr("wis");
    intel = me->query_attr("int");
    if( wis < 1 ) wis = 1;

    exp = ((random(wis) + 1) * (random(wis) + 1) + random(wis)) * (random(rank) + 1);
    if( !hit && (exp /= 4) < 1 ) exp = 1;
    me->improve_skill_exact("spells", exp);

    exp = ((intel > 0 ? random(intel) : 0) * random(wis) + random(wis)) * (random(rank) + 1);
    if( !hit && (exp /= 4) < 1 ) exp = 1;
    if( exp > 0 ) me->improve_skill_exact("virtual sword", exp);
}

/* 放出幻劍：起手、效果、命中或落空；傳回是否命中。cast 與太乙劍法的自動施展共用。 */
private int release(object me, object target, string spell, int power)
{
    int dealt, hit;

    say_line(me, target, start_line(me, spell));
    blank(me);
    say_line(me, target, effect_line(spell));
    blank(me);

    hit = SPELLS_D->spell_hits(me, target, "virtual", 1);
    if( !hit ) {
        say_line(me, target, miss_line(spell));
    } else {
        dealt = target->receive_damage(power, me, me);
        say_line(me, target, SPELLS_D->is_dummy(target) ? dummy_hit_line(spell) : hit_line(spell));
        if( objectp(target) ) COMBAT_D->report_status(target);
        if( userp(me) ) me->gain_score("combat", (1 + dealt / 40) > 20 ? 20 : (1 + dealt / 40));
    }
    return hit;
}

// ------------------------------------------------------------------
// 施咒：傷害 = 人物附加傷害 + 招式數字；耗神 = 總傷害的一半；自身停頓 1 回合。
// ------------------------------------------------------------------

varargs int cast_spell(object me, string spell, object target)
{
    object *enemies;
    int sk, power, cost, hit;

    if( me->skill_mapped("spells") != "virtual sword" )
        return notify_fail("你沒有使用幻劍術。\n");
    if( me->is_busy() ) return notify_fail("你現在沒有空施咒。\n");

    if( stringp(spell) ) spell = replace_string(spell, "_", "-");
    if( !stringp(spell) || undefinedp(SPELLS[spell]) )
        return notify_fail("指令格式﹕cast <咒文名稱> [on <施咒對象>]\n");

    sk = me->query_skill("virtual sword", 1);
    /* 求教後還沒學成的 0 級也算學會，可以施展十面埋伏。 */
    if( (sk < 1 && me->query_learn("virtual sword") < 1) || sk < SPELLS[spell][0] )
        return notify_fail("你的幻劍術火候未到﹐還驅使不了這道咒法。\n");

    if( !objectp(target) ) {
        enemies = me->query_enemy();
        if( sizeof(enemies) ) target = enemies[0];
    }
    if( !objectp(target) || target == me || !living(target)
    ||  environment(target) != environment(me) )
        return notify_fail("這裡沒有可施咒的對象。\n");

    power = me->query_temp("apply/damage") + SPELLS[spell][1];
    if( power < 1 ) power = 1;
    cost = power / 2;
    if( cost < 1 ) cost = 1;
    if( me->query_stat("sen") < cost )
        return notify_fail("你心神不足﹐無法催動這道幻劍。\n");

    me->consume_stat("sen", cost);
    me->fight_ob(target);
    target->fight_ob(me);
    // 每次施展得法術修為 random(靈性/2) + 1（比照天師咒術）。
    me->gain_score("magic", random(me->query_attr("spi") / 2) + 1);

    hit = release(me, target, spell, power);

    spell_gain(me, SPELLS[spell][4], hit);
    me->start_busy(1);
    return 1;
}

/* 太乙劍法的招架特技（使用者定案，2026-11-24）：招架成功時自動放出幻劍術，
 * 不耗神、不停頓、不看技能等級與 enable，也不累積修練點數。
 * 觸發後（50% 由太乙劍法判斷）隨機挑一招：十面埋伏、無極幻影各 10%，六陰六陽劍、九九陽極幻劍各 15%，四九歸元、六十四爻誅殺訣各 25%。 */
int auto_cast(object me, object target)
{
    int n, power;
    string spell;

    if( !objectp(me) || !objectp(target) || !living(target) || target == me
    ||  environment(target) != environment(me) ) return 0;

    n = random(100);
    if( n < 10 ) spell = "ten";
    else if( n < 25 ) spell = "thirty-six";
    else if( n < 50 ) spell = "forty-nine";
    else if( n < 75 ) spell = "sixty-four";
    else if( n < 90 ) spell = "eighty-one";
    else spell = "ninety-nine";

    power = me->query_temp("apply/damage") + SPELLS[spell][1];
    if( power < 1 ) power = 1;
    release(me, target, spell, power);
    return 1;
}
