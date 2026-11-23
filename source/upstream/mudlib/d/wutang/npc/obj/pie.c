// /d/wutang/npc/obj/pie.c — 五堂鎮賣餅大叔賣的餡餅。價值 30 文。

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
    set_name("餡餅", ({ "pie" }));
    if( !clonep() ) {
        set("unit", "疊");
        set("base_unit", "個");
        set("base_value", 30);
        set("value", 30);   // F_VENDOR 直接讀 value
        set("base_weight", 150);
        set("food_stuff", 20);
        set("long", "熱騰騰的餡餅，大人小孩都喜歡。\n");
    }
    set_amount(1);
    setup();
}
