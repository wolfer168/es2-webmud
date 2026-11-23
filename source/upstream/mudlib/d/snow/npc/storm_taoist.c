#include <npc.h>

inherit F_FIGHTER;

void create()
{
    seteuid(getuid());
    set_name("玄衣派弟子", ({ "black-taoist", "black taoist", "black", "taoist", "玄衣派弟子" }));
    set_race("avatar");
    set_class("taoist");
    set_level(30);

    // Race initialization fills every attribute not specified here.

    set_skill("taoism-storm", 160);
    map_skill("spells", "taoism-storm");

    set("long", "這名玄衣派弟子精通天師道法【風符】，手持長劍，身穿布衣。\n");
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
        (: command, "cast 1" :),
        (: command, "cast 2" :),
        (: command, "cast 3" :),
        (: command, "cast 4" :)
    }));

    set("custom_faction", "taoist.storm");   // 門派記號（docs/martial_arts/門派武功對照表.md）
    set_power("B");
    setup();
    carry_object("/obj/area/obj/cloth")->wear();
    carry_object("/obj/area/obj/longsword")->wield();
}