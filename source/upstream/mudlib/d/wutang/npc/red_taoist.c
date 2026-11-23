// /d/wutang/npc/red_taoist.c — 五堂鎮 NPC：紅衣道士（依五堂鎮設計表）。

#include <npc.h>
inherit F_FIGHTER;

void create()
{
    seteuid(getuid());
    set_name("紅衣道士", ({ "taoist", "red taoist" }));
    set_race("human");
    set_class("taoist");
    set_level(15);
    set("age", 20);
    set("long", @LONG
一身道士打扮，看他的氣息應是朱衣派道士。
LONG
    );
    set_skill("taoism-fire", 80);
    map_skill("spells", "taoism-fire");
    set("chat_chance_combat", 40);
    set("chat_msg_combat", ({
        (: command, "cast 1" :),
        (: command, "cast 2" :),
        (: command, "cast 3" :),
    }));
    set("custom_faction", "taoist.fire");   // 門派記號（docs/martial_arts/門派武功對照表.md）
    set_power("B");
    setup();
    carry_object("/d/wutang/npc/obj/red_robe")->wear();
    carry_object("/obj/example/weapon/longsword")->wield();
}
