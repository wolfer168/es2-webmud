/* 掩心甲 — 舊站裝備（許彥之身上）。名稱取自舊站畫面紀錄；數值與敘述由使用者提供（2026-10-15），
 * 比照 /d/npc/obj/leather_armor.c。NEW */
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("掩心甲", ({ "heart armor", "armor" }));
    set_weight(10000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 2000);
        set("long",
            "一件輕便的皮甲，在心口處強化防禦，讓裝備者行動自如的同時還兼顧要害的防禦。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 8,
            "cps": 1,
        ]));
    }
    setup();
}
