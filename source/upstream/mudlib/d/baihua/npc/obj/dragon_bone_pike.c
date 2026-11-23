/* 龍骨槍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("龍骨槍", ({ "dragon_bone pike", "pike" }));
    set_weight(18500);
    init_damage(4, 16, 150, 4, "twohanded pike");

    if( !clonep() ) {
        set("wield_as", "twohanded pike");
        set("unit", "把");
        set("value", 15000);
        set("long",
            "一把精鋼鍊製的長槍, 色泛淺黃, 槍頭尖硬, 據聞鍊製時加入了龍骨, 揮舞起\n"
            "來有如龍騰飛耀, 發出壑壑聲響, 聲勢奪人.\n");
        set("apply_weapon/twohanded pike", ([
            "force": 10,
            "str": 3,
        ]));
    }
    setup();
}
