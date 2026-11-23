/* CUSTOM GHOST NPC: 魑魅 */
inherit "/d/npc/ghost/std_ghost";

void create()
{
    set_name("魑魅", ({ "mountain sprite", "sprite", "ghost" }));
    set("long",
        "一隻由深山老林中的瘴氣、木石等自然異氣化生而成的精怪，身形忽濃忽淡，\n"
        "隱約帶著一股潮濕腐朽的草木氣味。\n");
    set("ghost_chat", ({
        "魑魅化作一團灰綠色的瘴氣，在林間緩緩盤旋，發出沙沙的怪響。\n",
        "魑魅的身形忽然散成點點磷光，片刻後又在不遠處重新聚攏。\n",
    }));
    setup_ghost(100, 20);
}
