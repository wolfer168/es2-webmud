/* CUSTOM RACE COMMAND: yaksa devour */
#include <ansi.h>
inherit F_CLEAN_UP;

#define TICK_SECONDS 2

// 吞魂封印開關：2026-11-03 封印，2026-11-04 改版後重新開放（使用者指示）。
// 要再封印時把 DEVOUR_SEALED 改成 1，再 update 本檔即可。
#define DEVOUR_SEALED 0

private void create() { seteuid(getuid()); }

// 吞食期間以 call_out 每 tick 吞一口，保持載入。
int clean_up() { return 1; }

private int rnd(int n) { return n > 0 ? random(n) : 0; }

// 同一個鬼魂一次只能被一隻夜叉吞（使用者指示，2026-11-15）：鬼魂身上記著抓住它的夜叉。
#define HOLDER_KEY "yaksa_devour_by"
// 已被吞完、等著魂飛魄散的鬼魂，任何夜叉都不能再吞。
#define DONE_KEY   "yaksa_devoured"

private void stop_devour(object me) {
    object victim;

    if (!objectp(me)) return;
    victim = me->query_temp("yaksa_devour/victim");
    if (objectp(victim) && victim->query_temp(HOLDER_KEY) == me)
        victim->delete_temp(HOLDER_KEY);
    me->delete_temp("yaksa_devour");
}

// 鬼魂目前被哪一隻夜叉抓住（那隻夜叉確實還在吞它才算）。
private object holder_of(object victim) {
    object holder = victim->query_temp(HOLDER_KEY);

    if (objectp(holder) && holder->query_temp("yaksa_devour/victim") == victim)
        return holder;
    return 0;
}

// 永久增加精氣神最大值，並同時補上目前值，讓增加的部分立即可用。
private void grow(object me, string stat, int n) {
    if (n < 1) return;
    me->advance_stat(stat, n);
    me->heal_stat(stat, n);
    me->supplement_stat(stat, n);
}

// 有效吞魂次數（使用者指示，2026-11-04 歸零）：只有達到門檻的吞魂才計數。
// 舊規則的次數 yaksa/devoured_players 不再使用。
#define COUNT_KEY "yaksa/devour_count"
// 大幅增加的次數（使用者指示，2026-11-19）：不加目標下指令時給夜叉自己看。
#define BIG_KEY "yaksa/devour_big"

// 吞魂紀錄（使用者指示，2026-11-04；2026-11-15 擴充）。本檔的身分（Mudlib）不能寫 /log，
// 系統權限只開放 /data/daemon 給 Mudlib，所以紀錄放在這裡。只記玩家，不記鬼魂 NPC。
//   DEVOUR_LOG  給人看的紀錄，每筆一段。
//   DEVOUR_DATA 給巫師指令 devourlog 查詢的資料，每筆一行（save_variable 格式）。
// 另外每隻夜叉身上存一份自己的紀錄（RECORD_KEY，最多 RECORD_MAX 筆），紀錄檔被清掉也查得到。
#define DEVOUR_LOG "/data/daemon/yaksa_devour.log"
#define DEVOUR_DATA "/data/daemon/yaksa_devour.dat"
#define RECORD_KEY  "yaksa/devour_records"
#define RECORD_MAX  200
// 吞過的玩家魂總數（不論有沒有達門檻，2026-11-15 起算）與每個帳號被這隻夜叉吞過的次數。
#define SOUL_KEY    "yaksa/devour_souls"
#define VICTIM_KEY  "yaksa/devour_victims"

private void devour_log(string text) {
    assure_file(DEVOUR_LOG);
    write_file(DEVOUR_LOG, text);
}

// 紀錄編號：另存一個小檔累加（資料檔可能很大，一次讀不完）。
#define SERIAL_FILE "/data/daemon/yaksa_devour.serial"

private int next_serial() {
    int n = to_int(read_file(SERIAL_FILE) || "0") + 1;

    write_file(SERIAL_FILE, n + "", 1);
    return n;
}

