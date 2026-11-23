/* 金線僧袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("金線僧袍", ({ "gold robe", "robe" }));
    set_weight(6000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 85000);
        set("long",
            "一件花俏的僧袍，紅底黃邊加上金色繡線，雙肩上都各繡了一個佛字，而且重\n"
            "量比起一般衣服重了許多，翻到內層才發現奧妙所在，原來它內部是金絲織成\n"
            "的金褸衣，看來用一般的武器可能還不容易劃破這件僧袍呢。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "absorption": 15,
            "armor": 25,
        ]));
    }
    setup();
}
