#include <npc.h>
inherit F_SOLDIER;
void create()
{
    set_name("小兵", ({"soldier","小兵"}));
    set_race("human");
    set_class("soldier"); set_level(5);
    set_skill("twohanded pike", 20);
    set_skill("dodge", 10);
    set_skill("parry", 10);
    set("long", "軍營裡的新兵，通常負責簡單的體力工作。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "小兵瞪了你一眼，喝道：看甚麼！軍營門口不可逗留！\n",
    }));
    set_power("B");
    setup();
    carry_object("/d/npc/obj/clothboot")->wear();
    carry_object("/d/npc/obj/helmet")->wear();
    carry_object("/d/npc/obj/leather_armor")->wear();
    carry_object("/custom/zhenwu/obj/short_pike")->wield();
}
