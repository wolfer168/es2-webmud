

#include <command.h>
#include <login.h>

inherit F_CLEAN_UP;

int do_give(object me, object item, object who);

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    string target, item;
    object obj, who, *inv, obj2, fwho;
    int i, amount;

    if(!arg) return notify_fail("你要給誰什麼東西﹖\n");

    if( !(sscanf(arg, "%s to %s", item, target)==2
        || sscanf(arg, "%s %s", target, item)==2) )
        return notify_fail("你要給誰什麼東西﹖\n");

    if( !objectp(who = present(target, environment(me)))
    ||  !living(who))
        return notify_fail("這裡沒有 \"" + target + "\" 這個人。\n");

    if(who==me) return notify_fail("你給自己東西幹麻﹖\n");

    // add by dragoon
    if( objectp(who) && who->query("no_fight") )
        return notify_fail("什麼??\n");

    if(sscanf(item, "%d %s", amount, item)==2)
    {
        if( !objectp(obj = present(item, me)) )    
            return notify_fail("你身上沒有這樣東西。\n");
        // 增加不能把玩家給人的檢查 -Dragoon
        if( obj->query("no_drop") || userp(obj) )
            return notify_fail("這樣東西不能隨便給人。\n");
        if( !obj->query_amount() )    
            return notify_fail( obj->name() + "不能被分開給人。\n");
        if( amount < 1 )
            return notify_fail("東西的數量至少是一個。\n");
        if( amount > obj->query_amount() ) 
            return notify_fail("你沒有那麼多的" + obj->name() + "。\n");
        else if( amount == (int)obj->query_amount() )
            return do_give(me, obj, who);
        else {
            seteuid(MUDLIB_UID);
            obj2 = new(base_name(obj));
            seteuid(getuid());
            obj2->set_amount(amount);
            if( do_give(me, obj2, who) ) {
                obj->add_amount(-amount);
                return 1;
            } else {
                destruct(obj2);
                return 0;
            }
        }
    }

    if( arg=="all" ) {
        foreach(object ob in all_inventory(me))
            do_give(me, ob, who);
        write("Ok.\n");
        return 1;
    }

    if(!objectp(obj = present(item, me)))
        return notify_fail("你身上沒有這樣東西。\n");

    return do_give(me, obj, who);
}

private int
do_give(object me, object item, object who)
{
    if( item->query("no_drop") )
        return notify_fail("這樣東西不能隨便給人。\n");

    if( who->over_encumbranced() )
        return notify_fail( who->name() + "已經負荷過重﹐再也搬不動任何東西了。\n");

    notify_fail("看起來" + who->name() + "並不願意收下這" + item->query("unit")
        + item->name() + "。\n");

    if( !userp(who) ) {
        // 先確認 NPC 放得下再問他收不收：NPC 答應後常會立刻給獎或推進任務，
        // 若之後才搬不進去，東西還在玩家身上卻已拿到好處（使用者定案，2026-11-22）。
        // 錢（value() 有值）交出後直接銷毀，不佔 NPC 的位子，不必檢查。
        if( !item->value()
        &&  (sizeof(all_inventory(who)) >= 20
            || who->query_encumbrance() + item->weight() > who->query_strength("carriage")) )
            return notify_fail(who->name() + "身上已經放不下了。\n");
        if( !who->accept_object(me, item) ) return 0;
        // 只有錢有 value() 函式，所以這裡只會銷毀錢；其他東西照常交到 NPC 身上，
        // 要不要刪掉由各 NPC 自己處理（例：call_out("drop_item", 1, ob)）。
        if( item->value() ) {

            // 只顯示數量與中文名稱（例：五兩黃金），不帶英文 ID（使用者指示，2026-11-24）。
            message_vision("$N拿出" + chinese_number(item->query_amount())
                + item->query("base_unit") + item->name() + "交給$n。\n", me, who);
            destruct(item);
            return 1;
        }
    }

    if( !item->move(who) ) return 0;

    if( wizardp(me) && (userp(who) && !wizardp(who)) )
        log_file( "static/GIVE", sprintf("[%s] %s gived %s to %s\n",
                ctime(time()), geteuid(me), item->name(), geteuid(who)) );
    message_vision("$N交給$n一" + item->query("unit") + item->name()
        + "。\n", me, who );

    return 1;
}

int help(object me)
{
    write(@HELP
指令格式 : give <物品名稱> to <某人>
           give <某人> <物品名稱>

這個指令可以讓你將某樣物品給別人。
 
HELP
    );
    return 1;
}

