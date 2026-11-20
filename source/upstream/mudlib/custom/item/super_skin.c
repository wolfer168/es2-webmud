/* 混元一氣袋 — 奐族製作的神祕水袋，袋中只要還有剩餘，馬上補滿，容量 10 公升。
 * 買到手時已經裝滿。補滿的是袋裡的混元清水（custom/item/super_skin_water.c）。
 * 設計文件：docs/CUSTOM_ANCIENT_BAG_AND_SUPER_SKIN.md */
#include <ansi.h>

inherit CONTAINER_ITEM;

// 液體 volume 單位：1000 = 1 升（見 std/item/liquid.c 的 short() 換算）
#define SKIN_CAPACITY 10000   // 10 公升

void create()
{
    seteuid(getuid());   // 產生時要順便裝一袋水，需要有效 UID 才能 new()
    set_name(HIM "混元一氣袋" NOR, ({ "super skin", "skin" }));
    set_weight(500);
    set_max_encumbrance(SKIN_CAPACITY);
    set("liquid_container", 1);
    set("auto_refill", 1);   // 袋裡的混元清水被喝掉一部分時，馬上補滿（見 super_skin_water.c）
    if( !clonep() ) {
        set("unit", "個");
        set("value", 100000);
        set("long",
            "這是奐族製作的一只神祕水袋，袋身暗紫，摸來溫潤如玉。內裡彷彿藏著\n"
            "一口不竭的活泉，袋中只要還剩一口水，轉眼又會盈滿。\n");
    }
    setup();
    if( clonep() ) {
        object w = new("/custom/item/super_skin_water");
        w->set_volume(SKIN_CAPACITY);
        w->move(this_object());
    }
}
