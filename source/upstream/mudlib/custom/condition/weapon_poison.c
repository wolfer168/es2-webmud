/* CUSTOM WEAPON CONDITION BASE: 武器劇毒的共用規則。
 *
 * 各毒放在 daemon/condition/<名稱>.c，繼承這個檔案並定義：
 *   poison_msg()   中毒時的敘述（以「你」開頭，同房間的人看到把「你」換成名字）
 *   burst_ticks()  幾 tick 發作一次（1 tick = 一次心跳 2 秒）
 *   burst_count()  共發作幾次
 *   burst_damage() 每次發作的傷害：({ ({ 屬性, 實格扣, 目前值扣 }), ... })
 *
 * 實格（heal 值）是可隨時間恢復的上限，不是永久扣除。每次發作先扣目前值、
 * 再扣實格，例如 500/500 每次目前值 -10、實格 -8：490/492、480/484、470/476。
 *
 * 武器命中並造成傷害時呼叫 poison(目標, 攻擊者)。已中毒時再被命中，只把剩餘
 * 次數重設為滿，發作節奏不變。發作敘述固定為「你中的毒發作了！」。
 */
#include <condition.h>

inherit CONDITION;

#define TICK_SECONDS    2

string poison_msg() { return "你中毒了！"; }
int burst_ticks() { return 2; }
int burst_count() { return 4; }
mixed *burst_damage() { return ({}); }

// 發作靠 call_out 串起來，保持載入。
int clean_up() { return 1; }

string cnd_name() { return explode(base_name(this_object()), "/")[<1]; }

private void burst(object me, object from)
{
    if( !objectp(from) ) from = me;

    tell_object(me, "你中的毒發作了！\n");
    if( environment(me) )
        message("vision", me->name() + "中的毒發作了！\n", environment(me), me);

    foreach(mixed *d in burst_damage()) {
        if( d[2] ) me->consume_stat(d[0], d[2], from);
        if( objectp(me) && d[1] ) me->damage_stat(d[0], d[1], from);
        if( !objectp(me) ) return;
    }
}

void poison_tick(object me, int serial)
{
    mapping data;

    if( !objectp(me) ) return;
    data = me->query_condition(cnd_name());
    if( !mapp(data) || data["serial"] != serial ) return;

    burst(me, data["from"]);
    if( !objectp(me) ) return;

    // 直接修改 data：set_condition() 會觸發 unapply/apply 而多開一條計時。
    data["left"]--;
    if( data["left"] <= 0 ) {
        me->delete_condition(cnd_name());
        return;
    }
    call_out("poison_tick", TICK_SECONDS * burst_ticks(), me, serial);
}

// 武器命中時呼叫。沒中毒就開始計時；已中毒只把剩餘次數重設為滿。
void poison(object me, object from)
{
    string msg;
    mapping data;

    // 練武假人是死物，毒性滲不進去（使用者指示，2026-11-02）。
    if( !objectp(me) || me->query("training_dummy") ) return;

    msg = poison_msg();
    data = me->query_condition(cnd_name());

    tell_object(me, msg + "\n");
    if( environment(me) )
        message("vision", replace_string(msg, "你", me->name(), 1) + "\n", environment(me), me);

    if( mapp(data) ) {
        data["left"] = burst_count();
        data["from"] = from;
        return;
    }
    me->set_condition(cnd_name(), ([
        "left":     burst_count(),
        "from":     from,
        "serial":   time() * 1000 + random(1000),
    ]));
}

// 上毒或重新登入時開始計時；第一次發作在 burst_ticks() 之後。
void condition_apply(object me, string cnd, mixed data)
{
    if( !mapp(data) ) return;
    call_out("poison_tick", TICK_SECONDS * burst_ticks(), me, data["serial"]);
}

varargs void condition_unapply(object me, string cnd, mixed data) { }

void condition_update(object me, string cnd, mixed data)
{
    if( !mapp(data) || data["left"] <= 0 ) me->delete_condition(cnd);
}
