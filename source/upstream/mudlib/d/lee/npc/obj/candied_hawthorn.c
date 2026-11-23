// /d/lee/npc/obj/candied_hawthorn.c
// NEW（李家村復原版新增道具，非原始 ES2 資料，由專案成員指定數值）

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
    set_name("冰糖葫蘆", ({ "candied hawthorn", "hawthorn" }));
    if( !clonep() ) {
        set("unit", "堆");
        set("base_unit", "串");
        set("base_value", 5);
        set("value", 5);   // F_VENDOR reads "value" directly, not base_value
        set("base_weight", 150);
        set("food_stuff", 10);
        set("long", "一串用竹籤串起的山楂，外頭裹著一層晶亮的冰糖，紅豔可愛，吃起來酸甜可口。\n");
    }
    set_amount(1);
    setup();
}
