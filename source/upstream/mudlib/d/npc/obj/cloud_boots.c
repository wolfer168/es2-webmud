/* 流雲靴 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("流雲靴", ({ "cloud boots", "boots" }));
    set_weight(1000);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 4000);
        set("long",
            "一雙用某種毛皮縫製的灰白色長靴，質地輕而耐用。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 3,
            "dex": 1,
        ]));
    }
    setup();
}
