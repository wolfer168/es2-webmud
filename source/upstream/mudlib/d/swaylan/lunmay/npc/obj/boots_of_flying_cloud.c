/* 奔雲靴 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("\x1b[1;37m奔雲靴\x1b[m", ({ "boots of flying cloud", "boots" }));
    set_weight(500);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 25000);
        set("long",
            "一雙銀白色的長靴﹒光滑的表面，細緻的織工，讓你忍不住的想摸一\n"
            "摸。奇怪的是，這雙靴子的材質似乎不是這世界上的東西﹒據說是梅\n"
            "影風年輕時在北方大山的一場雪崩中所得的。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "dex": 1,
            "dodge": 15,
        ]));
    }
    setup();
}
