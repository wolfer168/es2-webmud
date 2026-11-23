// /d/npc/obj/dragon_pill.c — 武魁龍轉（受傷的旅客身上）。
// 吃下後：食物 +5、飲水 -30；精目前值 +30、實格 +50；氣目前值 +100、實格 +120；
// 形體目前值與實格各恢復根骨（con）點。都不會超過上限。

inherit ITEM;

void create()
{
    set_name("武魁龍轉", ({ "dragon pill", "pill" }));
    set_weight(5);
    if( !clonep() ) {
        set("unit", "顆");
        set("value", 100000);
        set("long", "天朝罕見的丹藥，療傷效果奇佳。\n");
    }
    setup();
}

int stuff_ob(object me)
{
    int con = me->query_attr("con");

    message_vision("$N吞下一顆武魁龍轉，頓時覺得一股暖流遊走全身。\n", me);
    me->supplement_stat("food", 5);
    me->consume_stat("water", 30);
    me->heal_stat("gin", 50);
    me->supplement_stat("gin", 30);
    me->heal_stat("kee", 120);
    me->supplement_stat("kee", 100);
    if( con > 0 ) {
        me->heal_stat("HP", con);
        me->supplement_stat("HP", con);
    }
    destruct(this_object());
    return 1;
}
