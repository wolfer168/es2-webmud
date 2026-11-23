/* CUSTOM GHOST NPC: 倀鬼 */
inherit "/d/npc/ghost/std_ghost";

void create()
{
    set_name("倀鬼", ({ "tiger thrall", "thrall", "ghost" }));
    set("long",
        "一個被老虎咬死的人所化的倀鬼。死後靈魂無法投胎，反而成為老虎的奴隸，\n"
        "替老虎引路去吃更多的人。\n");
    set("ghost_chat", ({
        "倀鬼堆起一臉詭異的笑容，招手道：「這邊走，這邊的路比較近……」\n",
        "倀鬼側耳傾聽山林深處的虎嘯，身子不由自主地打了個哆嗦。\n",
    }));
    setup_ghost(60, 30);
}
