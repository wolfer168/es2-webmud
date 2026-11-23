// /d/lee/npc/obj/big_candied_hawthorn.c
// NEW（李家村復原版新增道具，非原始 ES2 資料，由專案成員指定數值）

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
    set_name("大冰糖葫蘆", ({ "big candied hawthorn", "big hawthorn" }));
    if( !clonep() ) {
        set("unit", "堆");
        set("base_unit", "串");
        set("base_value", 8);
        set("value", 8);   // F_VENDOR reads "value" directly, not base_value
        set("base_weight", 280);
        set("food_stuff", 20);
        set("long", "一大串紅豔豔的山楂，外面裹著厚厚的冰糖，比普通的冰糖葫蘆大了許多。\n");
    }
    set_amount(1);
    setup();
}
