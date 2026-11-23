/* CUSTOM GHOST NPC BASE: 鬼魂類 NPC（魂魄狀態），以人類為基礎。
 *
 * 只有陰陽眼（apply/vision_of_ghost）看得見；一般攻擊會從身上穿透。
 * 說話與移動比照瞎眼老太婆（d/snow/npc/gammer.c），用 chat_chance / chat_msg
 * 隨機觸發：平均約 30 tick 說一句台詞、約 15 tick 移動一次
 * （1 tick = 一次心跳 2 秒）。夜叉可以 devour 吞食。
 *
 * 顏色規則：所有鬼魂一律用暗灰色（HIK）顯示名字、房間中的簡短敘述與台詞，
 * 和玩家死後的鬼魂同色。新的鬼魂只要繼承這個基底就會自動套用。
 */
#include <ansi.h>

inherit NPC;

// NPC 的 chat() 每 tick 有 (chat_chance + 1)% = 10% 的機率行動，再從 chat_msg
// 三項裡隨機選一項：一項說話、兩項移動。平均每 tick 說話 10% x 1/3 = 1/30，
// 移動 10% x 2/3 = 1/15。
#define GHOST_CHAT_CHANCE  9

void ghost_say()
{
    string *msg = query("ghost_chat");

    if( arrayp(msg) && sizeof(msg) )
        say(HIK + msg[random(sizeof(msg))] + NOR);
}

// 名字（移動、動作訊息中的 $N）與房間中的簡短敘述都顯示為暗灰色。
// raw 版本維持原字串，供程式比對使用。
varargs string name(int raw)
{
    string str = ::name(raw);
    return raw ? str : HIK + str + NOR;
}

varargs string short(int raw)
{
    string str = ::short(raw);
    return raw ? str : HIK + str + NOR;
}

// 子類別在 create() 最後呼叫：設定魂魄狀態、說話與移動、精與神。
void setup_ghost(int gin, int sen)
{
    set_race("human");
    set("life_form", "ghost");
    set("attitude", "peaceful");
    set("chat_chance", GHOST_CHAT_CHANCE);
    set("chat_msg", ({
        (: ghost_say :),
        (: random_move :),
        (: random_move :),
    }));
    setup();

    set_stat_maximum("gin", gin);
    set_stat_effective("gin", gin);
    set_stat_current("gin", gin);
    set_stat_maximum("sen", sen);
    set_stat_effective("sen", sen);
    set_stat_current("sen", sen);
}

int accept_fight(object who)
{
    return 0;
}
