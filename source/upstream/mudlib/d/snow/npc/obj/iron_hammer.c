/* 鐵鎚 — 雪亭鎮鐵匠販售（/d/snow/npc/smith）。單手鎚，左右手都能拿，
 * 兩柄就能雙鎚分持（撼山鎚法，docs/martial_arts/共通_撼山鎚法.md）。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLUNT;

void create()
{
    set_name("鐵鎚", ({ "iron hammer", "hammer", "blunt" }));
    set_weight(3500);
    setup_blunt(2, 8, 60, 0);

    if( !clonep() ) {
        set("wield_as", ({ "blunt", "secondhand blunt" }));
        set("unit", "柄");
        set("value", 1500);
        set("long",
            "一柄打鐵用的鐵鎚，木柄磨得光滑，鎚頭方方正正，拿來防身也還趁手。\n");
    }
    setup();
}
