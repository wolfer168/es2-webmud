// /d/npc/obj/salt.c
// NEW（李家村復原版新增道具，非原始 ES2 資料，由專案成員指定數值）

inherit COMBINED_ITEM;

void create()
{
    set_name("鹽", ({ "salt" }));
    if( !clonep() ) {
        set("unit", "堆");
        set("base_unit", "包");
        set("base_value", 10);
        set("value", 10);   // F_VENDOR reads "value" directly, not base_value
        set("base_weight", 200);
        set("long", "一小包潔白的細鹽，可用來調味食物。\n");
    }
    set_amount(1);
    setup();
}
