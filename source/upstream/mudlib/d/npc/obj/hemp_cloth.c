// /d/npc/obj/hemp_cloth.c
// NEW（李家村復原版新增道具，非原始 ES2 資料，由專案成員指定數值）
// 內容與 obj/area/obj/cloth.c（布衣）完全一致，僅名稱不同。
// 補了 "hemp"/"hemp cloth" 這兩個更明確的代號，跟共用池的布衣("cloth")區隔開，
// 同一人身上兩者都有時也能準確指定。

#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("麻布衣", ({ "hemp cloth", "hemp", "cloth" }));
    set_weight(1000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 0);
        set("long", "一套普通的棉布衣褲。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 1,
        ]));
    }

    setup();
}
