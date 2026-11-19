// devourlog.c - 查詢夜叉吞魂紀錄（使用者指示，2026-11-15；只給 arch 以上使用）
// 紀錄由 /daemon/race/yaksa/devour.c 寫入，只記玩家；規則見 docs/CUSTOM_RACE_A_H.md。

#include <command.h>

inherit F_CLEAN_UP;

#define DEVOUR_DATA "/data/daemon/yaksa_devour.dat"
#define RECORD_KEY  "yaksa/devour_records"
#define LIST_MAX    100

int help(object me);

private void create() { seteuid(getuid()); }

// 資料檔可能超過一次讀檔的上限（MaxReadFileSize），大檔分段讀。
// 注意：要求的行數超過檔案剩下的行數時，read_file() 會傳回 0，所以最後不足一段的部分改成一行一行讀。
#define CHUNK     100
#define SMALL_FILE 150000

private mapping *load_all() {
    string data;
    mapping *recs = ({});
    mixed rec;
    int line = 1, size = file_size(DEVOUR_DATA);

    if (size <= 0) return recs;
    if (size <= SMALL_FILE) {
        data = read_file(DEVOUR_DATA);
        if (data)
            foreach (string str in explode(data, "\n") - ({ "" }))
                if (!catch(rec = restore_variable(str)) && mapp(rec))
                    recs += ({ rec });
        return recs;
    }
    while (data = read_file(DEVOUR_DATA, line, CHUNK)) {
        foreach (string str in explode(data, "\n") - ({ "" }))
            if (!catch(rec = restore_variable(str)) && mapp(rec))
                recs += ({ rec });
        line += CHUNK;
    }
    while (data = read_file(DEVOUR_DATA, line++, 1))
        if (!catch(rec = restore_variable(replace_string(data, "\n", ""))) && mapp(rec))
            recs += ({ rec });
    return recs;
}

private string gain_of(mapping rec) {
    if (rec["result"] == "ok")
        return sprintf("%s 精+%d 氣+%d 神+%d", rec["big"] ? "大幅" : "小幅",
            rec["gin"], rec["kee"], rec["sen"]);
    return rec["result"] == "ghost_low" ? "鬼魂未達門檻" : "夜叉未達門檻";
}

// 一筆一行的摘要。
private string brief(mapping rec) {
    return sprintf("#%-4d %s  %s 吞 %s  第%d魂/%s  %s\n",
        rec["serial"], ctime(rec["time"])[4..15], rec["yaksa"], rec["victim"],
        rec["soul_no"], rec["valid_no"] ? "有效第" + rec["valid_no"] + "次" : "不計數",
        gain_of(rec));
}

// 單筆的完整內容。
private string detail(mapping rec) {
    return sprintf(
        "吞魂紀錄 #%d\n"
        "  時間：%s\n"
        "  夜叉：%s（%s）\n"
        "  夜叉 IP：%s\n"
        "  第幾個魂：第 %d 個玩家魂，%s；吞這個帳號第 %d 次\n"
        "  被吞：%s（%s）\n"
        "  被吞 IP：%s\n"
        "  被吞角色：%s\n"
        "  死因：%s\n"
        "  死亡時間、地點：%s，%s\n"
        "  門檻：鬼魂精（最大值）%d／夜叉精（最大值）%d／門檻 %d\n"
        "  加成：%s\n"
        "  吞後夜叉最大值：精 %d、氣 %d、神 %d\n"
        "  吞食地點：%s\n",
        rec["serial"], ctime(rec["time"]),
        rec["yaksa"], rec["yaksa_class"], rec["yaksa_ip"],
        rec["soul_no"], rec["valid_no"] ? "計入第 " + rec["valid_no"] + " 次有效吞魂" : "不計數",
        rec["same_victim"],
        rec["victim"], rec["victim_class"], rec["victim_ip"], rec["victim_age"],
        rec["killer"],
        rec["death_time"] ? ctime(rec["death_time"]) : "不明", rec["death_room"],
        rec["ghost_gin"], rec["own_gin"], rec["need"],
        gain_of(rec),
        rec["max_gin"], rec["max_kee"], rec["max_sen"],
        rec["room"]);
}

private int show_list(mapping *recs, string title) {
    string out;
    int n = sizeof(recs);

    if (!n) {
        write(title + "：沒有紀錄。\n");
        return 1;
    }
    out = sprintf("%s：共 %d 筆%s\n", title, n,
        n > LIST_MAX ? "，只列出最近 " + LIST_MAX + " 筆" : "");
    if (n > LIST_MAX) recs = recs[<LIST_MAX..];
    foreach (mapping rec in recs) out += brief(rec);
    out += "看單筆的完整內容：devourlog -d <編號>\n";
    this_player()->start_more(out);
    return 1;
}

int main(object me, string arg) {
    mapping *recs;
    object ob;
    string id;
    int serial;

    // 只給 arch 以上使用（使用者指示，2026-11-15）：紀錄裡有玩家的 IP。
    SECURED_ARCH_COMMAND;
    seteuid(getuid());
    if (!arg || arg == "") return show_list(load_all(), "全部吞魂紀錄");
    if (arg == "-h" || arg == "help") return help(me);

    if (sscanf(arg, "-d %d", serial) == 1) {
        foreach (mapping rec in load_all())
            if (rec["serial"] == serial) {
                me->start_more(detail(rec));
                return 1;
            }
        return notify_fail("找不到編號 " + serial + " 的紀錄。\n");
    }
    if (sscanf(arg, "-v %s", id) == 1)
        return show_list(filter(load_all(), (: $1["victim_id"] == $2 :), id),
            "被吞者 " + id + " 的紀錄");
    if (sscanf(arg, "-p %s", id) == 1) {
        // 夜叉角色身上的紀錄（最多 200 筆）：紀錄檔被清掉時用。角色要在線上。
        if (!objectp(ob = find_player(id)))
            return notify_fail("找不到在線上的 " + id + "。\n");
        recs = ob->query(RECORD_KEY);
        return show_list(arrayp(recs) ? recs : ({}), id + " 身上的吞魂紀錄");
    }
    if (arg[0] == '-') return help(me);
    return show_list(filter(load_all(), (: $1["yaksa_id"] == $2 :), arg),
        "夜叉 " + arg + " 的紀錄");
}

int help(object me) {
    write(@HELP
指令格式：devourlog                 列出全部吞魂紀錄（最近 100 筆）
          devourlog <夜叉代號>      只看某一隻夜叉吞的
          devourlog -v <玩家代號>   只看某個玩家被吞的紀錄
          devourlog -d <編號>       看單筆的完整內容
          devourlog -p <夜叉代號>   看在線夜叉身上存的紀錄

查詢夜叉吞噬玩家鬼魂的紀錄（鬼魂 NPC 不記）。每筆有時間、第幾個
魂、吞食對象、增加的精氣神、雙方 IP、死因、門檻與吞食地點。
紀錄檔：/data/daemon/yaksa_devour.dat（另有給人看的 .log）。
HELP);
    return 1;
}
