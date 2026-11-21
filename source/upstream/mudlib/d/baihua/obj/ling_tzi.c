// /d/baihua/obj/ling_tzi.c — 血靈芝粉（老王回贈，穹槍訣任務；送去給懸崖平台的高玉）。

inherit ITEM;

void create()
{
    set_name("血靈芝粉", ({ "ling tzi", "ling_tzi", "powder" }));
    set_weight(1);
    if( !clonep() ) {
        set("unit", "包");
        set("value", 0);
        set("long", "一包紅色的粉末，帶著淡淡的桂花甜香。老王說這是千年血靈芝粉，對刀劍外創有神效。\n");
    }
    setup();
}
