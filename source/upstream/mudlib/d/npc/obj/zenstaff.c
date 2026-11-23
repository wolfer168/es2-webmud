/* 禪杖 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("禪杖", ({ "zenstaff", "staff" }));
    set_weight(15700);
    init_damage(3, 18, 135, 0, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("affix_short_name", "禪杖");
        set("unit", "把");
        set("value", 60000);
        set("long",
            "一把青銅鑄成的禪杖，拿在手中相當沉重。\n");
    }
    setup();
    // 武器附加屬性：每把新產生的武器擲一次前綴／後綴（adm/daemons/enhanced.c）。
    if( clonep() ) ENHANCE_D->roll_affix(this_object());
}