// 真實 IP 與同一戶代表（玩家都從網頁橋接程式連入，遊戲直接看到的位址是本機）。
private string ip_of(object ob) {
    string ip, group;

    ip = REALIP_D->query_ip(ob);
    if (!ip) ip = ob->query_temp("realip");
    if (!ip) ip = interactive(ob) ? query_ip_number(ob) : "斷線中";
    group = REALIP_D->query_body_group(ob);
    return group && group != ip ? ip + "（同一戶：" + group + "）" : ip;
}

private string room_of(object ob) {
    object env = environment(ob);

    if (!env) return "不明";
    return sprintf("%s(%s)", env->query("short") || "?", base_name(env));
}

private string class_of(object ob) {
    string cls = ob->query_class();
    mapping names = ([ "commoner": "平民", "fighter": "武者", "taoist": "道士",
        "alchemist": "方士", "soldier": "軍人", "scholar": "書生", "monk": "和尚",
        "thief": "盜賊" ]);

    return sprintf("%s／%s／%d級", to_chinese(ob->query_race()),
        names[cls] || cls || "不明", ob->query_level());
}

// 被吞角色的年紀：創角時間（這個角色）與帳號累計上線時間（魂飛魄散重新創角也不歸零）。
private string age_of(object ob) {
    int birth = ob->query("birthday"), aged;
    object link = ob->link();
    string online;

    if (link) {
        link->update_age();
        aged = link->query("time_aged");
        online = sprintf("帳號累計上線 %d 小時 %d 分", aged / 3600, aged % 3600 / 60);
    } else online = "帳號上線時間不明（斷線中）";
    if (birth <= 0) return "創角時間不明，" + online;
    return sprintf("創角於 %s（約 %d 天前），%s", ctime(birth), (time() - birth) / 86400, online);
}

private void write_record(object me, mapping rec) {
    mixed *recs;

    rec["serial"] = next_serial();
    assure_file(DEVOUR_DATA);
    write_file(DEVOUR_DATA, save_variable(rec) + "\n");

    recs = me->query(RECORD_KEY);
    if (!arrayp(recs)) recs = ({});
    recs += ({ rec });
    if (sizeof(recs) > RECORD_MAX) recs = recs[<RECORD_MAX..];
    me->set(RECORD_KEY, recs);

    devour_log(sprintf(
        "#%d [%s] 夜叉 %s 吞噬 %s\n"
        "  第幾個魂：第 %d 個玩家魂，%s；吞這個帳號第 %d 次\n"
        "  加成：%s\n"
        "  門檻：鬼魂精（最大值）%d／夜叉精（最大值）%d／門檻 %d\n"
        "  吞後夜叉最大值：精 %d、氣 %d、神 %d\n"
        "  夜叉：%s，IP %s\n"
        "  被吞：%s，IP %s，%s\n"
        "  死因：%s，死於 %s（%s）\n"
        "  地點：%s\n",
        rec["serial"], ctime(rec["time"]), rec["yaksa"], rec["victim"],
        rec["soul_no"], rec["valid_no"] ? "計入第 " + rec["valid_no"] + " 次有效吞魂" : "不計數",
        rec["same_victim"],
        rec["result"] == "ok"
            ? sprintf("%s，精 +%d、氣 +%d、神 +%d", rec["big"] ? "大幅" : "小幅",
                rec["gin"], rec["kee"], rec["sen"])
            : rec["result"] == "ghost_low" ? "鬼魂未達門檻，不加成" : "夜叉自身未達門檻，不加成",
        rec["ghost_gin"], rec["own_gin"], rec["need"],
        rec["max_gin"], rec["max_kee"], rec["max_sen"],
        rec["yaksa_class"], rec["yaksa_ip"],
        rec["victim_class"], rec["victim_ip"], rec["victim_age"],
        rec["killer"], rec["death_room"], rec["death_time"] ? ctime(rec["death_time"]) : "不明",
        rec["room"]));
}

