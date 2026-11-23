// /d/qiaoyin/npc/smith.c — 喬陰縣 NPC：鐵匠（依使用者設計表，2026-10-16）。

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
    set_name("鐵匠", ({ "smith" }));
    set_race("human");
    set_class("commoner");
    set_level(13);
    set("gender", "male");
    set("age", 40);
    set("long", @LONG
渾身肌肉，右手臂更是健壯異常，平日為左鄰右舍修修工具，偶有興致也會打幾把兵器，賣給來往的江湖人士。
LONG
    );
    set("merchandise", ([
        "/obj/area/obj/rod" : 5,          // 鐵鞭
        "/obj/area/obj/kris" : 5,         // 短刀
        "/obj/area/obj/axe" : 5,          // 斧頭
        "/obj/area/obj/shortsword" : 5,   // 短劍（設計表原寫 obj/example 範例檔，改用正式商品）
        "/obj/area/obj/longsword" : 5,    // 長劍
    ]));
    set("chat_chance", 5);
    set("chat_msg", ({
        "鐵匠將一塊燒紅的鐵塊「嗤」地一聲浸入一旁的水箱中。\n",
        "鐵匠用手中的鐵鎚在鐵砧上用力敲打。\n",
    }));
    set_power("C");
    setup();
    carry_object("/d/npc/obj/smock")->wear();
}
