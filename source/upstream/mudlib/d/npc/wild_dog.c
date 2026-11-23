// /d/npc/wild_dog.c — 喬陰縣 NPC：野狗（依使用者設計表，2026-10-16）。

#include <npc.h>

void create()
{
    seteuid(getuid());
    set_name("野狗", ({ "wild dog", "dog" }));
    set_race("beast");
    set_class("commoner");
    set_level(1);
    set("long", @LONG
路邊的一條野狗，髒兮兮的，看起來有點可憐。
LONG
    );
    set("unit", "條");
    set("beast_actions", ({
        ([ "action": "$N齜牙咧嘴地往$n的$l咬了過去", "damage_type": "咬傷" ]),
        ([ "action": "$N撲上前去，用爪子往$n的$l亂抓", "damage_type": "抓傷" ])
    }));
    // 野獸強度（1～10），數值見 daemon/race/beast.c。
    set_beast(1);
    setup();
}
