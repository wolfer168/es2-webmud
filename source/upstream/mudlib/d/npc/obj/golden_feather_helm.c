/* 金羽神盔 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("金羽神盔", ({ "helm" }));
    set_weight(2000);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 12000);
        set("long",
            "金色烏鴉在人們心目中一直是太陽的象徵, 雖然古籍中記載確有其事, 但現今\n"
            "也沒有任何人看過. 這頂盔帽金光閃閃, 令人眼炫, 盔緣鑲有金色羽毛, 據聞\n"
            "為金色烏鴉所遺, 有降魔鎮鬼之能.\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "damage": 5,
            "armor": 5,
            "str": 1,
        ]));
    }
    setup();
}
