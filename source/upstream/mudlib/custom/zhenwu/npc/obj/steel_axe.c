/* 精鋼戰斧 — 米沛的替代武器（使用者指定，2026-11-23）。
 * 萬夫莫敵是唯一物品，還在世上被別人拿著時，米沛重生改拿這把（照蔚楓的寫法）。
 * 雙手持用：傷害 8 ～ 100，力氣加成上限 140（4 × 24 × 146 / 100）。
 * 擺放：只有振武軍營的米沛用到，放 custom/zhenwu/npc/obj/（docs/NPC_ITEM_PLACEMENT.md）。 */
#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("精鋼戰斧", ({ "steel axe", "axe" }));
    set_weight(12000);
    init_damage(4, 24, 146, 4, "twohanded axe");

    if( !clonep() ) {
        set("wield_as", "twohanded axe");
        set("unit", "把");
        set("value", 12000);
        set("long",
            "一把精鋼打造的戰斧，斧刃寬厚，柄上纏著防滑的牛皮，是振武軍將領\n"
            "慣用的兵刃。份量雖然不輕，在膂力過人的手裡卻揮灑自如。\n");
        set("apply_weapon/twohanded axe", ([
            "cor": 1,
            "str": 1,
            "berserk": 10,
        ]));
    }
    setup();
}
