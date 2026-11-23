/* 玄蛛皂白靴 — ES2 原始護具資料。由五堂鎮小船上的煙波釣叟（/d/wutang/npc/smoke_fisher）穿戴。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("玄蛛皂白靴", ({ "spider boots", "boots" }));
    set_weight(500);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 15000);
        set("long",
            "這是一雙由響冰天池的玄蛛所吐的皂白絲所織成的短靴。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "dex": 3,
        ]));
    }
    setup();
}
