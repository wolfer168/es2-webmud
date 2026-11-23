// /d/oldpine/npc/obj/venison.c — 野店店小二賣的烤鹿肉。食物 +100，價值 40 文。

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
    set_name("烤鹿肉", ({ "roast venison", "venison" }));
    if( !clonep() ) {
        set("unit", "些");
        set("base_unit", "塊");
        set("base_value", 40);
        set("value", 40);   // F_VENDOR 直接讀 value
        set("base_weight", 300);
        set("food_stuff", 100);
        set("long", "香噴噴的烤鹿肉。\n");
    }
    set_amount(1);
    setup();
}
