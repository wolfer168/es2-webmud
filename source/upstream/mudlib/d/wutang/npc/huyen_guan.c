// /d/wutang/npc/huyen_guan.c — 五堂鎮 NPC：綠竹居士 呼延光（依五堂鎮設計表）。

#include <npc.h>
inherit F_SCHOLAR;

void create()
{
    seteuid(getuid());
    set_name("呼延光", ({ "huyen guan", "huyen", "guan" }));
    set_race("human");
    set_class("scholar");
    set_level(35);
    set("title", "綠竹居士");
    set("age", 50);
    set("long", @LONG
一位隱居在綠竹林中的居士，一襲雪白長袍，神態閒適，眉宇間透著一股
書卷氣。據說他見多識廣，天下奇聞軼事少有他不知道的，連五陵客棧的
李再延都對他推崇備至。
LONG
    );
    set_power("A");
    setup();
    carry_object("/d/npc/obj/white_cloth")->wear();
}
