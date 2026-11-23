/*---
description: 白甌繡過的包包（龍麟袋、太古塵包）共用的題名功能，由 *_bag_plus.c 引入。
design: docs/EMBROIDERY.md 第七節（使用者指示，2026-11-24）
rule: - 玩家身上帶著繡過的包包時可用 set bag name <名稱> 在籤牌上題字；可重複改名、不能取消。
      - 身上有兩個以上繡過的包包時用 set bag 2 name <名稱> 指定第幾個（只數繡過的包包）。
      - 顯示「原名稱 [ 名稱 ] (英文名稱)」；物品的名稱（name）與 ID 不變，放取東西的訊息仍是原名稱。
      - 名稱規則同 name 指令：最多 6 個中文字（12 格），不可換行、顏色碼、$ % |，只能用 Big5 有的字。
      - 家園儲物箱存取時保留名稱（query_store_data／restore_store_data）。
---*/

#include <daemon.h>

#define LABEL_MAX_WIDTH 12      // 最多 12 格：6 個中文字，或 12 個英數字（中文字算 2 格）
#define SIGN_EMPTY  "袋角繡著一方小小的籤牌，可以在上頭題字 (set bag name)。\n"

// 包包原本的描述（由各 plus 檔在 create() 裡記下，題字後接上籤牌那一句）。
string query_base_long() { return query("base_long"); }

// 在籤牌上題字：顯示名稱改為「原名稱 [ 名稱 ]」，name 與 ID 不變。
void set_bag_label(string str)
{
    set("bag_label", str);
    set("short", query("name") + " [ " + str + " ]");
    set("long", query_base_long() + "袋角的籤牌上繡著「" + str + "」幾個字 (set bag name)。\n");
}

void init()
{
    add_action("do_set_label", "set");
}

int do_set_label(string arg)
{
    object me = this_player(), ob;
    string item, label, id, ch;
    int n = 1, count = 0, width = 0;

    if( !arg ) return 0;
    if( sscanf(arg, "%s name %s", item, label) != 2 ) {
        // 只打了「set bag name」沒寫名稱：提示格式。
        if( sscanf(arg, "%s name", item) == 1 && item != "" )
            return notify_fail("指令格式 : set bag name <名稱>\n");
        return 0;
    }
    if( item == "" || label == "" )
        return notify_fail("指令格式 : set bag name <名稱>\n");
    if( sscanf(item, "%s %d", id, n) != 2 ) id = item;
    if( n < 1 ) n = 1;

    // 只數身上繡過的包包：set bag name 是第一個，set bag 2 name 是第二個。
    foreach(object o in all_inventory(me))
        if( o->id(id) && function_exists("set_bag_label", o) && ++count == n ) {
            ob = o;
            break;
        }
    if( !objectp(ob) ) {
        if( !count && !objectp(present(id, me)) )
            return notify_fail("你身上沒有這樣東西。\n");
        if( !count )
            return notify_fail("只有白甌繡過的袋子才有籤牌可以題字。\n");
        return notify_fail("你身上沒有那麼多個繡過的袋子。\n");
    }

    // 名稱只能是一行乾淨的文字：不可換行，不可夾帶顏色碼與控制字元，頭尾不留空白。
    if( label[0] == ' ' || label[<1] == ' ' )
        return notify_fail("名稱的頭尾不能留空白。\n");
    foreach(ch in explode(label, "")) {
        if( strlen(ch) == 1 && (ch[0] < ' ' || ch[0] == 127 || ch == "$" || ch == "%" || ch == "|") )
            return notify_fail("名稱不能換行，也不能夾帶顏色碼或特殊字元。\n");
        width += (strlen(ch) > 1) ? 2 : 1;
    }
    if( width > LABEL_MAX_WIDTH )
        return notify_fail("名稱太長了﹐最多六個中文字。\n");
    if( !BIG5_D->valid_text(label) )
        return notify_fail("名稱裡有些字太罕見了﹐請換成常用的字。\n");

    ob->set_bag_label(label);
    write("你在" + ob->name() + "的籤牌上題了「" + label + "」。\n");
    return 1;
}

/* ---- 家園儲物箱存取（登出照一般規則丟在地上，所以不用 autoload） ------------ */

// 格式："1|名稱"（沒題字時名稱為空）
string query_store_data()
{
    string label = query("bag_label");
    return "1|" + (stringp(label) ? label : "");
}

void restore_store_data(string param)
{
    string label;

    if( !stringp(param) || sscanf(param, "1|%s", label) != 1 || label == "" ) return;
    set_bag_label(label);
}
