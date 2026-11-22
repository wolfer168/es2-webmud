/*---
description: 幽冥三箭（taoism of purify）。靈雲觀專長咒術，enable 在咒術（spells）上，以 cast 施展；
             netherbolt 青冥之箭、drainerbolt 紫幽之箭、feeblebolt 蒼靈之箭。
             每次施展消耗一張正陽符與神；箭射中 NPC 造成傷害，並把精、氣、神補給自己。
             設計見 docs/martial_arts/靈雲觀_幽冥三箭與五雷術.md。
---*/
#include <ansi.h>

inherit SKILL;

#define SCROLL   "/custom/item/scroll/yang"
#define SPELLS_D "/daemon/skill/taoism-spells"
#define FACTION  "mao-shan.cloud"

string type() { return "spell"; }
int valid_enable(string usage) { return usage == "spells"; }

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("taoism of purify");
    setup();
}

/* 學習條件：靈雲觀弟子。 */
int valid_learn(object me)
{
    if( me->query("custom_faction") != FACTION )
        return notify_fail("你不是靈雲觀弟子﹐參不透幽冥三箭的門道。\n");
    return 1;
}

/* 練成 10 級（使用者定案，2026-11-22）。 */
int query_entry_level() { return 10; }

void skill_completed(object me, string skill)
{
    tell_object(me, HIY "你默運真氣﹐指間隱隱凝出一點金光﹐幽冥三箭總算入了門。\n" NOR);
}

// ------------------------------------------------------------------
// 咒文資料（使用者定案，2026-11-22；需求、耗神、乘數照舊文檔）
// ------------------------------------------------------------------

/* 咒文：可用等級、耗神、攻擊乘數、補給的屬性、名稱。 */
mapping SPELLS = ([
    "netherbolt":  ({  0, 10, 1, "sen", "青冥之箭" }),
    "drainerbolt": ({ 25, 15, 2, "gin", "紫幽之箭" }),
    "feeblebolt":  ({ 50, 25, 3, "kee", "蒼靈之箭" }),
]);

/* 施咒點數（照茅山奇術／天師咒術）：
 * 基本咒術：((random(慧根)+1) × (random(慧根)+1) + random(慧根)) × (random(乘數)+1)
 * 幽冥三箭：(random(悟性) × random(慧根) + random(慧根)) × (random(乘數)+1)
 * 沒打中只給 1/4、至少 1 點。 */
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
    if( exp > 0 ) me->improve_skill_exact("taoism of purify", exp);
}

object find_scroll(object me)
{
    foreach(object ob in all_inventory(me))
        if( base_name(ob) == SCROLL ) return ob;
    return 0;
}

/* 殭屍、鬼魂、動物：傷害較高。遊戲裡殭屍沒有專屬種族，
 * 以 undead 標記、英文代號含 zombie、名稱含「殭」「僵」認定。 */
int is_unclean(object target)
{
    string *ids;

    if( target->query_race() == "beast" ) return 1;
    if( target->query("life_form") == "ghost" ) return 1;
    if( target->query("undead") ) return 1;
    if( strsrch(target->name(), "殭") >= 0 || strsrch(target->name(), "僵") >= 0 ) return 1;
    ids = target->parse_command_id_list();
    if( arrayp(ids) )
        foreach(string id in ids)
            if( strsrch(id, "zombie") >= 0 ) return 1;
    return 0;
}

// ------------------------------------------------------------------
// 顯示：敘述灰色、咒文名稱黃色；排版照天師咒術
// （起手一行、空行、效果、空行、結果）。
// ------------------------------------------------------------------

void say_line(object me, object target, string msg)
{
    message_vision(HIK + msg + NOR "\n", me, target, 1);
}

void blank(object me)
{
    message_vision("\n", me, 0, 1);
}

string spell_title(string spell)
{
    return HIY "「" + SPELLS[spell][4] + "」" NOR HIK;
}

void start_line(object me, object target, string spell)
{
    say_line(me, target, "$N拈起一張正陽符﹐口中念念有詞﹐開始施展" + spell_title(spell) + " ....");
    blank(me);
}

string effect_line(string spell)
{
    if( spell == "netherbolt" )
        return "$N將正陽符往空中一拋﹐符紙化作一支青幽幽的小箭﹐箭尖直指$n眉心。";
    if( spell == "drainerbolt" )
        return "$N雙指夾著正陽符一抖﹐符紙化作一支紫瑩瑩的長箭﹐箭身繞著幽幽的寒光。";
    return "$N將正陽符按在掌心一搓﹐符紙化作一支蒼白的重箭﹐箭上隱隱有鬼影流轉。";
}

string hit_line(string spell, int dummy)
{
    if( dummy ) {
        if( spell == "netherbolt" ) return "青箭釘在$n身上﹐留下一個冒著青煙的小洞。";
        if( spell == "drainerbolt" ) return "紫箭貫入$n﹐箭尾猶自微微顫動﹐寒光久久不散。";
        return "蒼箭重重撞上$n﹐撞出一道深深的裂痕。";
    }
    if( spell == "netherbolt" ) return "青箭釘入$n的肩頭﹐$n只覺一股陰寒直透心神﹐不由得悶哼一聲。";
    if( spell == "drainerbolt" ) return "紫箭貫入$n的胸口﹐$n眼前一黑﹐精力似乎隨著箭身被抽走了一截。";
    return "蒼箭重重撞在$n身上﹐$n只覺五臟翻騰﹐氣力被抽去了大半。";
}

