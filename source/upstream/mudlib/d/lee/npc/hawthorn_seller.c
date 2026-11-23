// /d/lee/npc/hawthorn_seller.c
// NEW（李家村復原版新增角色，非原始 ES2 資料，由專案成員指定人設）

#include <npc.h>
inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("冰糖葫蘆小販", ({ "seller", "hawthorn seller" }));
    set_race("human");
    set_class("commoner");
    set_level(5);
    set("long", @LONG
一名挑著小擔的冰糖葫蘆小販，正在這裡叫賣。
擔子上插滿了一串串裹著糖衣的山楂，村中的孩子們都喜歡來找他買冰糖葫蘆。
LONG
    );
    // merchandise 的數字是庫存份數，不是價錢——價錢是各道具檔自己的 "value"。
    set("merchandise", ([
        "/d/lee/npc/obj/candied_hawthorn" : 20,
        "/d/lee/npc/obj/big_candied_hawthorn" : 10,
    ]));
    set_power("C");
    setup();
}

void init()
{
    ::init();
    add_action("do_vendor_list", "list");
}
