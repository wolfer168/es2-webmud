/* CUSTOM A-H RACE COMMAND: blackteeth gnaw */
#include <ansi.h>
inherit F_CLEAN_UP;
private void create() { seteuid(getuid()); }
int main(object me, string arg) {
    object victim;
    int damage, duration, age, mine, theirs, ratio, roll;
    mapping data;
    if (me->query_race() != "blackteeth") return notify_fail("你不是黑齒，無法使用 gnaw。\n");
    if (!arg || !objectp(victim = present(arg, environment(me))) || !victim->is_character() || victim == me)
        return notify_fail("你要咬誰？\n");
    if (environment(me)->query("no_fight") || victim->query("no_fight")) return notify_fail("這裡不能這麼做。\n");
    if (!me->is_fighting(victim)) return notify_fail("你必須先與對方進入戰鬥。\n");

    age = me->query("age");
    damage = 1 + age / 20;
    victim->consume_stat("kee", damage, me);
    message_vision(HIR "$N猛然張口咬住$n，狠狠地撕咬了一口！\n" NOR, me, victim);

    // Poison only lands on top of a successful bite: roll 1~3, success if
    // the roll is below (own(gin+kee) x1.5 / opponent(gin+kee)) -- the same
    // "ratio of a combined stat, dice under it wins" shape as hide/hoof.
    mine = me->query_stat("gin") + me->query_stat("kee");
    theirs = victim->query_stat("gin") + victim->query_stat("kee"); if (theirs < 1) theirs = 1;
    ratio = (mine * 3 / 2) / theirs;
    roll = 1 + random(3);
    // 練武假人是死物，不會中毒（使用者指示，2026-11-02）。
    if (roll < ratio && !victim->query("training_dummy")) {
        duration = 1 + age / 10; if (duration > 12) duration = 12;
        damage = 5 + age / 15; if (damage > 15) damage = 15;
        load_object("/custom/race/condition/blackteeth_gnaw");
        data = ([
            "duration":duration,
            "kee_loss":damage,
            "serial":time() * 1000 + random(1000)
        ]);
        victim->set_condition("blackteeth_gnaw", data);
        message_vision(HIR "齒間的毒性隨傷口滲入了$n的體內！\n" NOR, me, victim);
    }
    return 1;
}
int help(object me) {
    write("指令格式：gnaw <人物>\n"
        "黑齒咬擊造成 (1 + 自身年紀/20) 點氣傷害。\n"
        "另外機率附加中毒：骰 1~3 < 自身(精+氣)x1.5 / 對手(精+氣) 則中毒。\n"
        "中毒後每 tick 扣目標 (5+自身年紀/15) 點氣目前值（最多 15 點），"
        "持續 (1+自身年紀/10) tick，最多 12 tick（所有除法取整數）。\n");
    return 1;
}
