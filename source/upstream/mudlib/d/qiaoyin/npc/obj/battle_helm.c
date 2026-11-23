/* 步軍戰盔 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("步軍戰盔", ({ "battle helm", "helm" }));
    set_weight(2000);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 20000);
        set("long",
            "一頂天朝步軍武將的制式戰盔，整個頭盔用精鐵鑄成，頂上裝著尖刺，可\n"
            "以撞擊敵人，脖子部份也有皮護遮保護，戴起來威風凜凜。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor": 9,
            "intimidate": 10,
        ]));
    }
    setup();
}
