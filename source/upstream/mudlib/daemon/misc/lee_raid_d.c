// /daemon/misc/lee_raid_d.c — 李家村事件管理：野羊山山賊洗劫李家村。
// NEW（設計見 docs/LEE_BANDIT_RAID.md）。
//
// 流程：李嘯天（d/lee/npc/lee_xiao_tian.c）答應幫忙後，玩家到上山小路（d/lee/wroad5.c）把孝敬交給
// 野羊山探子（d/lee/npc/bandit_scout.c）；探子放煙火、10～20 tick 後山賊入侵李家村，
// 入侵者全部死亡就收尾。全服同一時間只有一場事件，伺服器重開（rb）後才能再觸發。
// 「連續開啟」的紀錄（誰開的、連續幾次）存在 data/lee_raid.o，重開後仍然記得。
//
// 狀態：IDLE 閒置／WAIT_PAY 探子等人交錢／SIGNAL 煙火放了、等入侵／RAID 入侵中／DONE 結束（等重開）。

#include <ansi.h>

inherit F_SAVE;

#define ST_IDLE      0
#define ST_WAIT_PAY  1
#define ST_SIGNAL    2
#define ST_RAID      3
#define ST_DONE      4

#define BASE_PRICE   3000      // 第一次的孝敬（兩）
#define STEP_PRICE   1000      // 連續開啟每次加價
#define PAY_LIMIT    60        // 探子問過之後，多久沒交錢就算失敗（秒）
#define SIGNAL_MIN   10        // 煙火後多少 tick 開始入侵（一 tick 兩秒）
#define SIGNAL_RANGE 11        // 再隨機加 0～10 tick
#define SPARE_STEP   15        // 村裡每多一位玩家，村民被放過的機率增加多少 %
#define SPARE_MAX    90

#define BOSSES  ({ "/d/lee/npc/bandit_chief", "/d/lee/npc/bandit_second", \
                   "/d/lee/npc/bandit_third", "/d/lee/npc/bandit_fourth" })

// 李家村裡入侵者能去的房間（不含客棧、南邊入口、聶家密室與上山小路）。
#define VILLAGE_ROOMS ({ "creek", "eroad1", "eroad2", "farm_w1", "farm_w2", "gate_e", "gate_n", \
    "gate_s", "gate_w", "grocery", "herb_shop", "hunter", "nroad1", "nroad2", "nroad3", \
    "pawnshop", "riverside_n1", "riverside_n2", "riverside_s", "school", "shrine", \
    "square_c", "square_e", "square_s", "square_w", "street1", "street2", \
    "watermelon_n1", "watermelon_n2", "watermelon_n3", "watermelon_s1", "watermelon_s2", \
    "watermelon_s3", "wroad1", "wroad2", "wroad3", "wroad4" })

string last_starter = "";   // 上一位開啟事件的玩家（存檔）
int streak = 0;             // 他連續開啟了幾次（存檔）

static int state = ST_IDLE;
static string cur_who = "";           // 這一場的開啟者
static object scout;                  // 正在等錢的探子
static object *invaders = ({});
static int event_id = 0;              // 每一場不同，給村民記「這場我決定過了」用

void finish();

void create()
{
    seteuid(getuid());
    restore();
}

string query_save_file() { return DATA_DIR + "lee_raid"; }

int query_state() { return state; }
int query_event_id() { return event_id; }
string query_starter() { return cur_who; }

// 這位玩家這次要付多少兩：同一個人連續開啟每次加價，換人就重算。
int query_price(object who)
{
    int n = (stringp(last_starter) && last_starter == who->query("id")) ? streak : 0;

    return BASE_PRICE + STEP_PRICE * n;
}

// ------------------------------------------------------------------
// 廣播
// ------------------------------------------------------------------

private object *village_rooms()
{
    object ob, *list = ({});
    string name;

    foreach(name in VILLAGE_ROOMS) {
        ob = find_object("/d/lee/" + name);
        if( objectp(ob) ) list += ({ ob });
    }
    return list;
}

private void broadcast(string msg)
{
    object room;

    foreach(room in village_rooms()) message("vision", msg, room);
}

// 這個房間（路徑）是不是入侵者能去的李家村房間。
int in_village(mixed room)
{
    string path, tmp;

    if( objectp(room) ) path = base_name(room);
    else path = room;
    if( !stringp(path) ) return 0;
    if( sscanf(path, "%s.c", tmp) == 1 ) path = tmp;
    return member_array(path, map(VILLAGE_ROOMS, (: "/d/lee/" + $1 :))) != -1;
}

