/* CUSTOM WEAPON CONDITION: 藍涎刀之毒 (blue_venom)
 *
 * 藍涎刀每次命中都會上毒，持續 10 tick（1 tick = 一次心跳 2 秒）。
 * 每 2 tick 發作一次：精最大值 -3、精目前值 -5、氣最大值 -2、氣目前值 -4、
 * 形體 -2。持續時間內共發作 5 次。
 *
 * 再次命中只會把剩餘時間重新設為 10 tick，發作節奏仍維持每 2 tick 一次，
 * 不會因為一直被砍中而延後發作。昏倒時照樣毒發、繼續扣形體，形體扣到 0
 * 就會死亡（由種族 daemon 的 statistic_exhausted() 處理）。
 */
#include <ansi.h>
#include <condition.h>

inherit CONDITION;

#define TICK_SECONDS    2
#define DURATION_TICKS  10
#define BURST_TICKS     2

// 發作靠 call_out 串起來，保持載入。
int clean_up() { return 1; }

// 毒傷算在下毒的人頭上；對方已經不在（或重新登入後）就算在自己身上。
private void burst(object me, object from)
{
    if( !objectp(from) ) from = me;

    tell_object(me, "你中的毒發作了！\n");
    if( environment(me) )
        message("vision", me->name() + "中的毒發作了！\n", environment(me), me);

    // 先扣目前值，再扣實格（可隨時間恢復的上限）。
    me->consume_stat("gin", 5, from);
    me->damage_stat("gin", 3, from);
    me->consume_stat("kee", 4, from);
    me->damage_stat("kee", 2, from);
    me->consume_stat("HP", 2, from);
}

void venom_tick(object me, int serial)
{
    mapping data;

    if( !objectp(me) ) return;
    data = me->query_condition("blue_venom");
    if( !mapp(data) || data["serial"] != serial ) return;

    burst(me, data["from"]);
    if( !objectp(me) ) return;

    // 直接修改 data：set_condition() 會觸發 unapply/apply 而多開一條計時。
    data["left"] -= BURST_TICKS;
    if( data["left"] < BURST_TICKS ) {
        me->delete_condition("blue_venom");
        return;
    }
    call_out("venom_tick", TICK_SECONDS * BURST_TICKS, me, serial);
}

// 藍涎刀命中時呼叫。沒中毒就開始計時；已中毒只把剩餘時間重設為 10 tick。
void poison(object me, object from)
{
    mapping data;

    // 練武假人是死物，毒性滲不進去（使用者指示，2026-11-02）。
    if( !objectp(me) || me->query("training_dummy") ) return;

    data = me->query_condition("blue_venom");

    tell_object(me, "你突然感到一陣冷冽的蝕骨之痛從傷口傳了過來！\n");
    if( environment(me) )
        message("vision", me->name() + "突然感到一陣冷冽的蝕骨之痛從傷口傳了過來！\n",
            environment(me), me);

    if( mapp(data) ) {
        data["left"] = DURATION_TICKS;
        data["from"] = from;
        return;
    }
    me->set_condition("blue_venom", ([
        "left":     DURATION_TICKS,
        "from":     from,
        "serial":   time() * 1000 + random(1000),
    ]));
}

// 上毒或重新登入時開始計時；第一次發作在 2 tick 之後。
void condition_apply(object me, string cnd, mixed data)
{
    if( !mapp(data) ) return;
    call_out("venom_tick", TICK_SECONDS * BURST_TICKS, me, data["serial"]);
}

void condition_unapply(object me, string cnd, mixed data) { }

void condition_update(object me, string cnd, mixed data)
{
    if( !mapp(data) || data["left"] < BURST_TICKS ) me->delete_condition(cnd);
}
