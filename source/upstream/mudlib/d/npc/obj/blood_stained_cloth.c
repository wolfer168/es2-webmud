/* 征衣「血染」 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("征衣「血染」", ({ "blood cloth", "cloth" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 100000);
        set("long",
            "一件和陽間將官所穿的征衣類似的戰袍﹐雖然洗得相當乾淨﹐但是\n"
            "聞起來確有一股血腥氣。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "str": 3,
            "armor": 5,
        ]));
    }
    setup();
}
