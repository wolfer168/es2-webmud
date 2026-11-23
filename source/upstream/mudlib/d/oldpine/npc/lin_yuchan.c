// /d/oldpine/npc/lin_yuchan.c — 迷霧森林 NPC：逆靈宮四宮主 靈玉嬋（依老松林設計表）。

#include <npc.h>

inherit F_FIGHTER;


void create()
{
    seteuid(getuid());
    set_name("靈玉嬋", ({ "lin yu-chan", "lin", "yu-chan" }));
    set_race("human");
    set_class("fighter");
    set_level(30);
    set("title", "逆靈宮四宮主");
    set("gender", "female");
    set("age", 18);
    set("long", @LONG
一位膚色白皙的女郎，眉頭深鎖，似乎正在為什麼事情煩心。
LONG
    );
    set_skill("force", 60);
    set_power("A");
    setup();
    carry_object("/d/oldpine/npc/obj/violet_shoes")->wear();
    carry_object("/d/oldpine/npc/obj/violet_cloth")->wear();
    carry_object("/d/oldpine/npc/obj/violet_hairpin")->wear();
    carry_object("/d/oldpine/npc/obj/voliet_jade")->wear();
}
