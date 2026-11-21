/* 混元清水 — 混元一氣袋（custom/item/super_skin.c）裡的水。
 * 在混元一氣袋裡被喝掉一部分、但還有剩餘時，馬上補回 10 公升；整袋倒光了就不再補。
 * 倒進別的容器時（fill）不帶補滿的效果，只是一般的清水。 */

inherit LIQUID_ITEM;
inherit F_DRINK;

#define SKIN_CAPACITY 10000   // 10 公升，與 super_skin.c 一致

void create()
{
    set_name("清水", ({ "water" }));
    if( !clonep() ) {
        set("long", "... 水就是水﹐沒啥好看的。\n");
        set("density", 1);
    }
    setup();
    set_volume(1000);
}

void add_volume(int v)
{
    object env = environment();

    // 只有裝在混元一氣袋裡、減少後還有剩餘，才補滿。
    if( v < 0 && env && env->query("auto_refill") && query_volume() + v > 0 ) {
        set_volume(SKIN_CAPACITY);
        return;
    }
    ::add_volume(v);
}
