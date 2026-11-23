// /custom/wizroom/w/windstory/obj/lvcloth.c — 固定詞綴繡花布衣（windstory 自用）。
// 規則：docs/EMBROIDERY.md（鳳娘白甌的繡花）。
// 繼承繡花布衣（/obj/area/obj/embroidered_cloth），產生時直接當作「繡到詞綴」：
// 底子只有防禦力 +1，必定有前綴＋後綴，前綴從 太陽、無腸、焦僥、巫首 隨機抽一種，後綴從 風波、羅漢 隨機抽一種
// （使用者指示，2026-11-24；後綴加上羅漢，2026-11-24）。價值照規則是原價的 2.25 倍。
// 家園儲物箱存取沿用繡花布衣的 query_store_data／restore_store_data，取出時不會重擲。

inherit "/obj/area/obj/embroidered_cloth";

#define RESULT_AFFIX 6   // 與 embroidered_cloth.c 的「詞綴」結果代號相同
#define FIXED_PREFIX ({ "太陽", "無腸", "焦僥", "巫首" })
#define FIXED_SUFFIX ({ "風波", "羅漢" })

void create()
{
    string *pre = FIXED_PREFIX, *suf = FIXED_SUFFIX;

    ::create();
    if( clonep() ) {
        set("apply_armor/cloth", ([ "armor": 1 ]));
        set("cloth_base_apply", ([ "armor": 1 ]));
        set("embroidery_result", RESULT_AFFIX);
        ENHANCE_D->apply_cloth_affix(this_object(),
            ([ "prefix": pre[random(sizeof(pre))], "suffix": suf[random(sizeof(suf))] ]));
    }
}
