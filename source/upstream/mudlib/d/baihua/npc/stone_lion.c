// /d/baihua/npc/stone_lion.c — 百花村：石獅子（依使用者設計表，2026-10-20）。
// 繼承練武假人底本：不還手、不損壞，被擊中的敘述不提部位（設計文件：docs/TRAINING_DUMMY.md）。
inherit "/feature/npc/training_dummy";

void create()
{
    set_name("石獅子", ({"stone lion","lion","石獅子"}));
    set("long", "一尊蹲坐在廟門口的石獅子，石身佈滿青苔與裂紋，鬃毛的雕紋卻依舊清晰。它張著大口、瞪著圓眼，神態威武，不時有路過的人朝它比劃幾下拳腳，它也只是默默地承受著。
");
    setup();
}