// 門檻（使用者指示，2026-11-04）：鬼魂的精（開始吞時的目前值）與夜叉自己的精
// （最大值）都要達到門檻，才加精氣神、才計數。第 1～10 隻 500，第 11 隻起每隻多 50（550、600……）。
// 夜叉族的鬼魂門檻減半：250，第 11 隻起每隻多 25（275、300……）。
int devour_threshold(int count, int yaksa_ghost) {
    int extra = count >= 10 ? count - 9 : 0;
    return yaksa_ghost ? 250 + 25 * extra : 500 + 50 * extra;
}

private string who(object ob) {
    return sprintf("%s(%s)", ob->name(1), ob->query("id"));
}

// 吞完玩家鬼魂：達到門檻才依原始公式給予永久加成並計數；沒有反噬。
// 鬼魂的精以被吞角色的精最大值計算（使用者指示，2026-11-15），被咬過、流失多少都不影響。
private void reward_player(object me, object victim, int ghost_gin) {
    int count, big, gin, kee, sen, yaksa_ghost, need, raw_gin, own_gin;
    string result;
    mapping death, rec;

    raw_gin = ghost_gin;
    // 夜叉自己的精（最大值）也要達到同一個門檻（使用者指示，2026-11-04）。
    own_gin = me->query_stat_maximum("gin");

    count = me->query(COUNT_KEY);
    yaksa_ghost = victim->query_race() == "yaksa";
    need = devour_threshold(count, yaksa_ghost);

    // 第幾個玩家魂（不論有沒有達門檻都算）、吞這個帳號第幾次。
    me->add(SOUL_KEY, 1);
    me->add(VICTIM_KEY + "/" + victim->query("id"), 1);

    if (ghost_gin < need || own_gin < need) {
        tell_object(me, HIK + (ghost_gin < need
            ? "這縷魂魄太過稀薄，沒能為你增添半分力量。\n"
            : "你的根基尚淺，化不開這縷魂魄的力量，沒能增添半分。\n") + NOR);
        result = ghost_gin < need ? "ghost_low" : "self_low";
    } else {
        me->add(COUNT_KEY, 1);
        // 夜叉族的鬼魂，精以兩倍計算（門檻比的是加倍前的精）。
        if (yaksa_ghost) ghost_gin *= 2;
        // 前 10 次必定大幅增加；之後機率 = 10 / (10 + random(吞食次數))。
        big = count < 10 || random(10 + rnd(count)) < 10;
        if (big) {
            me->add(BIG_KEY, 1);
            gin = 1 + ghost_gin / 40;
            kee = 1 + rnd(ghost_gin / 40);
            sen = 1 + rnd(ghost_gin / 80);
        } else {
            gin = 1 + random(2);
            kee = random(2);
            sen = 0;
        }
        grow(me, "gin", gin);
        grow(me, "kee", kee);
        grow(me, "sen", sen);
        tell_object(me, HIG "你的精增加了 " + gin + " 點"
            + (kee ? "、氣增加了 " + kee + " 點" : "")
            + (sen ? "、神增加了 " + sen + " 點" : "") + "！\n" NOR);
        result = "ok";
    }

    death = victim->query("last_death");
    if (!mapp(death)) death = ([]);
    rec = ([
        "time":         time(),
        "yaksa_id":     me->query("id"),
        "yaksa":        who(me),
        "yaksa_class":  class_of(me),
        "yaksa_ip":     ip_of(me),
        "soul_no":      me->query(SOUL_KEY),
        "valid_no":     result == "ok" ? count + 1 : 0,
        "victim_id":    victim->query("id"),
        "victim":       who(victim),
        "victim_class": class_of(victim),
        "victim_ip":    ip_of(victim),
        "victim_age":   age_of(victim),
        "same_victim":  me->query(VICTIM_KEY + "/" + victim->query("id")),
        "killer":       death["killer"] || "不明",
        "death_time":   death["time"],
        "death_room":   death["room"] || "不明",
        "ghost_gin":    raw_gin,
        "own_gin":      own_gin,
        "need":         need,
        "result":       result,
        "big":          result == "ok" ? big : 0,
        "gin":          gin,
        "kee":          kee,
        "sen":          sen,
        "max_gin":      me->query_stat_maximum("gin"),
        "max_kee":      me->query_stat_maximum("kee"),
        "max_sen":      me->query_stat_maximum("sen"),
        "room":         room_of(me),
    ]);
    write_record(me, rec);
}

