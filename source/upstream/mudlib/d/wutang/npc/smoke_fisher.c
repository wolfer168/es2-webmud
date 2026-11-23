// /d/wutang/npc/smoke_fisher.c — 五堂鎮 NPC：煙波釣叟（依五堂鎮設計表）。

#include <npc.h>
inherit F_FIGHTER;

void create()
{
    seteuid(getuid());
    set_name("煙波釣叟", ({ "fisher", "smoke fisher" }));
    set_race("human");
    set_class("fighter");
    set_level(40);
    set("age", 70);
    set("long", @LONG
看起來在這裡但感覺不到他在這裡，只見一翁一竿在草船上坐著，彷彿時間就這樣停止了。
LONG
    );
    set_skill("unarmed", 100);
    set_skill("dodge", 100);
    set_skill("parry", 100);
    set_skill("whip", 100);
    set_power("S");
    setup();
    carry_object("/d/wutang/npc/obj/silk_fishing_stick")->wield();
    carry_object("/d/wutang/npc/obj/straw_cloth")->wear();
    carry_object("/d/npc/obj/spider_boots")->wear();
}
