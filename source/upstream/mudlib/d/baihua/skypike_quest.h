// /d/baihua/skypike_quest.h — 穹槍訣任務（老王尋妻）共用的記號與小工具。
// 設計與對白見 docs/martial_arts/穹槍訣.md「任務：老王尋妻」。
//
// 玩家身上的記號 SQ_STAGE（用 set，重新上線仍有效）：任務進度，0 還沒開始，見下方 SQ_*。
// 道具（肉塊、信、血靈芝粉）不記取得者：誰取得的都能拿來交（使用者定案，2026-11-21）。
// 每個玩家各自進行，進度存在玩家身上；NPC 同時只演一段，演到一半有人又交東西就不收。

#define SQ_STAGE    "baihua/skypike/stage"
#define SQ_SAT      "baihua/skypike/sat"    // 暫時記號：在老王家坐下聽故事了
#define SQ_TICK     2                       // 一個 tick 的秒數

#define SQ_NONE     0                       // 還沒開始（先坐下聽老王說故事）
#define SQ_HELP     1                       // 答應幫忙，要把肉塊拿給老王看
#define SQ_TO_CHEN  2                       // 老王要玩家去找陳仙人（雪亭鎮私塾的陳維俠）
#define SQ_CHEN     3                       // 陳維俠看過了，再拿肉塊給老王
#define SQ_TO_SIS   4                       // 老王要玩家去五堂鎮問她姊姊
#define SQ_LETTER   5                       // 姊姊寫了信，轉交老王
#define SQ_BONE     6                       // 老王要收遺骨：先交肉塊
#define SQ_POWDER   7                       // 肉塊交了，再交化屍粉
#define SQ_MEDICINE 8                       // 老王回贈血靈芝粉，送去懸崖平台給高玉

#define SQ_MEAT_FILE   "/d/oldpine/obj/meat"
#define SQ_DUST_FILE   "/obj/dust"
#define SQ_LETTER_FILE "/d/baihua/obj/sister_letter"
#define SQ_MED_FILE    "/d/baihua/obj/ling_tzi"
#define SQ_PILL_FILE   "/d/oldpine/obj/dragon_pill"

private int sq_stage(object who) { return who->query(SQ_STAGE); }

// 是這種任務道具嗎？
private int sq_is(object ob, string file) { return base_name(ob) == file; }

// 玩家還在 NPC 同一個房間嗎？
private int sq_here(object npc, object who)
{
    return objectp(who) && objectp(npc) && environment(who) == environment(npc);
}

// 把任務道具交給玩家；玩家已經走開或拿不動，就放在 NPC 所在的房間。
private object sq_give(object npc, object who, string file)
{
    object ob = new(file);

    if( !sq_here(npc, who) || !ob->move(who) ) ob->move(environment(npc));
    return ob;
}

// 演一段：acts 每項是 "say 文字" 或 "emote 文字"，每項隔 SQ_TICK；演完呼叫 done（沒有就不呼叫）。
// 說話與表情都是一行不斷行。NPC 在演的時候 quest_busy 為 1，別的玩家這時交東西就不收。
int quest_busy;

void sq_play(string *acts, int i, string done, object who)
{
    if( i >= sizeof(acts) ) {
        quest_busy = 0;
        if( done ) call_out(done, 0, who);
        return;
    }
    command(acts[i]);
    call_out("sq_play", SQ_TICK, acts, i + 1, done, who);
}

void sq_start(string *acts, string done, object who)
{
    quest_busy = 1;
    call_out("sq_play", SQ_TICK, acts, 0, done, who);
}

void sq_drop(object ob)
{
    if( objectp(ob) ) destruct(ob);
}
