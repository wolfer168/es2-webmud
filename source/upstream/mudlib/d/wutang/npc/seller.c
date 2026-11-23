// /d/wutang/npc/seller.c — 五堂鎮 NPC：賣餅大叔（依五堂鎮設計表）。

#include <npc.h>
inherit F_VILLAGER;
inherit F_VENDOR;

void init()
{
    ::init();
    add_action("do_vendor_list", "list");
}

void create()
{
    seteuid(getuid());
    set_name("賣餅大叔", ({ "seller", "pie seller" }));
    set_race("human");
    set_class("commoner");
    set_level(1);
    set("age", 40);
    set("long", @LONG
長年在五堂鎮賣餅，與街訪都相當熟識。你可以用 list 看他賣些什麼，用 buy 購買。
LONG
    );
    set_skill("unarmed", 2);
    set_skill("dodge", 2);
    set_skill("parry", 2);
    // 約 5～7 tick 說一句（每 tick 16% 機率）。
    set("chat_chance", 15);
    set("chat_msg", ({
        "賣餅大叔掀開蒸籠，熱氣直冒：「熱騰騰的餡餅喔！剛出爐的餡餅喔！」\n",
        "賣餅大叔笑著跟路過的鎮民打招呼：「王大娘，今天要不要帶兩個餅回去給孫子吃啊？」\n",
    }));
    // merchandise 的數字是庫存份數，價錢是各物品自己的 value。
    set("merchandise", ([
        "/d/wutang/npc/obj/pie" : 20,
    ]));
    set_power("C");
    setup();
}
