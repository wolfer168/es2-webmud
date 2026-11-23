// /d/qiaoyin/npc/apprentice.c — 喬陰縣 NPC：桐城派二代弟子（依使用者設計表，2026-10-16）。

#include <npc.h>
inherit F_FIGHTER;

void create()
{
    seteuid(getuid());
    // 「桐城派」只是稱號，不屬於門派表中的門派（使用者決定）。
    set_name("桐城派二代弟子", ({ "apprentice" }));
    set_race("human");
    set_class("fighter");
    set_level(10);
    set("gender", "male");
    set("age", 20);
    set("long", @LONG
來自桐城的二代弟子，功力一般，正盤算著暫時在金水客棧落腳。
LONG
    );
    set_power("C");
    setup();
    carry_object("/d/npc/obj/white_scholar_dress")->wear();
    carry_object("/obj/area/obj/longsword")->wield();
}
