// /d/npc/squirrel.c — 迷霧森林／老松林 野獸：松鼠（強度 1，野豬為 4）。

#include <npc.h>

void create()
{
    seteuid(getuid());
    set_name("松鼠", ({ "squirrel" }));
    set_race("beast");
    set_class("commoner");
    set_level(1);
    set("long", @LONG
森林裡的松鼠數量眾多，同時也是獵人的主要獵物之一。
LONG
    );
    set("beast_actions", ({
        ([ "action": "$N張口往$n的$l咬去", "damage_type": "咬傷" ]),
        ([ "action": "$N跳到$n身上，往$n的$l抓了一把", "damage_type": "抓傷" ])
    }));
    // 野獸強度（1～10），數值見 daemon/race/beast.c。
    set_beast(1);
    setup();
}
