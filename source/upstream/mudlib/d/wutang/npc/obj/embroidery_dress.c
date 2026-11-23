/* 繡花旗袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("繡花旗袍", ({ "embroidery dress", "dress" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 20000);
        set("long",
            "這是一件大紅色的繡花旗袍，紅色的底上繡上金色的繡花煞是好看，左胸前繡\n"
            "的那隻飛鳳甚是靈動，看來用的應該是傳聞中的織井鏽的繡工手法吧。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 4,
            "wis": 1,
            "cps": 1,
        ]));
    }
    setup();
}
