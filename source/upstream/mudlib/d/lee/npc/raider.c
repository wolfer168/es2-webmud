// /d/lee/npc/raider.c — 野羊山入侵者的共用程式（李家村事件，設計見 docs/LEE_BANDIT_RAID.md）。
//
// 入侵者在李家村裡四處走動，碰到村民或玩家就動手；一律只「打」（fight），不下死手，
// 所以村民被打昏而不會死。走動頻率略快於鬼魂，而且絕不離開李家村（由 raid_d 判定哪些房間算李家村）。
// 村民會不會被打，看村裡有多少玩家：人越多，被放過的機率越高（raid_d 的 spare_chance）。
// 死亡時先回報 raid_d，全部死光事件就結束。

#include <npc.h>
#include <ansi.h>

inherit F_FIGHTER;

#define RAID_D "/daemon/misc/lee_raid_d"

private int raid_act();

int is_raider() { return 1; }

// 在子類別 create() 的 setup() 之前呼叫：設定走動與出手的節奏。
// 鬼魂每 tick 約 6% 移動（chat_chance 9、三句裡兩句是移動），入侵者每 tick 約 12%。
void setup_raider()
{
    set("raider", 1);
    set("chat_chance", 12);
    set("chat_msg", ({ (: raid_act :) }));
}

// 這個人值不值得動手：活著的玩家或村民，不是自己人，也不在不能打架的地方。
private int valid_target(object ob)
{
    if( !objectp(ob) || ob == this_object() || !living(ob) ) return 0;
    if( !ob->is_character() || ob->query("raider") ) return 0;
    if( wizardp(ob) || ob->query("no_fight") || ob->query("life_form") == "ghost" ) return 0;
    if( !objectp(environment(ob)) || environment(ob)->query("no_fight") ) return 0;
    if( !visible(ob) || is_fighting(ob) ) return 0;
    return 1;
}

private int attack_target(object ob)
{
    int id;

    if( !userp(ob) ) {
        // 村民一場事件只決定一次：被放過的就一直放過。
        id = RAID_D->query_event_id();
        if( ob->query_temp("raid/roll") != id ) {
            ob->set_temp("raid/roll", id);
            ob->set_temp("raid/spare", random(100) < RAID_D->spare_chance());
        }
        if( ob->query_temp("raid/spare") ) return 0;
    }

    message_vision(({
        HIR "$N一聲怪叫﹐掄起兵刃就撲向$n﹗\n" NOR,
        HIR "$N獰笑著逼近$n﹐擺開架勢動起手來﹗\n" NOR,
        HIR "$N朝地上啐了一口﹐扯開嗓門罵著衝向$n﹗\n" NOR,
    })[random(3)], this_object(), ob);
    fight_ob(ob);
    ob->fight_ob(this_object());
    return 1;
}

// 往李家村裡的相鄰房間走一步；出口通到村外（上山小路、南邊入口、客棧等）的一律不走。
private void raid_move()
{
    mapping exits;
    string *dirs = ({}), dir;

    if( !objectp(environment()) || !mapp(exits = environment()->query("exits")) ) return;
    foreach(dir in keys(exits))
        if( stringp(exits[dir]) && RAID_D->in_village(exits[dir]) ) dirs += ({ dir });
    if( !sizeof(dirs) ) return;
    "/cmds/std/go"->main(this_object(), dirs[random(sizeof(dirs))]);
}

private int raid_act()
{
    object ob;

    if( !objectp(environment()) || !living(this_object()) || is_fighting() ) return 0;
    foreach(ob in all_inventory(environment()))
        if( valid_target(ob) && attack_target(ob) ) return 1;
    raid_move();
    return 1;
}

// 有人走進來（或自己走進有人的房間）就動手。
void init()
{
    object ob = this_player();

    ::init();
    if( !living(this_object()) || is_fighting() ) return;
    if( valid_target(ob) ) attack_target(ob);
}

// 入侵者不挑對手，任何人找他單挑都奉陪。
int accept_fight(object ob)
{
    return 1;
}

void die()
{
    RAID_D->raider_died(this_object());
    ::die();
}
