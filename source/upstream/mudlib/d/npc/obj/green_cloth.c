/* 翠綠短杉 — 舊站裝備（夜羅剎身上）。名稱取自舊站畫面紀錄；數值與敘述由使用者提供（2026-10-15）。NEW */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name(HIG "翠綠短杉" NOR, ({ "green cloth", "cloth" }));
    set_weight(800);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 1500);
        set("long",
            "一件翠綠色的短上衣，是尋常人家難以觸及的珍品。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 3,
            "spi": 1,
            "int": 1,
        ]));
    }
    setup();
}
