#include <npc.h>
inherit F_VILLAGER;
void create()
{
    set_name("小孩", ({ "child", "lee child" }));
    set_race("human"); set_class("commoner"); set_level(1);
    set("age", 5);
    set("long", "一個在村裡跑來跑去的小孩，衣角沾著灰土，像是剛從廣場玩回來。\n");
    set_power("C");
    setup();
    carry_object("/d/npc/obj/tummy_cover")->wear();
}

// MODIFIED: F_VILLAGER 預設的 accept_fight() 一律拒絕（return 0），
// 這裡讓小孩也能被玩家發起 fight。
int accept_fight(object ob)
{
    return 1;
}
