// /d/npc/obj/coarse_cloth.c — 粗布衣（徐彪），防禦力 3。
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("粗布衣", ({ "coarse cloth", "cloth" }));
    set_weight(1200);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 150);
        set("long", "一件用粗麻布縫成的衣服，布料粗糙厚實，倒也耐磨耐穿。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 3,
        ]));
    }
    setup();
}
