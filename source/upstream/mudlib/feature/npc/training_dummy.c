// /feature/npc/training_dummy.c — 練武假人底本（使用者指示，2026-11-02）。
//
// 振武軍營假人、冷梅莊假人、百花村石獅子等練武用的死物都繼承這份。
// 假人是「死物的人物」：外表是人物（才能被比劃、攻擊），但生物才有的反應全部關掉。
//   - 不會反擊、不閃躲、不招架，必定命中（combatd 依 training_dummy 跳過防禦）。
//   - 打不壞、不會死，精氣神不會被扣。
//   - 每一擊都算命中有傷害，所以靠命中觸發的特效照樣按機率發動。
//   - 不會中毒、流血或有任何狀態（feature/char/condition.c 擋下）。
//   - 不能偷竊、針灸（cmds/std/steal.c、acupuncture.c 擋下）；
//     背刺只能練到粗淺的程度（cmds/std/backstab.c）。
// 設計文件：docs/TRAINING_DUMMY.md
//
// 用法：
//     inherit "/feature/npc/training_dummy";
//     void create() { set_name(...); set("long", ...); setup(); }
// 假人檔不要再 #include <npc.h>：底本已經繼承了 NPC 的標準物件。
// 底本的 setup() 會補上種族、職業、等級與 training_dummy 標記。

#include <npc.h>

inherit F_VILLAGER;

void setup()
{
    if( !query_race() ) set_race("human");
    if( !query_class() ) set_class("commoner");
    if( !query_level() ) set_level(20);
    set("civilized", 1);
    set("training_dummy", 1);
    ::setup();
}

int accept_fight(object who) { return 1; }

/* 假人是死物：被 kill 時不會喊救命。 */
void accept_kill(object ob) { }

/* 不還手。 */
void fight_ob(object ob) { }
void kill_ob(object ob) { }

/* 不閃躲、不招架、不減傷。 */
int defend(int ability, int strength, object from) { return 0; }
int absorb(int ability, int strength, object from) { return 0; }
int resist_damage(int damage, object from_ob) { return 0; }

/* 傳回正數讓命中照樣算數（練功點數、特效觸發），但不扣任何數值。 */
varargs int receive_damage(int damage, object from, object attacker)
{
    if( damage < 1 ) damage = 1;
    return damage;
}

/* 精氣神不會被扣（針法、吸取類特效等）。 */
varargs int consume_stat(string type, int damage, object who) { return 0; }
varargs int damage_stat(string type, int damage, object who) { return 0; }

void die() { }
