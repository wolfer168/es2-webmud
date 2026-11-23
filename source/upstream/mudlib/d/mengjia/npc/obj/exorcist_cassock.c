/* 伏魔法衣 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("\x1b[1;37m伏魔法衣\x1b[m", ({ "exorcist cassock", "cassock" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 25000);
        set("long",
            "一件用粗布縫製的法衣，上面用血書了一堆稀奇古怪的咒符。這些咒符的意義已經失傳\n"
            "，但穿過這件法衣的人都可以感受到這些咒符所散發出的強大法力。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 5,
            "wis": 1,
            "spell": 15,
        ]));
    }
    setup();
}
