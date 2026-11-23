// /d/oldpine/npc/bandit_minion.c — 老松林 NPC：土匪嘍囉（依老松林設計表）。

#include <npc.h>

inherit F_FIGHTER;


void create()
{
    seteuid(getuid());
    set_name("土匪嘍囉", ({ "bandit minion", "minion", "bandit" }));
    set_race("human");
    set_class("thief");
    set_level(5);
    set("long", @LONG
看起來沒啥江湖經驗，努力裝兇卻顯得異常可笑。
LONG
    );
    set_skill("blade", 10);
    set_skill("dodge", 10);
    set_skill("parry", 10);
    set_skill("unarmed", 10);
    // 擊殺者獲得戰場功勳。
    set("bounty", ([ "military service": 5 ]));
    set_power("C");
    setup();
    carry_object("/obj/area/obj/blade")->wield();
    carry_object("/d/oldpine/npc/obj/leather_vest")->wear();
    carry_money("silver", 2);
}
