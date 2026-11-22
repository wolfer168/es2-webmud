/*---
description: who command, used to display online players and their information.
author: Annihilator <taedlar@gmail.com>
---*/
#include <ansi.h>

inherit F_CLEAN_UP;

object *all, *target;
string msg;
int i, j;

// 組合選項用：等級分段（0 代表 1～10 級……6 代表 61～70 級）、種族代號、職業代號。
// 同一類條件符合任一個就列出，不同類條件要全部符合（使用者指示，2026-11-23）。
int *lv_opts;
string *race_opts, *class_opts;

// 種族、職業選項對應的程式代號。和尚選項用 -bn（bonze），對應內部職業代號 monk。
mapping race_map = ([
    "-bh": "blackteeth", "-hn": "human",   "-av": "avatar",   "-wn": "woochan",
    "-jo": "jiaojao",    "-yd": "yenhold", "-dl": "dingling", "-rr": "rainner",
    "-aa": "ashura",     "-hs": "headless","-ya": "yaksa",    "-ml": "malik",
]);
mapping class_map = ([
    "-at": "alchemist", "-cr": "commoner", "-fr": "fighter", "-sr": "soldier",
    "-tf": "thief",     "-tt": "taoist",   "-sc": "scholar", "-bn": "monk",
]);

void msg_format(string arg);

// 依「畫面上佔的格數」計算寬度：sprintf 把一個中文字（UTF-8 三個位元組）當成 3 格，
// 但畫面上只佔 2 格，中文字數不同的名字就會對不齊。ANSI 顏色碼不佔格。
private int dwidth(string s)
{
    int k, c, w = 0, n = strlen(s);

    for( k = 0; k < n; k++ ) {
        c = s[k] & 0xff;
        if( c == 27 ) {                         // 跳過 ESC[...m
            while( k < n && (s[k] & 0xff) != 'm' ) k++;
            continue;
        }
        if( c < 0x80 ) w += 1;
        else if( (c & 0xe0) == 0xc0 ) w += 1;   // 兩位元組字元（如拉丁字母）
        else if( (c & 0xf0) == 0xe0 ) w += 2;   // 三位元組字元（中文）
        else if( (c & 0xf8) == 0xf0 ) w += 2;   // 四位元組字元
    }
    return w;
}

private string pad_left(string s, int width)
{
    int d = width - dwidth(s);
    return (d > 0 ? repeat_string(" ", d) : "") + s;
}

private string pad_right(string s, int width)
{
    int d = width - dwidth(s);
    return s + (d > 0 ? repeat_string(" ", d) : "");
}

private string pad_center(string s, int width)
{
    int d = width - dwidth(s);
    if( d <= 0 ) return s;
    return repeat_string(" ", d / 2) + s + repeat_string(" ", d - d / 2);
}

private void
create()
{
  seteuid(getuid());
}

// 判斷一位使用者是否符合目前的組合條件。
private int match_opts(object ob)
{
    if( sizeof(lv_opts) ) {
        if( wizardp(ob) ) return 0;
        if( member_array((ob->query_level()-1)/10, lv_opts) == -1 ) return 0;
    }
    if( sizeof(race_opts) && member_array(ob->query_race(), race_opts) == -1 ) return 0;
    if( sizeof(class_opts) && member_array(ob->query_class(), class_opts) == -1 ) return 0;
    return 1;
}

mixed
main(object me, string arg, int remote)
{
    int center_lv, n;
    string *opts, o;

    target = ({});
    msg = "";
    lv_opts = ({});
    race_opts = ({});
    class_opts = ({});

    /* 先過濾尚未登入完成的使用者，與隱形的上級巫師。
     * 注意在被 rwho_q 呼叫的狀況下，this_player() 為 0。
     */
    if( this_player(1) )
        all = filter(users(), (:
            objectp(environment($1))
            && (!wizardp($1) || wiz_level($2)>wiz_level($1) || $1->visible($2))
        :), this_player(1));
    else
        all = filter(users(), (: objectp(environment($1)) && !wizardp($1) :));

    i = sizeof(all);

    opts = arg ? filter(explode(arg, " "), (: $1 != "" :)) : ({});

    if( !sizeof(opts) ) {
        center_lv = me->query_level();
        while( i-- ) {
            if (all[i]->query("level") - center_lv < 6 &&
                center_lv - all[i]->query("level") < 6 &&
                (!wizardp(all[i]) || all[i]==this_player(1))
            )
                target += ({ all[i] });
        }
        msg_format("1");
    } else if( sizeof(opts) == 1 && member_array(opts[0], ({ "-l", "-w", "-i", "-n" })) != -1 ) {
        // 這四個選項只能單獨使用。
        switch(opts[0]){
        case "-l":
            if( me->is_character() && !wizardp(me) ) {
                write("為了減低系統負荷, 目前只有巫師可以使用 who -l。\n");
                return 1;
            }
            target = all;
            msg_format("5");
            break;
        case "-w":
            target = filter(all, (: wizardp :));
            msg_format("5");
            break;
        case "-i":
            msg_format("41");
            break;
        case "-n":
            msg_format("42");
            break;
        }
    } else {
        // 等級（-1～-7）、種族、職業三類條件可以組合。
        foreach( o in opts ) {
            if( sscanf(o, "-%d", n) == 1 && o == "-" + n && n >= 1 && n <= 7 ) {
                if( member_array(n - 1, lv_opts) == -1 ) lv_opts += ({ n - 1 });
            } else if( race_map[o] ) {
                race_opts += ({ race_map[o] });
            } else if( class_map[o] ) {
                class_opts += ({ class_map[o] });
            } else if( member_array(o, ({ "-l", "-w", "-i", "-n" })) != -1 ) {
                return notify_fail("-l、-w、-i、-n 只能單獨使用﹐請看 help who。\n");
            } else if( sizeof(opts) == 1 && objectp(me) && wizardp(me) && o[0]=='@' ) {
                //RWHO_Q->send_rwho_q(o[1..sizeof(o)], me, 0);
                return notify_fail("遠端查詢功能已關閉。\n");
            } else {
                return notify_fail("指令格式更新﹕請看 help who。\n");
            }
        }
        target = filter(all, (: match_opts($1) :));
        msg_format("1");
    }

    msg = sprintf("◎ %s\n"
        "──────────────────────────────────────────────────────────────────────────────\n"
        "%s──────────────────────────────────────────────────────────────────────────────\n"
        "共列出 %d/%d 位使用者﹐系統負荷﹕%s\n",
        MUD_NAME, msg, sizeof(target), sizeof(all), query_load_average());

    if( me && me->query_stat_current("sen") > 5 )
        me->consume_stat("sen", 5);
    
    if( remote ) return msg;

    me->start_more_if_needed (msg);
    return 1;
}

