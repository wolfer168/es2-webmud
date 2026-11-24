// /d/lee/npc/obj/sheepskin_vest.c
// NEW（野羊山事件新增道具，設計見 docs/LEE_BANDIT_RAID.md）
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("羊皮罩衫", ({ "sheepskin vest", "vest" }));
    set_weight(3000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 1500);
        set("long",
            "一件連毛帶皮縫成的粗羊皮罩衫，針腳歪歪斜斜，穿在身上又悶又熱，卻能擋\n"
            "下不少刀劍。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "cps": 1,
            "armor": 15,
        ]));
    }
    setup();
}