private void finish(object me, object victim, int total) {
    int ghost_gin;

    message_vision(HIR "$N張口一吸，將$n最後一縷魂魄吞進肚裡！\n" NOR, me, victim);
    ghost_gin = me->query_temp("yaksa_devour/ghost_gin");
    // 吞完就做記號：對方要等自己的下一次心跳才魂飛魄散，這段時間誰都不能再吞。
    victim->set_temp(DONE_KEY, 1);

    if (userp(victim)) {
        reward_player(me, victim, ghost_gin);
        stop_devour(me);
        // 不在這裡直接 die() + make_mist()：魂飛魄散後的選種族畫面與輸入，
        // 會綁在「目前下指令的人」身上，在這裡就是夜叉，結果變成夜叉看到選種族、
        // 被吞的玩家什麼都沒看到。改為耗盡對方的形體（HP），讓對方在自己的心跳裡
        // 走鬼魂再死一次的正常流程（die() → make_mist()），畫面才會出現在對方身上。
        victim->consume_stat("HP", victim->query_stat("HP") + 1, me);
        return;
    }
    stop_devour(me);

    // 鬼魂類 NPC：吞多少補多少精、神（目前值與受損的最大值）。
    me->heal_stat("gin", total);
    me->supplement_stat("gin", total);
    me->heal_stat("sen", total);
    me->supplement_stat("sen", total);
    tell_object(me, HIG "吞下的鬼氣補回了你的精神。\n" NOR);
    destruct(victim);
}

void devour_tick(object me, object victim, int serial) {
    int bite, left, total;

    if (!objectp(me) || me->query_temp("yaksa_devour/serial") != serial) return;
    if (!objectp(victim) || environment(victim) != environment(me)
    ||  victim->query("life_form") != "ghost"
    ||  victim->query_temp(DONE_KEY) || victim->query_temp(HOLDER_KEY) != me
    ||  !living(me) || me->is_fighting() || me->query("life_form") == "ghost") {
        stop_devour(me);
        tell_object(me, "你停止了吞食。\n");
        return;
    }

    // 每口吞食量 = 膽識 + 機敏 + random(自己的精)/10，從鬼魂的精扣除。
    bite = me->query_attr("cor") + me->query_attr("dex") + rnd(me->query_stat("gin")) / 10;
    left = victim->query_stat("gin");
    if (bite > left) bite = left;
    total = me->query_temp("yaksa_devour/total") + bite;
    me->set_temp("yaksa_devour/total", total);

    if (left - bite <= 0) {
        victim->set_stat_current("gin", 0);
        finish(me, victim, total);
        return;
    }
    victim->set_stat_current("gin", left - bite);
    message_vision(HIM "$N大口吞食著$n的魂魄，$n的身形越來越淡了....\n" NOR, me, victim);

    // 吞食期間夜叉無法行動。鬼魂 NPC 也無法行動；玩家的鬼魂可以走開，
    // 離開房間就中斷吞食。
    me->start_busy(1);
    if (!userp(victim)) victim->start_busy(1);
    call_out("devour_tick", TICK_SECONDS, me, victim, serial);
}

