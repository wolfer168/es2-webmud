// /d/wutang/npc/white_taoist.c — 五堂鎮 NPC：白衣道士（依五堂鎮設計表）。

#include <npc.h>
inherit F_FIGHTER;

void create()
{
    seteuid(getuid());
    set_name("白衣道士", ({ "taoist", "white taoist" }));
    set_race("woochan");
    set_class("taoist");
    set_level(15);
    set("age", 25);
    set("long", @LONG
身上透出淡淡的寒氣，應該是修習冰咒的素衣派道士。
LONG
    );
    set_skill("taoism-freeze", 80);
    map_skill("spells", "taoism-freeze");
    set("chat_chance_combat", 40);
    set("chat_msg_combat", ({
        (: command, "cast 1" :),
        (: command, "cast 2" :),
        (: command, "cast 3" :),
    }));
    set("custom_faction", "taoist.freeze");   // 門派記號（docs/martial_arts/門派武功對照表.md）
    set_power("B");
    setup();
    carry_object("/d/wutang/npc/obj/white_taoist_robe")->wear();
    carry_object("/obj/example/weapon/longsword")->wield();
}
