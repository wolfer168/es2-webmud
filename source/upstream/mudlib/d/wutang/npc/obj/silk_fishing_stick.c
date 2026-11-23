/* 青絲釣竿 — ES2 參考資料（es2tips）。煙波釣叟替楊子陵報答，追風劍任務取得。
 * 英文與生鐵釣竿（fishing_stick.c）相同，照原資料保留。
 * crash（把河魚碾成魚餌）要等遊戲有河魚、魚餌後再做。 */
#include <ansi.h>
#include <weapon.h>

inherit F_WHIP;

void create()
{
    set_name("青絲釣竿", ({ "fishing stick", "stick", "whip" }));
    set_weight(6300);
    init_damage(3, 12, 100, 7, "whip");

    if( !clonep() ) {
        set("wield_as", "whip");
        set("unit", "支");
        set("value", 100000);
        set("long",
            "一支十分特別的釣魚竿，當然可以當鞭子用，不過魚竿後面還有一個小釘錘，好\n"
            "像可以用來把食物碾碎 ... (crash)\n");
        set("apply_weapon/whip", ([
            "halieutics": 10,
        ]));
    }
    setup();
}
