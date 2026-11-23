// /d/obj/well.c
// NEW（李家村復原版新增道具，非原始 ES2 資料，由專案成員指定數值）
// 功能與 d/snow/npc/obj/pot.c（大水缸）相同：固定在房間裡、標記為裝水容器、
// 水量用 reset() 自動補滿，不會被用完。

inherit ITEM;

void create()
{
    object water;

    seteuid(getuid());   // 產生時要放一井清水，需要有效 UID 才能 new()
    set_name("水井", ({ "well" }));
    set_max_encumbrance(180000);
    set("long", "一口普通的水井，井口以石塊砌成，井中有清水，可供村民取用。\n");
    set("no_get", 1);
    set("liquid_container", 1);
    setup();
    if( clonep() ) {
        water = new("/obj/water");
        water->set_volume(100000);
        water->move(this_object());
    }
}

varargs int accept_object(object me, object ob)
{
    if( ob )
        if( !userp(ob) )
            return 1;
    else return notify_fail("你不能將玩家放到容器裡面。\n");
}

// 補滿：清水被喝光時液體物件會消失，以前的 reset() 只補還在的，喝乾後就不會再有。
// 現在不見了就重新放一份，再補到滿；房間每次重生（reset）時也會呼叫。
void refill()
{
	object liquid;

	if( !(liquid = present("water", this_object())) ) {
		seteuid(getuid());
		liquid = new("/obj/water");
		liquid->move(this_object());
	}
	liquid->set_volume(100000);
}

void reset()
{
	refill();
}
