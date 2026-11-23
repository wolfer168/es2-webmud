// /d/lee/npc/lee_yong.c
// NEW（李家村復原版新增角色，非原始 ES2 資料，由專案成員指定人設，取代原本的通用「獵戶」佔位角色）

#include <npc.h>
inherit F_VILLAGER;

void create()
{
    set_name("李勇", ({ "lee yong", "li yong", "lee", "li", "yong" }));
    set_race("human");
    set_class("fighter");
    set_level(15);
    set_skill("pike", 30);
    set("age", 20);
    set("long", @LONG
李勇是村子裡惟一的獵戶，雖然沒學過甚麼武功，天生的神力卻讓他足以打敗
普通好手，從他家裡滿屋子的獸皮你就能了解他的實力。
LONG
    );
    set_power("B");
    setup();
    carry_object("/d/lee/npc/obj/leather_boots")->wear();
    carry_object("/d/lee/npc/obj/tight_cloth")->wear();
    carry_object("/d/lee/npc/obj/hunter_pike")->wield();
}
