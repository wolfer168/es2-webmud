/*---
description: 巫師留言板，放在巫師公會（/adm/guild/guildhall）。巫師（immortal）以上可以張貼，容量 100 篇。
---*/
inherit BULLETIN_BOARD;

private void
create()
{
  set_name("巫師留言板", ({ "wizard board", "board" }));
  set("location", "/adm/guild/guildhall");
  set("board_id", "wizard");
  set("capacity", 100);
  set("post_wiz_level", 1);   // (immortal) 以上
  setup();
  set("long", "這是巫師公會的留言板，巫師們在這裡留下討論與交辦事項，約可容納一百篇留言。\n");
}

// 名稱後面顯示「Wizard Board」（預設只會把第一個字母大寫）。
string query_id() { return "Wizard Board"; }
