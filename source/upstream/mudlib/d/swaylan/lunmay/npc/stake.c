// /d/swaylan/lunmay/npc/stake.c — 冷梅莊 NPC：假人（照振武軍營的假人，敘述改成冷梅莊的）。
// 繼承練武假人底本（設計文件：docs/TRAINING_DUMMY.md）。
inherit "/feature/npc/training_dummy";

void create()
{
    set_name("假人", ({"target stake","stake","假人"}));
    set("long", "一具用粗木紮成的假人，牢牢釘在地上，身上佈滿了深淺不一的劍痕，是冷梅莊弟子平日練劍用的。\n");
    setup();
}
