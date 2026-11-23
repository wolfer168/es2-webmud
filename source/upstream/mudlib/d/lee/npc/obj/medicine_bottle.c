inherit ITEM;
void create()
{
    set_name("小藥瓶", ({ "medicine bottle", "small bottle", "bottle" }));
    set_weight(300); set_max_encumbrance(1200);
    set("unit", "個"); set("value", 30); set("container_unit", "瓶");
    set("liquid_container", 1);
    set("long", "一個小巧的藥瓶，可以盛裝少量液體或藥材。原版精確用途仍待資料核對。\n");
    setup();
}
int accept_object(object me, object ob) { return 1; }
