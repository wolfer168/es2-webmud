/*---
description: 白甌繡過的太古塵包：沿用太古塵包（ancient_bag.c）的一切設定，多了籤牌題名的功能。
design: docs/EMBROIDERY.md 第七節（使用者指示，2026-11-24）
rule: - 由白甌（d/wutang/npc/bai_ou.c）收下太古塵包後產生的新物件；名稱、ID、容量、重量、價值都不變。
      - 題名功能（set bag name）與儲物箱存取寫在 bag_plus.h。
      - 記號 bag_embroidered：白甌不再收（「這我已經改過了」）。
---*/

inherit "/custom/item/ancient_bag";

#include "/custom/item/bag_plus.h"

void create()
{
    seteuid(getuid());
    ::create();
    if( !clonep() ) {
        set("bag_embroidered", 1);
        set("base_long", query("long"));
        set("long", query("base_long") + SIGN_EMPTY);
    }
}
