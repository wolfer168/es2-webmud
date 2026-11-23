/* CUSTOM GHOST NPC: 餓鬼 */
inherit "/d/npc/ghost/std_ghost";

void create()
{
    set_name("餓鬼", ({ "hungry ghost", "ghost" }));
    set("long",
        "一隻肚子大如鼓、食道卻細如針孔的餓鬼。每當牠看到食物想要進食時，\n"
        "食物就會化為烈火，只能永遠處於飢餓交迫的游離狀態。\n");
    set("ghost_chat", ({
        "餓鬼捧著鼓脹的肚子，嘶啞地哀號：「餓……好餓啊……」\n",
        "餓鬼盯著你身上的乾糧直流口水，喉嚨裡發出咕嚕咕嚕的聲音。\n",
    }));
    setup_ghost(20, 20);
}
