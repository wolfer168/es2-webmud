// fish.c — 釣魚。設計見 docs/FISHING_DESIGN.md。
//
// 在有水的房間（房間設定 fishing）下竿，每 1 tick 判定一次：
//   第 n 個 tick（n = 1…9）：(n-1)×20 + random(捕魚技巧) > 200 就釣起；第 10 個 tick 必定釣起。

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

private object find_rod(object me)
{
    object ob;

    foreach( ob in all_inventory(me) )
        if( ob->id("stick") || ob->id("rod") || ob->id("fishing stick") || ob->id("fishing rod") )
            return ob;
    return 0;
}

private string *CATCH_MSG = ({
    "浮標猛地往下一沉﹐$N手腕一翻﹐一尾河魚被甩出水面﹐在半空閃著銀光。\n",
    "絲線忽然繃直﹐$N穩住竿身緩緩收線﹐一尾河魚拖著水花被拉上了岸。\n",
    "水面「嘩」地炸開﹐$N順勢提竿﹐一尾河魚已經在鉤上活蹦亂跳。\n",
});

private string *WAIT_MSG = ({
    "浮標輕輕晃了一下﹐又歸於平靜。\n",
    "水面泛起一圈小小的漣漪﹐不知是魚兒碰了碰餌。\n",
    "一陣風過﹐絲線在水面上微微顫動。\n",
});

private void end_fish(object me, int caught)
{
    me->delete_temp("fishing");
}

/* 每 tick 呼叫一次；傳回 0 表示結束。 */
int do_fish(object me)
{
    int tick, s, hit;
    object fish;

    if( !me || !environment(me) ) return 0;
    if( !environment(me)->query("fishing") ) {
        end_fish(me, 0);
        return 0;
    }

    tick = me->add_temp("fishing/tick", 1);
    s = me->query_skill("halieutics");

    if( tick >= 10 ) hit = 1;
    else hit = ((tick - 1) * 20 + (s > 0 ? random(s) : 0) > 200);

    if( !hit ) {
        if( random(3) == 0 )
            tell_object(me, WAIT_MSG[random(sizeof(WAIT_MSG))]);
        return 1;
    }

    fish = new("/obj/food/river_fish");
    message_vision(CATCH_MSG[random(sizeof(CATCH_MSG))], me);
    if( !fish->move(me) ) {
        fish->move(environment(me));
        tell_object(me, "你身上拿不下了﹐河魚只好放在地上。\n");
    }
    // 等得越久，技巧點數越少（第 1 tick 100 點、第 10 tick 10 點）。
    me->improve_skill("halieutics", (11 - tick) * 10);
    end_fish(me, 1);
    return 0;
}

int halt_fish(object me, object who, string how)
{
    end_fish(me, 0);
    message_vision("$N收起釣竿﹐這回算是白忙一場。\n", me);
    return 1;
}

int main(object me, string arg)
{
    object rod, bait;

    if( !environment(me) || !environment(me)->query("fishing") )
        return notify_fail("這裡沒有可以垂釣的水邊。\n");
    if( me->is_fighting() )
        return notify_fail("刀光劍影之中﹐哪有閒情釣魚？\n");
    if( me->query_temp("fishing") )
        return notify_fail("你已經下了竿﹐耐心等著吧。\n");
    if( me->is_busy() )
        return notify_fail("你正忙著別的事。\n");
    if( !(rod = find_rod(me)) )
        return notify_fail("你身上沒有釣竿﹐空手怎麼釣魚？\n");
    if( !objectp(bait = present("bait", me)) )
        return notify_fail("鉤上空空的﹐魚兒是不會理你的﹐總得先有點魚餌。\n");

    bait->add_amount(-1);
    me->set_temp("fishing/tick", 0);
    message_vision("$N把魚餌掛上鉤﹐手腕輕輕一抖﹐絲線劃出一道弧線﹐魚鉤「噗通」一聲沒入水中。\n", me);
    me->start_busy((: do_fish, me :), (: halt_fish, me :));
    return 1;
}

int help(object me)
{
    write(@HELP
指令格式﹕fish

在河邊、溪邊或池邊垂釣。身上要帶著釣竿(stick 或 rod)和魚餌(bait)﹐
下竿會用掉一份魚餌。魚兒上鉤要等一會兒﹐捕魚技巧越高﹐等得越短﹐
最多等十個 tick 一定會釣起一尾河魚。等待的時候可以用 halt 收竿。
HELP
    );
    return 1;
}
