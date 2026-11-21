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
        set("long", "一尾剛從河裡釣上來的魚，尾巴還在不甘心地拍打著。\n");
    }
    setup();
}

/* 吃完河魚：5% 吐出河魚腹珠。
 * F_FOOD 的 stuff_ob 吃完會把自己 destruct 掉，所以先擲骰、先把珍珠準備好，
 * 吃成功後才交給玩家，不在魚消失之後才做事（消失後的物件不能再 new 東西）。
 * 身上放不下就掉在地上；吃不下（太飽）時珍珠不交出，直接丟掉。 */
int stuff_ob(object me)
{
    object pearl, env;

    if( random(100) < 5 ) pearl = new("/obj/fish_pearl");
    env = environment(me);

    if( !::stuff_ob(me) ) {
        if( pearl ) destruct(pearl);
        return 0;
    }

    if( pearl ) {
        tell_object(me, "你嚼著嚼著﹐牙齒碰到一顆硬東西﹐吐出來一看﹐竟是顆珍珠﹗\n");
        if( !pearl->move(me) ) pearl->move(env);
    }
    return 1;
}
