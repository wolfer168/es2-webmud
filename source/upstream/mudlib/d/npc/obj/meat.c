// /d/npc/obj/meat.c — 凶暴的野熊身上的一團肉塊。
// 總共可補 1000 食物；每口補 100，離食物上限不到 100 就補到滿；吃完消失。不可堆疊。

inherit ITEM;

void create()
{
    set_name("肉塊", ({ "meat" }));
    set_weight(500);
    if( !clonep() ) {
        set("unit", "團");
        set("value", 0);
        set("long", "一團血淋淋的生肉。\n");
    }
    set("meat_left", 1000);
    setup();
}

int stuff_ob(object me)
{
    int need = me->query_stat_maximum("food") - me->query_stat("food");
    int left = query("meat_left");
    int bite;

    if( need <= 0 )
        return notify_fail("你的肚子已經撐得什麼東西也吞不下去了。\n");
    bite = need < 100 ? need : 100;
    if( bite >= left ) {
        me->supplement_stat("food", left);
        message_vision("$N把剩下的肉塊一口吞下。\n", me);
        destruct(this_object());
        return 1;
    }
    me->supplement_stat("food", bite);
    set("meat_left", left - bite);
    message_vision("$N狠狠的咬了一口肉塊，看起來很滿足的樣子。\n", me);
    return 1;
}
