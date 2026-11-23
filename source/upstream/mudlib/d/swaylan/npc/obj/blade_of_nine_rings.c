/* 九環霸王刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("\x1b[1;36m九環霸王刀\x1b[m", ({ "blade of nine-rings", "blade" }));
    set_weight(26700);
    init_damage(4, 26, 172, 4, "twohanded blade");

    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 100000);
        set("long",
            "一把刀背串著九個銅環的九環刀，粗厚的刀柄上面寫著一個\n"
            "【霸】字，刀身閃閃發亮，在陽光的反射下現的非常的耀眼。\n");
        set("apply_weapon/twohanded blade", ([
            "intimidate": 50,
            "str": 1,
        ]));
    }
    setup();
}