string miss_line(string spell)
{
    if( spell == "netherbolt" ) return "$n偏頭一閃﹐青箭擦著耳際飛過﹐無聲散成一縷青煙。";
    if( spell == "drainerbolt" ) return "$n就地一滾﹐紫箭釘在地上﹐寒光一閃便熄了。";
    return "$n橫身急退﹐蒼箭落空﹐在地上炸成一團慘白的霧氣。";
}

string gain_line(string spell)
{
    if( spell == "netherbolt" ) return "一縷青氣自$n身上被箭引了回來﹐沒入$N的眉心﹐$N的神思清明了許多。";
    if( spell == "drainerbolt" ) return "一縷紫氣自$n身上被箭引了回來﹐沒入$N的胸口﹐$N的精神振作了許多。";
    return "一縷蒼氣自$n身上被箭引了回來﹐沒入$N的丹田﹐$N的氣力充盈了許多。";
}

// ------------------------------------------------------------------
// 施咒：命中照天師咒術（不看抗性）；
// 傷害 = 咒文強度 × 75% × 攻擊乘數，對殭屍、鬼魂、動物 125%；
// 打中後補給自己：神 = 靈性 × 2、精 = 敏捷 × 2、氣 = 體格 × 4。
// ------------------------------------------------------------------

int do_bolt(object me, object target, string spell, int sen)
{
    int power, dealt, gain, dummy;
    string stat;

    me->fight_ob(target);
    target->fight_ob(me);
    dummy = target->query("training_dummy") ? 1 : 0;

    start_line(me, target, spell);
    say_line(me, target, effect_line(spell));
    blank(me);

    if( !SPELLS_D->spell_hits(me, target, "purify", 1) ) {
        say_line(me, target, miss_line(spell));
        return 0;
    }

    power = SPELLS_D->spell_strength(me, sen) * 75 / 100 * SPELLS[spell][2];
    if( is_unclean(target) ) power = power * 125 / 100;
    if( power < 1 ) power = 1;

    dealt = target->receive_damage(power, me, me);
    say_line(me, target, hit_line(spell, dummy));
    if( objectp(target) ) COMBAT_D->report_status(target);

    stat = SPELLS[spell][3];
    if( stat == "sen" ) gain = me->query_attr("spi") * 2;
    else if( stat == "gin" ) gain = me->query_attr("dex") * 2;
    else gain = me->query_attr("con") * 4;
    if( gain > 0 ) {
        me->supplement_stat(stat, gain);
        say_line(me, target, gain_line(spell));
    }

    if( userp(me) ) me->gain_score("combat", (1 + dealt / 40) > 20 ? 20 : (1 + dealt / 40));
    return 1;
}

varargs int cast_spell(object me, string spell, object target)
{
    object scroll, *enemies;
    int sk, sen, hit;

    if( me->skill_mapped("spells") != "taoism of purify" )
        return notify_fail("你沒有使用幽冥三箭。\n");
    if( me->is_busy() ) return notify_fail("你現在沒有空施咒。\n");
    if( !stringp(spell) || undefinedp(SPELLS[spell]) )
        return notify_fail("指令格式﹕cast <咒文名稱> [on <施咒對象>]\n");

    sk = me->query_skill("taoism of purify", 1);
    /* 求教後還沒學成的 0 級也算學會，可以施展需求 0 級的青冥之箭。 */
    if( (sk < 1 && me->query_learn("taoism of purify") < 1) || sk < SPELLS[spell][0] )
        return notify_fail("你的幽冥三箭火候未到﹐還驅使不了這道咒法。\n");

    if( !objectp(target) ) {
        enemies = me->query_enemy();
        if( sizeof(enemies) ) target = enemies[0];
    }
    if( !objectp(target) || target == me || !living(target)
    ||  environment(target) != environment(me) )
        return notify_fail("這裡沒有可施咒的對象。\n");
    if( userp(target) )
        return notify_fail("幽冥三箭只能射向 NPC。\n");

    if( !(scroll = find_scroll(me)) )
        return notify_fail("你身上沒有正陽符﹐無從施展幽冥三箭。\n");
    sen = me->query_stat("sen");
    if( sen < SPELLS[spell][1] )
        return notify_fail("你心神渙散﹐無法施展幽冥三箭。\n");

    me->consume_stat("sen", SPELLS[spell][1]);
    scroll->add_amount(-1);
    // 每次施展得法術修為 random(靈性/2) + 1（比照天師咒術）。
    me->gain_score("magic", random(me->query_attr("spi") / 2) + 1);
    hit = do_bolt(me, target, spell, sen);

    spell_gain(me, SPELLS[spell][2], hit);
    me->start_busy(1);
    return 1;
}
