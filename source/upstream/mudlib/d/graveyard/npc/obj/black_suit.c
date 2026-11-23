/* 黑獄服 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("黑獄服", ({ "black suit", "suit" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 10000);
        set("long",
            "這是一件相當輕飄的暗黑色緊身衣﹐所用材料相當有彈性所以對外\n"
            "力有相當的反禦力﹐是適於夜中行走的裝備。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "sneak": 5,
            "armor": 10,
        ]));
    }
    setup();
}
