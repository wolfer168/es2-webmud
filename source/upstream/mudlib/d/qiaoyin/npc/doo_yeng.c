// /d/qiaoyin/npc/doo_yeng.c — 喬陰縣 NPC：杜言（依使用者設計表，2026-10-16）。

#include <npc.h>
inherit F_FIGHTER;

void create()
{
    seteuid(getuid());
    set_name("杜言", ({ "doo yeng", "doo", "yeng" }));
    set_race("human");
    set_class("fighter");
    set_level(15);
    set("gender", "male");
    set("age", 24);
    set("long", @LONG
尚未在江湖上出名的武者，不曉得在這裡做什麼。
LONG
    );
    set_power("C");
    setup();
    carry_object("/d/npc/obj/blood_stained_cloth")->wear();
    carry_object("/obj/area/obj/longsword")->wield();
}
