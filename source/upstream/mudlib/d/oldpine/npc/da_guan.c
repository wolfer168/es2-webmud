// /d/oldpine/npc/da_guan.c — 老松林 NPC：彤雲寺住持 大觀和尚（依老松林設計表）。

#include <npc.h>

inherit F_FIGHTER;
inherit F_VENDOR;

void init()
{
    ::init();
    add_action("do_vendor_list", "list");
}

void create()
{
    seteuid(getuid());
    set_name("大觀和尚", ({ "abbot da-gaun", "abbot", "da-gaun", "da gaun" }));
    set_race("human");
    set_class("monk");
    set_level(30);
    set("title", "彤雲寺住持");
    set("age", 60);
    set("long", @LONG
大觀和尚是彤雲寺的住持，到南方雲遊七年，幾天前才剛回來。
LONG
    );
    // 販售佛經（使用者指定，2026-10-16）。數字是庫存份數。
    set("merchandise", ([
        "/obj/books/book_of_buddhology" : 10,      // 【般若波羅密多心經】
        "/obj/books/book_of_life" : 10,            // 【無量壽經】
        "/obj/books/book_of_mercy" : 10,           // 【大悲咒】
        "/obj/books/book_of_afterlife" : 10,       // 【往生經】
    ]));
    set_power("A");
    setup();
    carry_object("/d/oldpine/npc/obj/wither_zenstaff")->wield();
    carry_object("/d/oldpine/npc/obj/animitta_kasaya")->wear();
    carry_object("/d/npc/obj/psakaml")->wear();
}
