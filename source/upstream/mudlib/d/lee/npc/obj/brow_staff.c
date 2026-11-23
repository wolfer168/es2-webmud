// /d/lee/npc/obj/brow_staff.c
// NEW（李家村復原版新增道具，非原始 ES2 資料，由專案成員指定數值）
// 以 d/snow/npc/obj/cane.c（拐杖）為基礎：傷害四參數 +10%（四捨相關計算後取整數，
// 仍在杖類上限 x<=3/y<=25/z<=250/r 範圍內）；重量、售價 +10% 後無條件進到百位。

#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("齊眉棍", ({ "brow staff", "staff" }));
    set_weight(2700);              // 拐杖 2400 * 1.1 = 2640，無條件進位到百位
    setup_staff(1, 21, 143, 0);    // 拐杖 setup_staff(1,19,130,0) 各項 *1.1

    if( !clonep() ) {
        set("wield_as", ({ "staff", "twohanded staff" }));
        set("affix_short_name", "棍");
        set("unit", "根");
        set("value", 700);         // 拐杖 600 * 1.1 = 660，無條件進位到百位
        set("rigidity", 12);       // 沿用拐杖數值，未要求調整
        set("long", "一根常見的齊眉棍，棍身結實，是守衛用來防身的尋常兵器。\n");
    }
    setup();
    // 武器附加屬性：每把新產生的武器擲一次前綴／後綴（adm/daemons/enhanced.c）。
    if( clonep() ) ENHANCE_D->roll_affix(this_object());
}
