/* CUSTOM GHOST NPC: 枉死鬼 */
inherit "/d/npc/ghost/std_ghost";

void create()
{
    set_name("枉死鬼", ({ "wronged ghost", "ghost" }));
    set("long",
        "一個因意外而亡的枉死鬼，無法投胎轉世，只能在事發地點附近遊蕩，\n"
        "一遍又一遍地重複著死前的那一刻。\n");
    set("ghost_chat", ({
        "枉死鬼喃喃自語：「我不該死的……我還不該死的……」\n",
        "枉死鬼突然停下腳步，驚恐地回頭張望，彷彿又看見了當日的慘事。\n",
    }));
    setup_ghost(50, 25);
}
