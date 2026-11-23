// /custom/wizroom/w/windstory/obj/shortsword.c — 固定詞綴短劍（windstory 自用）。
// 規則：docs/WEAPON_AFFIX.md（武器附加屬性）。
// 繼承原本的短劍（/obj/area/obj/shortsword），傷害、重量、ID、外觀都照原版；
// 只把擲詞綴換成：必定有前綴＋後綴，前綴從 太陽、無腸、焦僥、巫首 隨機抽一種，後綴從 風波、羅漢 隨機抽一種
// （使用者指示，2026-11-24；後綴加上羅漢，2026-11-24）。價值照規則是原價的 2.25 倍。
// 家園儲物箱取出時由儲物箱照存的 affix 還原，不會重擲。

inherit "/obj/area/obj/shortsword";

#define FIXED_PREFIX ({ "太陽", "無腸", "焦僥", "巫首" })
#define FIXED_SUFFIX ({ "風波", "羅漢" })

void create()
{
    string *pre = FIXED_PREFIX, *suf = FIXED_SUFFIX;

    ::create();
    if( clonep() )
        ENHANCE_D->apply_affix(this_object(),
            ([ "prefix": pre[random(sizeof(pre))], "suffix": suf[random(sizeof(suf))] ]));
}
