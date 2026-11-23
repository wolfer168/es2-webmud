// /d/npc/obj/waterskin.c
// NEW（李家村復原版新增道具，非原始 ES2 資料，由專案成員指定數值）
// 純容器，裝清水用。買到手時已經裝滿；喝完可以用 fill 指令從其他水源裝過來。

inherit CONTAINER_ITEM;

// 液體 volume 單位：1000 = 1 升（見 std/item/liquid.c 的 short() 換算）
#define SKIN_CAPACITY 10000   // 10 公升

void create()
{
    seteuid(getuid());   // 產生時要順便裝一袋清水，需要有效 UID 才能 new()
    set_name("牛皮水袋", ({ "water skin", "waterskin", "skin" }));
    set_weight(500);
    set_max_encumbrance(SKIN_CAPACITY);
    set("liquid_container", 1);
    if( !clonep() ) {
        set("unit", "個");
        set("value", 50);
        set("long", "一口常見的牛皮水袋，出門在外必不可少。\n");
    }
    setup();
    if( clonep() ) {
        object w = new("/obj/water");
        w->set_volume(SKIN_CAPACITY);
        w->move(this_object());
    }
}