// 目前在李家村裡的玩家人數（不含巫師）。
int players_in_village()
{
    object ob;
    int n;

    foreach(ob in users())
        if( environment(ob) && in_village(environment(ob)) && !wizardp(ob) ) n++;
    return n;
}

// 入侵者放過村民的機率（%）：村裡的人越多，村民越不容易被打昏。
int spare_chance()
{
    int n = SPARE_STEP * players_in_village();

    return n > SPARE_MAX ? SPARE_MAX : n;
}

// ------------------------------------------------------------------
// 探子收錢
// ------------------------------------------------------------------

// 探子問完銀兩，開始等錢；已經有事件就傳回 0。
int begin_pay(object who, object by)
{
    if( state != ST_IDLE ) return 0;
    state = ST_WAIT_PAY;
    cur_who = who->query("id");
    scout = by;
    remove_call_out("pay_timeout");
    call_out("pay_timeout", PAY_LIMIT);
    return 1;
}

void pay_timeout()
{
    if( state != ST_WAIT_PAY ) return;
    state = ST_IDLE;
    cur_who = "";
    if( objectp(scout) ) scout->pay_failed();
    scout = 0;
}

// 探子收到錢：事件正式開啟，記下連續開啟的紀錄。
void paid(object who)
{
    string id = who->query("id");

    if( state != ST_WAIT_PAY ) return;
    remove_call_out("pay_timeout");
    if( id == last_starter ) streak++;
    else {
        last_starter = id;
        streak = 1;
    }
    save();
    state = ST_SIGNAL;
    event_id = time();
    scout = 0;
    call_out("launch", (SIGNAL_MIN + random(SIGNAL_RANGE)) * 2);
}

// ------------------------------------------------------------------
// 入侵
// ------------------------------------------------------------------

private void spawn_raider(string file)
{
    object ob;
    string room;

    room = "/d/lee/" + VILLAGE_ROOMS[random(sizeof(VILLAGE_ROOMS))];
    ob = new(file);
    if( !objectp(ob) ) return;
    if( !ob->move(room) ) {
        destruct(ob);
        return;
    }
    message_vision(HIR "$N殺氣騰騰地闖了進來﹗\n" NOR, ob);
    invaders += ({ ob });
}

void launch()
{
    string *bosses, file;
    int i;

    if( state != ST_SIGNAL ) return;
    state = ST_RAID;
    invaders = ({});

    broadcast(HIR "\n遠方方向傳來陣陣殺聲與此起彼落的哭聲，野羊山的匪子正洗劫李家村！\n\n" NOR);

    // 四位當家每次隨機出兩位。
    bosses = BOSSES;
    for( i = 0; i < 2; i++ ) {
        file = bosses[random(sizeof(bosses))];
        bosses -= ({ file });
        spawn_raider(file);
    }
    // 小兵共 20 個：捍匪 3、山賊 7、毛賊 10。
    for( i = 0; i < 3; i++ )  spawn_raider("/d/lee/npc/rough_bandit");
    for( i = 0; i < 7; i++ )  spawn_raider("/d/lee/npc/fierce_bandit");
    for( i = 0; i < 10; i++ ) spawn_raider("/d/lee/npc/bandit_thug");

    remove_call_out("watch");
    call_out("watch", 10);
}

// 入侵者死亡時回報（在屍體產生之前）。
void raider_died(object ob)
{
    invaders -= ({ ob });
    invaders -= ({ 0 });
    if( state == ST_RAID && !sizeof(invaders) ) call_out("finish", 2);
}

// 定時清點：入侵者被別的原因清掉也要能收尾。
void watch()
{
    if( state != ST_RAID ) return;
    invaders -= ({ 0 });
    if( !sizeof(invaders) ) {
        finish();
        return;
    }
    call_out("watch", 10);
}

void finish()
{
    if( state != ST_RAID ) return;
    state = ST_DONE;
    remove_call_out("watch");
    broadcast(HIY "\n山頭方向又砰地升起一枚煙火，在空中散成一團殘紅，隨風飄散。\n" NOR
        "遠處傳來一陣雜亂的呼喝與腳步聲，野羊山的匪眾丟盔棄甲，一路往山裡奔逃而去。\n\n");
}
