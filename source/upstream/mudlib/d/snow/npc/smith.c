#include <ansi.h>
// smith.c
// 撼山鎚法任務（2026-11-24，docs/martial_arts/共通_撼山鎚法.md）：把野羊山大當家西門智的黑鐵大槌
// 交給鐵匠，他認出是師父打的槌子，請玩家替他掌鎚；他用小鎚點位置，玩家跟著落鎚 (forge)，
// 連續三次落對，他就把大槌重打成一對撼山鎚，並傳授撼山鎚法。任務可重複，已經會的人只拿鎚子。說話用 say、神情用 emote，每句間隔 1 tick。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

#define HAMMER   "/custom/weapon/blunt/black_iron_hammer"
#define REWARD   "/d/snow/npc/obj/quake_hammer"
#define QH_SKILL    "quake hammer"
#define WORKER   "quake/worker"     // 鐵匠暫存：正在替他掌鎚的人
#define HOLD     "quake/hammer"     // 鐵匠暫存：收著的黑鐵大槌
#define SPOT     "quake/spot"       // 鐵匠暫存：小鎚點的位置（0 表示還沒點）
#define ROUND    "quake/round"      // 鐵匠暫存：已經落對幾次
#define NEED     3                  // 連續落對幾次算成功
#define WAIT     10                 // 點位之後等幾秒

string *spots    = ({ "left", "middle", "right" });
string *spot_cn  = ({ "左端", "正中", "右端" });

int accept_hammer(object who, object ob);

void create()
{
        set_name("鐵匠", ({ "smith" }) );
        set_race("human"); set_class("commoner");
        set_level(13);

        set("long",
                "一個身材粗壯的鐵匠﹐正忙碌地工作著。\n"
                "如果你想買一些鐵器﹐可以用 list 看有哪些東西﹐用 buy 向鐵匠購買。\n");

        set("merchandise", ([
                "/d/npc/obj/hoe": 3,
                __DIR__"obj/shovel": 5,
                "/obj/area/obj/dagger": 10,
                "/obj/area/obj/shortsword": 5,
                "/d/snow/npc/obj/large_blade": 10,  // 大刀（使用者指定，2026-10-19）
                "/d/snow/npc/obj/iron_hammer": 10,  // 鐵鎚（撼山鎚法，2026-11-24）
        ]));

        set("chat_chance", 5);
        set("chat_msg", ({
                "鐵匠將一塊燒紅的鐵塊「嗤」地一聲浸入一旁的水箱中。\n",
                "鐵匠用手中的鐵鎚在鐵砧上用力敲打。\n",
                "鐵匠說道﹕站開點﹐小心別燙著了。\n",
                "鐵匠說道﹕唉 ... 真把我給忙壞了。\n",
        }));
        set_power("C");
        setup();
        carry_object("/d/npc/obj/smock")->wear();
}

// 打了一輩子鐵，扛得動玩家交來的黑鐵大槌（撼山鎚法任務）：只放寬負重，不改屬性與戰鬥力。
int query_strength(string application)
{
        int n = ::query_strength(application);

        if( application == "carriage" && n < 100000 ) n = 100000;
        return n;
}

int accept_fight()
{
        do_chat("鐵匠瞪了瞪眼﹐說道﹕走開﹐我正忙著。\n");
        return 0;
}

void init()
{
        ::init();
        add_action("do_vendor_list", "list");
        add_action("do_forge", "forge");
}
int accept_object(object who, object ob)
{
        object thing;
        if( base_name(ob) == HAMMER ) return accept_hammer(who, ob);
        if ( !ob->id("lo iron") ) return 0;
        call_out((:command("say 喔！要製成箭嗎, 那簡單, 馬上就可以做好.\n"):),1);
        thing=new(__DIR__"obj/arrow");
        thing->move(who);
call_out((:message_vision(CYN + "鐵匠把剛做好的箭交給了$N。\n" NOR,this_player(),) :),2);
        call_out("drop_item", 1, ob);
        return 1;
}

