#include <npc.h>
inherit F_VILLAGER;

void create()
{
    set_name("李嘯天", ({ "lee xiao tian", "li xiao tian", "manager lee", "lee", "li", "xiao", "tian" }));
    set_race("human");
    set_class("fighter");
    set_level(20);
    set("age", 40);
    set("long", "李員外家的二總管為人精明，年少時好舞刀弄槍，被派任當鋪掌櫃之後，諸事都處理得緊緊有條。\n");
    set("chat_chance", 1);
    set("chat_msg", ({ "李嘯天低頭翻著帳簿，偶爾撥動算盤珠。\n" }));
    set_power("B");
    setup();
    carry_object("/d/npc/obj/yellow_jade_ring")->wear();
    carry_object("/d/lee/npc/obj/willow_blade")->wield();
}
