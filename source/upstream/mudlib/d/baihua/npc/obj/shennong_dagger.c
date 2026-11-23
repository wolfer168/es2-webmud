/* 神農匕 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("神農匕", ({ "dagger" }));
    set_weight(2500);
    init_damage(1, 13, 40, 0, "dagger");
    init_damage(1, 13, 40, 0, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 75000);
        set("long",
            "據古文記, 炎帝黃帝乃同母異父兄弟, 各領一部落分占南北. 炎帝即是神農氏\n"
            ", 其遍嘗百草, 推行農耕之功, 結束遷徙無定的游牧生活, 影響至大. 此匕為\n"
            "先人感恩謹念而製, 刃身兩側燒上草花之紋, 曲線玲巧, 對採草取木似乎相當\n"
            "順手.\n");
        set("apply_weapon/dagger", ([
            "alchemy-medication": 10,
            "alchemy-wealth": 5,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "alchemy-medication": 10,
            "alchemy-wealth": 5,
        ]));
    }
    setup();
}
