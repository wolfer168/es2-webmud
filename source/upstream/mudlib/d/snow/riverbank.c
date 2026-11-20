// Room: /d/snow/riverbank.c

inherit ROOM;

void create()
{
	set("short", "河邊空地");
	set("long", @LONG
這裡是河邊的一處空地﹐湍急的河流從你的北邊往東南邊流去﹐離
這裡的河岸往北一丈多遠的地方可以看見一個水車﹐南邊則是一間破舊
的大宅院﹐牆壁上一個大缺口足足可以讓人通過。
LONG
	);
	set("outdoors", "snow");
	set("exits", ([ /* sizeof() == 1 */
		"south" : __DIR__"ruin2",
]));

    set("fishing", 1);
    set("detail/河水", "河水雖然湍急，近岸處卻有幾處迴水，水面下隱約有魚影逆流而上，在這裡垂釣 (fish) 或許能釣到幾尾。");
    setup();
	replace_program(ROOM);
	set("map/area", "雪亭鎮");
}
