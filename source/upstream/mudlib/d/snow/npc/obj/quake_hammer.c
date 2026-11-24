/* 撼山鎚 — 撼山鎚法任務的獎勵，雪亭鎮鐵匠用黑鐵大槌重打而成，一次給兩柄
 * （/d/snow/npc/smith；docs/martial_arts/共通_撼山鎚法.md）。左右手都能拿。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLUNT;

void create()
{
    set_name("撼山鎚", ({ "quake hammer", "hammer", "blunt" }));
    set_weight(3500);
    setup_blunt(3, 12, 100, 2);

    if( !clonep() ) {
        set("wield_as", ({ "blunt", "secondhand blunt" }));
        set("unit", "柄");
        set("value", 6000);
        set("long",
            "一柄黑沉沉的短柄鐵鎚，是用黑鐵大槌熔了重打的，鎚身不大卻十分壓手，"
            "鎚頭上還留著一圈圈細密的鍛紋。\n");
    }
    setup();
}
