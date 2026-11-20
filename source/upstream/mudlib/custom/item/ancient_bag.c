/* 太古塵包 — 奐族以古法製作的容器，容量為麻布袋（obj/area/obj/bag.c）的 15 倍。風城小販販售（取代龍麟袋）。
 * 設計文件：docs/CUSTOM_ANCIENT_BAG_AND_SUPER_SKIN.md */
#include <ansi.h>

inherit ITEM;

void create()
{
    set_name(YEL "太古塵包" NOR, ({ "ancient bag", "bag" }));
    set_weight(700);
    set_max_encumbrance(450000);   // 麻布袋 30000 的 15 倍
    if( !clonep() ) {
        set("unit", "隻");
        set("value", 20000);
        set("long",
            "這是奐族以古法縫製的大布袋，袋面蒙著一層洗不去的陳年塵灰，織紋\n"
            "細密如鱗。袋口看似尋常，裡頭卻深不見底，塞進再多東西也不見鼓脹。\n");
    }
    setup();
}

int accept_object() { return 1; }
