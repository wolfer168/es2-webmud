// /d/qiaoyin/npc/cao_xuanzhi.c — 喬陰縣 NPC：曹玄志（依使用者設計表，2026-10-16）。

#include <npc.h>
inherit F_FIGHTER;

void create()
{
    seteuid(getuid());
    set_name("曹玄志", ({ "cao xuanzhi", "cao", "xuanzhi" }));
    set("title", "喬陰縣府總捕頭");
    set_race("human");
    set_class("fighter");
    set_level(25);
    set("gender", "male");
    set("age", 45);
    set("long", @LONG
喬陰縣總捕頭，維持地方秩序頗有手段，鄰里街坊的安全都仰賴官府照料。最近老松林盜匪橫行，他正苦惱著該如何保護百姓安全。
LONG
    );
    set_power("A");
    setup();
    carry_object("/d/npc/obj/iron_cloth")->wear();
    carry_object("/d/qiaoyin/npc/obj/battle_armor")->wear();
    carry_object("/d/qiaoyin/npc/obj/tiger_helmet")->wear();
}