int
sort_user(object ob1, object ob2)
{
    int ord;

    ord = wiz_level(ob1) - wiz_level(ob2);
    if( ord==0 )
        ord = (int)ob1->query_level() - (int)ob2->query_level();
    return ord;
}

void
msg_format(string arg)
{
    if( !arg || arg=="" )    return;

    j = sizeof(target);
    target = sort_array(target, "sort_user", this_object());

    switch(arg){
    case "1":
    case "5":
    case "50":
        // detail message
        while( j-- ) {
            // <ansi.h> will confuse sprintf's format
            // 中文名字的字尾對齊、英文 ID 的左括號對齊（依畫面格數補空白）。
            if( wizardp(target[j]) )
                msg = sprintf("%s%s【 %s 】%s %s%s\n",
                    msg,
                    BOLD,
                    pad_center(target[j]->rank(), 10),
                    pad_left((target[j]->query("title") ? target[j]->query("title") : "") + (target[j]->query("nickname") ? "「"+ target[j]->query("nickname") +"」" : "") + (target[j]->query("name", 1)), 42),
                    "(" + capitalize(target[j]->query("id")) + ")",
                    NOR
                );
            else
                msg = sprintf("%s【 %2d%s 】%s%s %s\n",
                    msg,
                    target[j]->query_level(),
                    pad_center(target[j]->rank(), 8),
                    pad_right(target[j]->query("title") ? target[j]->query("title") : "", 12),
                    pad_left((target[j]->query("nickname") ? "「"+ target[j]->query("nickname") +"」" : "")
                        + target[j]->query("name", 1), 30),
                    "(" + capitalize(target[j]->query("id")) + ")"
                );
        }
        break;
    case "41":
        // who i, id of all
        target = sort_array(all, "sort_user", this_object());
        j = sizeof(target);
        while( j-- ) {
            msg = sprintf("%s%-13s%s",
                msg,
                capitalize(target[j]->query("id")),
                (( i - j ) % 6 ) ? "" : "\n"
            );
        }
        if( i % 6 )    msg += "\n";
        break;
    case "42":
        // who n, name of all
        target = sort_array(all, "sort_user", this_object());
        j = sizeof(target);
        while( j-- ) {
            // 中文名字依畫面格數補空白對齊（一個中文字佔 2 格）。
            msg = sprintf("%s%s%s",
                msg,
                pad_right(target[j]->query("name", 1), 12) + " ",
                (( i - j ) % 6 ) ? "" : "\n"
            );
        }
        if( i % 6 )    msg += "\n";
        break;
    default:
        msg = "Error at msg_format.\n";
    }
}

int help(object me)
{
    write(@HELP
指令格式 : who [選項]

這個指令可以列出在線上的使用者及其相關資訊。神 > 5 時會損神。

無選項時, 列出與你等級相差 5 級以內之使用者。

等級、種族、職業三類選項可以組合使用, 例如 who -7 -at。
同一類選項符合任一個就列出, 不同類選項要全部符合, 例如
who -6 -7 -at -fr 列出 51 到 70 級、而且是 alchemist 或 fighter
的使用者。沒有加等級選項時, 列出所有等級。
HELP
    );
    write(@HELP

等級選項﹕
-1    列出等級 1 到等級 10 的使用者。
-2    列出等級 11 到等級 20 的使用者。
-3    列出等級 21 到等級 30 的使用者。
-4    列出等級 31 到等級 40 的使用者。
-5    列出等級 41 到等級 50 的使用者。
-6    列出等級 51 到等級 60 的使用者。
-7    列出等級 61 到等級 70 的使用者。
HELP
    );
    write(@HELP

種族選項﹕例如 -hn 列出 race 為 human 之使用者。
bh => blackteeth  hn => human    av => avatar    wn => woochan
jo => jiaojao     yd => yenhold  dl => dingling  rr => rainner
aa => ashura      hs => headless ya => yaksa     ml => malik

職業選項﹕例如 -at 列出 class 為 alchemist 之使用者。
at => alchemist   cr => commoner  fr => fighter  sr => soldier
tf => thief       tt => taoist    sc => scholar  bn => bonze
HELP
    );
    write(@HELP

以下選項只能單獨使用﹕
-w    只列出巫師, 有系統設計上的問題請與巫師溝通。
-i    只列出使用者英文 id。
-n    只列出使用者中文名稱。
-l    列出所有使用者詳細資訊 (巫師專用)。

相關指令﹕finger
HELP
    );

    if( wizardp(me) )
        write("遠端查詢 (who @站名) 目前已關閉, 可用 mudlist 查看連線站。\n");

    return 1;
}
