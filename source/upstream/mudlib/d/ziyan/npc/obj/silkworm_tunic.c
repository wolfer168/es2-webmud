/* 烏蠶寶衣 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("\x1b[1;35m烏蠶寶衣\x1b[m", ({ "silkworm tunic", "tunic" }));
    set_weight(1000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 30000);
        set("long",
            "聽說烏蠶寶衣本是西方大山玄女族所特產的烏蠶絲作成的寶衣,\n"
            "據說玄女族所製的烏蠶衣具有非常好的防禦效果。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "defense": 30,
            "wittiness": 50,
            "armor": 10,
        ]));
    }
    setup();
}
