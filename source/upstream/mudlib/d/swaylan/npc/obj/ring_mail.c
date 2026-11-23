/* 鎖子鎧 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("鎖子鎧", ({ "ring mail", "mail" }));
    set_weight(8000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 8000);
        set("long",
            "一件用上千個鐵環嵌結而成的鎖子鎧﹐雖然防禦力比不上戰場上\n"
            "常用的重型戰鎧﹐但是輕便堅固﹐不會妨礙行動則是戰鎧所沒有\n"
            "的優點。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 5,
        ]));
    }
    setup();
}
