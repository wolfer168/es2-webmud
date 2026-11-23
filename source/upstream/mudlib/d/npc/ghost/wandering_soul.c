/* CUSTOM GHOST NPC: 遊魂 */
inherit "/d/npc/ghost/std_ghost";

void create()
{
    set_name("遊魂", ({ "wandering soul", "soul", "ghost" }));
    set("long",
        "一縷不屬於任何家族牌位的遊魂，無人祭祀、無處可歸，只能等待陽間的\n"
        "慈善廟宇進行集體收容與超度。\n");
    set("ghost_chat", ({
        "遊魂茫然地四處飄蕩，低聲問道：「有誰……記得我的名字嗎？」\n",
        "遊魂望著遠方廟宇的香火，幽幽地嘆了一口氣。\n",
    }));
    setup_ghost(40, 20);
}
