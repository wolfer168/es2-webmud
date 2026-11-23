/* CUSTOM GHOST NPC: 魍魎 */
inherit "/d/npc/ghost/std_ghost";

void create()
{
    set_name("魍魎", ({ "water goblin", "goblin", "ghost" }));
    set("long",
        "一隻皮膚紅黑、耳朵很長的魍魎，喜歡在夜間模仿人類的聲音來嚇人，\n"
        "或是引誘人走進水裡溺死。\n");
    set("ghost_chat", ({
        "魍魎捏著嗓子，學著小孩的聲音哭喊：「救命啊……我掉進水裡了……」\n",
        "魍魎豎起兩隻長耳朵，咧開嘴對著你嘻嘻怪笑。\n",
    }));
    setup_ghost(100, 20);
}
