#include <npc.h>
inherit F_VILLAGER;
void create()
{
    set_name("守衛", ({ "guard", "lee guard" }));
    set_race("human"); set_class("fighter"); set_level(15);
    set_skill("staff", 50);
    set_skill("parry", 20);
    set_skill("dodge", 20);
    set("age", 30);
    set("long", "一名負責巡看李家村出入口的守衛，穿著便於行動的短裝，目光時常警覺地掃視著來往的行人。\n");
    set_power("C");
    setup();
    carry_object("/d/lee/npc/obj/brow_staff")->wield();
    carry_object("/d/npc/obj/hemp_cloth")->wear();
    carry_object("/d/lee/npc/obj/hemp_boots")->wear();
}

// MODIFIED: F_VILLAGER's default accept_fight() always refuses (return 0),
// which is right for ordinary villagers but wrong for a guard. This override
// always accepts, and — unlike F_FIGHTER's accept_fight() — does not decline
// just because "kee" isn't at full, so the guard keeps fighting even while
// not at 100% state.
int accept_fight(object ob)
{
    do_chat( name() + "喝道：大膽！竟敢在此滋事！\n");
    return 1;
}
