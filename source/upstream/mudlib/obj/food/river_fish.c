// river_fish.c — 河魚（釣魚所得）。吃完有 5% 機會吃出河魚腹珠。設計見 docs/FISHING_DESIGN.md。

inherit ITEM;
inherit F_FOOD;

void create()
{
    set_name("河魚", ({ "river fish", "fish" }));
    set_weight(200);
    if( !clonep() ) {
        set("unit", "尾");
        set("value", 20);
        set("food_stuff", 20);
        set("long", "一尾剛從河裡釣上來的魚，銀灰色的鱗片在光下閃著水光，尾巴還在不甘心地拍打。清蒸、燒烤都好，就算生啃也填得了肚子。\n");
    }
    setup();
}

/* 吃完河魚：5% 吃出河魚腹珠，直接進身上的物品欄（放不下就掉在地上）。 */
int stuff_ob(object me)
{
    object pearl;

    if( !::stuff_ob(me) ) return 0;

    if( random(100) < 5 && objectp(pearl = new("/obj/fish_pearl")) ) {
        tell_object(me, "你嚼著嚼著﹐牙齒碰到一顆硬東西﹐吐出來一看﹐竟是顆珍珠﹗\n");
        if( !pearl->move(me) ) pearl->move(environment(me));
    }
    return 1;
}