/* 收下的東西刪掉，不留在身上（give 指令只會銷毀錢；使用者定案，2026-11-22）。 */
void drop_item(object ob)
{
    if( objectp(ob) && environment(ob) == this_object() ) destruct(ob);
}

// ------------------------------------------------------------------
// 撼山鎚法任務
// ------------------------------------------------------------------

private int still_here(object who)
{
    return objectp(who) && environment(who) == environment();
}

// 依序說話：lines 每項是一個指令字串；全部說完後呼叫 after（可為 0）。
void play(object who, string *lines, int i, string after)
{
    if( !living(this_object()) ) return;
    if( i >= sizeof(lines) ) {
        if( stringp(after) && still_here(who) ) call_other(this_object(), after, who);
        return;
    }
    command(lines[i]);
    call_out("play", 2, who, lines, i + 1, after);
}

private void talk(object who, string *lines, string after)
{
    call_out("play", 2, who, lines, 0, after);
}

// 已經會撼山鎚法，或已拿到點數還沒領悟。
private int knows_hammer(object who)
{
    return who->query_skill(QH_SKILL, 1) > 0 || who->query_learn(QH_SKILL) > 0;
}

int accept_hammer(object who, object ob)
{
    if( query_temp(WORKER) ) {
        command("say 沒看見我正忙著嗎﹖待會兒再說。");
        return 0;
    }
    if( !knows_hammer(who) && !SKILL_D(QH_SKILL)->valid_learn(who) ) {
        command("emote 接過黑鐵大槌掂了掂﹐又看了看你的胳膊﹐把槌子塞回你手裡。");
        command("say 你這身子骨還掄不動雙鎚﹐先去練練力氣吧。");
        return 0;
    }
    set_temp(WORKER, who);
    set_temp(HOLD, ob);
    // 已經會撼山鎚法（或已拿到點數）的人可以再打一對鎚子，但不會再傳授一次（使用者指示，2026-11-24）。
    if( knows_hammer(who) ) {
        talk(who, ({ "emote 接過黑鐵大槌掂了掂﹐神色又驚又喜。",
                     "say 又是一柄師父打的槌子﹗看來他老人家當年打的還不只一柄。",
                     "say 老規矩﹐我把它熔了重打一對鎚子﹐你來替我掌鎚。",
                     "emote 把黑鐵大槌送進火爐﹐把風箱拉得呼呼作響﹐爐火映得滿屋通紅。" }), "next_spot");
        return 1;
    }
    talk(who, ({ "emote 接過黑鐵大槌掂了掂﹐粗糙的手竟微微發起抖來。",
                 "say 這是我師父打的槌子……多少年了﹐竟還能再見到它。",
                 "say 我師父生前使一手雙鎚﹐左鎚點、右鎚落﹐打鐵是這樣﹐打架也是這樣。",
                 "say 這槌子太沉﹐一般人使不動﹐我把它熔了重打成一對雙鎚﹐你來替我掌鎚。",
                 "emote 把黑鐵大槌送進火爐﹐把風箱拉得呼呼作響﹐爐火映得滿屋通紅。" }), "next_spot");
    return 1;
}

// 掌鎚的人走了、昏了：不打了，把黑鐵大槌放在地上還給人家。
private int lost_worker(object who)
{
    object ob;

    if( still_here(who) && living(who) ) return 0;
    remove_call_out("timeout");
    remove_call_out("next_spot");
    ob = query_temp(HOLD);
    delete_temp(WORKER);
    delete_temp(HOLD);
    delete_temp(SPOT);
    delete_temp(ROUND);
    if( objectp(ob) ) {
        command("emote 嘆了口氣﹐用火鉗把燒得通紅的黑鐵大槌夾出來﹐擱在牆邊慢慢放涼。");
        ob->move(environment());
    }
    return 1;
}

