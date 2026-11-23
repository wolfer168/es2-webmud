/* 鐵布衫 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("\x1b[1;33m鐵布衫\x1b[m", ({ "iron cloth", "cloth" }));
    set_weight(6000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 9500);
        set("long",
            "一件發著銀鐵光的罩衫, 這件鐵布衫是用平常刀劍不易斬斷的銀鐵\n"
            "絲編織而成, 是一件相當罕見的護具, 據說是京城內好幾位名匠共同製\n"
            "成的。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 15,
        ]));
    }
    setup();
}