// 大幅增加的次數。這項計數是 2026-11-19 才加的：之前吞的，前 10 次有效吞魂一定是大幅，
// 照有效次數補上（最多 10）；第 11 次以後只能從身上的吞魂紀錄（2026-11-15 起）補。
int query_big_count(object me) {
    int n, count;
    mixed recs;

    if (!undefinedp(me->query(BIG_KEY))) return me->query(BIG_KEY);
    count = me->query(COUNT_KEY);
    n = count < 10 ? count : 10;
    recs = me->query(RECORD_KEY);
    if (arrayp(recs))
        foreach (mixed rec in recs)
            if (mapp(rec) && rec["big"] && rec["valid_no"] > 10) n++;
    me->set(BIG_KEY, n);
    return n;
}

// 不加目標：查看自己吞下的魂魄中，有幾縷令自己功力大進（只算玩家的魂魄）。
private int show_count(object me) {
    int n = query_big_count(me);

    if (!n) write("你至今還不曾吞下足以令你功力大進的魂魄。\n");
    else write("你至今吞噬的魂魄之中，共有" + chinese_number(n) + "縷令你功力大進。\n");
    return 1;
}

int main(object me, string arg) {
    object victim;
    int serial;

    if (me->query_race() != "yaksa") return notify_fail("你不是夜叉，無法吞食鬼魂。\n");
    if (!arg || arg == "") return show_count(me);
    if (DEVOUR_SEALED)
        return notify_fail("你體內的噬魂凶性已被封住，再也吞不下任何魂魄。\n");
    if (me->query("life_form") == "ghost") return notify_fail("你自己已經是鬼魂了。\n");
    if (me->query_temp("yaksa_devour")) return notify_fail("你正在吞食鬼魂。\n");
    if (me->is_busy()) return notify_fail("你正忙著。\n");
    if (me->is_fighting()) return notify_fail("戰鬥中無法吞食鬼魂。\n");
    if (!arg || !objectp(victim = present(arg, environment(me)))
    ||  !victim->is_character() || victim == me || !victim->visible(me))
        return notify_fail("你要吞食誰？\n");
    if (victim->query("life_form") != "ghost") return notify_fail("你只能吞食鬼魂。\n");
    if (wizardp(victim)) return notify_fail("你無法吞食巫師。\n");
    if (environment(me)->query("no_fight")) return notify_fail("這裡不能吞食鬼魂。\n");
    if (victim->query_temp(DONE_KEY))
        return notify_fail("這縷魂魄已被吞噬殆盡，正在消散。\n");
    if (holder_of(victim))
        return notify_fail("這縷魂魄已被其他夜叉攫住了。\n");

    serial = time() + random(100000);
    // 鬼魂的精：玩家以精的最大值計算（使用者指示，2026-11-15）；鬼魂 NPC 不加成，不影響。
    me->set_temp("yaksa_devour", ([ "serial": serial, "total": 0, "victim": victim,
        "ghost_gin": victim->query_stat_maximum("gin") ]));
    victim->set_temp(HOLDER_KEY, me);
    message_vision(HIR "$N張開血盆大口，一把抓住$n，開始吞食$n的魂魄！\n" NOR, me, victim);
    tell_object(victim, HIR "你被夜叉抓住了，快逃離這裡！\n" NOR);
    // 下指令後先等 2 tick 才吞第一口（使用者指示，2026-11-04），讓鬼魂有時間逃走。
    me->start_busy(2);
    call_out("devour_tick", TICK_SECONDS * 2, me, victim, serial);
    return 1;
}

int help(object me) {
    // 完整規則見 docs/CUSTOM_RACE_A_H.md（@HELP 區塊不可超過 1024 位元組）。
    write(@HELP
指令格式：devour <鬼魂>
          devour          查看吞下的魂魄中有幾縷令你功力大進

夜叉可以吞食鬼魂 NPC 或死去玩家的鬼魂：
- 抓住鬼魂後要稍待片刻才開始吞食，鬼魂可以趁機逃走。
- 吞鬼魂 NPC：鬼魂被吃掉，吞多少補多少精、神。
- 吞玩家鬼魂：對方魂飛魄散，須重新創造角色。魂魄夠凝實、自身
  根基也夠深厚，才能永久增加精氣神；吞得越多，要求越高。
HELP);
    return 1;
}
