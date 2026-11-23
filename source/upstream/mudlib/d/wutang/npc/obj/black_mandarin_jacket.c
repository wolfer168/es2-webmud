/* 黑醬色馬褂 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("黑醬色馬褂", ({ "black robe", "robe" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 1500);
        set("long",
            "一襲黑色油亮的馬褂, 看到那晶瑩的色澤讓人忍不住想摸摸看。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 5,
        ]));
    }
    setup();
}
