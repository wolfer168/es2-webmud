// /d/npc/obj/sister_letter.c — 老婦人（老王妻子的姊姊）寫給妹夫的信（穹槍訣任務）。

inherit ITEM;

void create()
{
    set_name("姊姊的信", ({ "sister letter", "letter to wang", "letter_to_wang", "letter" }));
    set_weight(1);
    if( !clonep() ) {
        set("unit", "封");
        set("value", 0);
        set("long", @LONG
一封簡短的信，字跡潦草，上面寫著：

妹夫見啟

    吾妹牙疼乃舉村皆知，唯新婚期間言歡不言苦，故隱而未言。人生短短數
十載，實苦多樂少。生亦何歡，死亦何苦。吾妹之事，或為天意，盼節哀順變。

                                                姊筆
LONG
        );
    }
    setup();
}
