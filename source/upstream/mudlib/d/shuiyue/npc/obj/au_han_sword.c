/* 古劍醒塵 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一把；NPC 重生時
// 若它還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_SWORD;

void create()
{
    set_name("\x1b[0;35m古劍醒塵\x1b[m", ({ "au-han sword", "sword" }));
    set_weight(9400);
    init_damage(3, 20, 150, 5, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 65000);
        set("long",
            "此劍乃上古時代所煉鑄之神兵利器。玄陽真人雲遊諸神之地, 忽見到一寒池中\n"
            "隱閃紫光, 於是潛入探查, 竟發現一塊渾然天成的劍形紫晶, 便將之帶回居所\n"
            ", 苦尋神劍煉法, 耗盡三十年精力與心血, 最後亦以自身鮮血, 賦予此劍純正\n"
            "靈氣, 並將此劍插於清虛峰頂七七四十九天, 吸取日陽月華的至陰至陽。玄陽\n"
            "鑄此劍時立下大願, 要以此劍醒濁塵，故此劍名曰「醒塵」。\n");
        set("apply_weapon/sword", ([
            "cor": 2,
            "cps": 2,
            "attack": 30,
        ]));
    }
    setup();
}
