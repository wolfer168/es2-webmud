// /d/lee/npc/obj/hunter_pike.c
// NEW（李家村復原版新增道具，非原始 ES2 資料，由專案成員指定數值）
// 以 obj/area/obj/pike.c（長槍：weight 11000, value 6000, setup_pike(2,11,60,1)）為基礎：
// 重量、售價各降 20%（11000->8800, 6000->4800）；傷害略低於長槍，
// 將 y(傷害範圍) 11->10、z(力量加成%) 60->55，multiplier/roll 維持不變。

#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("獵叉", ({ "hunter pike", "pike" }));
    set_weight(8800);
    setup_pike(2, 10, 55, 1);

    if( !clonep() ) {
        set("wield_as", ({ "twohanded pike", "pike" }));
        set("unit", "把");
        set("value", 4800);
        set("rigidity", 25);
        set("long", "一把用於狩獵野獸的鐵叉，叉頭比長槍略窄，握起來輕便許多，是獵戶慣用的趁手兵器。\n");
        set("apply_weapon/pike", (["cor": 1, "intimidate": 10]));
        set("apply_weapon/twohanded pike", (["cor": 1, "intimidate": 10]));
    }
    setup();
}
