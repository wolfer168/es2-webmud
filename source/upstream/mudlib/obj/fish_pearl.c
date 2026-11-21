// fish_pearl.c — 河魚腹珠。拿給五堂鎮醇雨樓三樓的珍寶商人可以抽獎。設計見 docs/FISHING_DESIGN.md。

inherit ITEM;

void create()
{
    set_name("河魚腹珠", ({ "fish pearl", "pearl" }));
    set_weight(10);
    if( !clonep() ) {
        set("unit", "顆");
        set("value", 10000);
        set("long", "一顆從河魚肚子裡找到的小珍珠，珠身渾圓，在手心裡泛著柔和的乳白光澤。珍寶商人都說，這種河珠雖不比海珠名貴，卻自有一股說不出的靈氣，愛珍寶的人多半肯收。\n");
    }
    setup();
}
