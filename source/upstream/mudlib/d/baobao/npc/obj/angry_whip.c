/* 怒天鞭 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_WHIP;

void create()
{
    set_name("\x1b[1;35m怒天鞭\x1b[m", ({ "angry whip", "whip" }));
    set_weight(7300);
    init_damage(3, 14, 85, 8, "whip");

    if( !clonep() ) {
        set("wield_as", "whip");
        set("unit", "把");
        set("value", 5000);
        set("long",
            "一條殷紅色長鞭，鞭子表面十分光滑，像是用人血染成的顏色。\n");
        set("apply_weapon/whip", ([
            "magic": 10,
            "taoism of darkness": 10,
        ]));
    }
    setup();
}
