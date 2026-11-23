// /d/lee/npc/traveller.c
// NEW（李家村復原版新增角色，非原始 ES2 資料，由專案成員指定人設）
// 註：d/oldpine/npc/traveller.c 已存在同名「過路客」角色，但人設完全不同（jiaojao 種族、
// 女性、盜賊職、20 級、佩鞭），與此處要求的一般路人不符，故另外新建。

#include <npc.h>
inherit F_VILLAGER;

void create()
{
    set_name("旅客", ({ "traveller" }));
    set_race("human");
    set_class("commoner");
    set_level(5);
    set("age", 20);
    set("long", "路上來來往往的旅人，每天都能碰上十來個。\n");
    set_power("C");
    setup();
    carry_object("/obj/area/obj/cloth")->wear();
    carry_object("/obj/area/obj/shortsword")->wield();
}
