/* 無相福田 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("\x1b[1;31m無相福田\x1b[m", ({ "animitta kasaya", "kasaya" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 45000);
        set("long",
            "一件大紅色的袈裟，隱隱流動著淡淡的金色光暈。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "cps": 2,
            "compassion": 10,
        ]));
    }
    setup();
}
