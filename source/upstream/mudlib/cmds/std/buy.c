

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    string item, targ, rest, err;
    object ob, owner;
    mixed handle;
    int price, afford, amount;

    if( me->is_busy() ) return notify_fail("你現在沒有空﹗\n");

    if( !arg || sscanf(arg, "%s from %s", item, targ)!=2 )
        return notify_fail("指令格式﹕buy [數量] <某物> from <某人>\n");

    // buy 10 manto from waiter：一次買多個。
    if( sscanf(item, "%d %s", amount, rest) == 2 && amount > 0 ) item = rest;
    else amount = 1;
    if( amount > 100 ) return notify_fail("一次最多只能買一百個。\n");

    if( !objectp(owner = present(targ, environment(me))) )
        return notify_fail("你要跟誰買東西﹖\n");

    if( userp(owner) ) {
        message_vision("$N想向$n購買「" + item + "」。\n", me, owner);
        return 1;
    }

    // add by dragoon
        if( objectp(owner) && owner->query("no_fight") )
                return notify_fail("什麼??\n");

    if( !living(owner) )
        return notify_fail("看起來"+owner->name()+"已經無法買賣東西了。\n");
        
    if( owner->is_fighting() )
        return notify_fail("看起來" + owner->name() + "正忙著 ... 打架﹐沒空理你。\n");

    notify_fail("對方好像不願意跟你交易。\n");
    if( !(handle = owner->affirm_merchandise(me, item, amount)) ) return 0;
    price = owner->query_trading_price(handle) * amount;

    switch( me->can_afford(price) ) {
        case 0: return notify_fail("你身上的錢不夠。\n");
        case 1:
            // 先交貨再收錢：交貨出錯時不扣錢（以前會先扣錢，物品出錯就白付）。
            if( err = catch(owner->deliver_merchandise(me, handle, amount)) ) {
                write("這筆交易出了點問題，" + owner->name() + "沒有收你的錢。\n");
                return 1;
            }
            me->pay_money(price);
            // 買東西的江湖歷練：random(價錢 ÷ 200 + 悟性)（使用者指示，2026-11-20）。
            me->gain_score("survive", random(price/200 + me->query_attr("int")) );
            return 1;
        case 2:
            // CUSTOM finance no longer returns this value; keep a safe fallback.
            return notify_fail("交易暫時無法完成。\n");
    }

}

int help(object me)
{
   write( @HELP
指令格式: buy [數量] <something> from <someone>

這一指令讓你可以從某些人身上買到物品。
加上數量可以一次買多個，例如 buy 10 manto from waiter，一次最多一百個。
可以堆疊的東西（例如饅頭）會合成一堆；其他東西則一件一件交給你，
身上拿不動的部分會直接消失，錢一樣照算。
HELP
   );
   return 1;
}

