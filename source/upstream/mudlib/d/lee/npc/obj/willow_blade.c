// /d/lee/npc/obj/willow_blade.c
// NEW（李家村復原版新增道具，非原始 ES2 資料，由專案成員指定數值）
// 以 obj/area/obj/glaive.c（鬼頭刀：weight 9000, value 6000, setup_blade(2,10,80,0)）為基礎：
// 改為僅能單手的輕量刀，重量、售價各變動20%（9000->7200, 6000->7200），
// 傷害提高（setup_blade 的 y:10->14、z:80->100），並附加攻勢等級+5。

#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("柳葉刀", ({ "willow blade", "blade" }));
    set_weight(7200);
    setup_blade(2, 14, 100, 0);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 7200);
        set("rigidity", 25);
        set("long", "刃身微彎、狀似柳葉，只是刀背略薄，少了幾分厚重的氣勢。\n");
        set("apply_weapon/blade", (["intimidate": 5]));
    }
    setup();
}