// 小鎚點一個位置，等掌鎚的人落鎚。
void next_spot(object who)
{
    int i;

    if( query_temp(WORKER) != who || lost_worker(who) ) return;
    i = random(sizeof(spots));
    set_temp(SPOT, i + 1);
    command("emote 左手捏起小鎚﹐在燒紅的鐵塊" + spot_cn[i] + "叮地輕輕一點。");
    call_out("timeout", WAIT, who);
}

// 重新燒過，從頭再來。
private void restart(object who, string why)
{
    delete_temp(SPOT);
    set_temp(ROUND, 0);
    talk(who, ({ "emote 搖了搖頭﹐把鐵塊重新送回爐裡。",
                 "say " + why }), "next_spot");
}

void timeout(object who)
{
    if( query_temp(WORKER) != who || !query_temp(SPOT) ) return;
    if( lost_worker(who) ) return;
    restart(who, "發什麼愣﹗火候過了﹐重新燒過。");
}

int do_forge(string arg)
{
    object me = this_player();
    int spot, i;

    if( query_temp(WORKER) != me ) return 0;
    if( !(spot = query_temp(SPOT)) )
        return notify_fail("鐵匠的小鎚還沒點下去﹐你先別急著落鎚。\n");
    if( !arg ) return notify_fail("你要往鐵塊的哪裡落鎚﹖\n");
    i = member_array(arg, spots);
    if( i < 0 ) i = member_array(arg, ({ "左", "中", "右" }));
    if( i < 0 ) i = member_array(arg, spot_cn);
    if( i < 0 ) return notify_fail("你要往鐵塊的哪裡落鎚﹖\n");

    remove_call_out("timeout");
    delete_temp(SPOT);
    if( i + 1 != spot ) {
        message_vision("$N掄起大鎚往鐵塊" + spot_cn[i] + "砸下﹐噹的一聲卻砸偏了位置。\n", me);
        restart(me, "點在哪兒就落在哪兒﹐重新燒過。");
        return 1;
    }
    message_vision("$N掄起大鎚照著點位落下﹐噹的一聲﹐火星四濺。\n", me);
    add_temp(ROUND, 1);
    if( query_temp(ROUND) < NEED ) {
        command("emote 點了點頭。");
        call_out("next_spot", 2, me);
        return 1;
    }
    delete_temp(ROUND);
    talk(me, ({ "emote 把兩柄還冒著熱氣的鎚子浸進水箱﹐嗤的一聲白煙直冒。",
                "say 好﹗好﹗這一對鎚子﹐總算沒辜負師父的槌子。" }), "give_reward");
    return 1;
}

// 交出一對撼山鎚；還不會的人另外傳授撼山鎚法（補足到剛好學成），已經會的不再傳授。
void give_reward(object who)
{
    object ob;
    int i;

    if( query_temp(WORKER) != who || lost_worker(who) ) return;
    ob = query_temp(HOLD);
    delete_temp(WORKER);
    delete_temp(HOLD);
    if( objectp(ob) ) destruct(ob);
    for( i = 0; i < 2; i++ ) new(REWARD)->move(who);
    message_vision(CYN "鐵匠把一對撼山鎚交給了$N。\n" NOR, who);
    if( knows_hammer(who) ) {
        talk(who, ({ "say 鎚法你早就會了﹐這對鎚子拿去﹐可別讓它們閒著。" }), 0);
        return;
    }
    if( SKILL_D(QH_SKILL)->valid_learn(who) ) {
        tell_object(who, CYN "鐵匠拿起兩柄鎚子一左一右比劃給你看﹐把撼山鎚法的訣竅仔仔細細地教給了你。\n" NOR);
        // 補足到學成等級（20 級）的門檻，玩家領悟後直接練成。
        who->improve_skill_exact(QH_SKILL,
            who->skill_threshold(QH_SKILL, who->skill_entry_level(QH_SKILL)) - who->query_learn(QH_SKILL));
    }
    talk(who, ({ "say 左鎚點、右鎚落﹐這就是我師父的鎚法﹐你可別糟蹋了。",
                 "say 要是嫌雙鎚麻煩﹐找柄大槌雙手合握也使得﹐只是那又是另一番勁道了。" }), 0);
}
