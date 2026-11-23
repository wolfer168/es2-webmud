# NPC 與道具的擺放規則（使用者指示，2026-11-23）

NPC 與道具檔案**照它出現的位置、和誰帶著它來擺放**，比照雪亭鎮原本的做法：
`d/snow/npc/obj/` 放雪亭 NPC 身上、手上的東西——穿的布衣、拿的兵器、老太婆的拐杖、鐵匠賣的鏟子、交給玩家的英雄帖與紙條；
`d/snow/obj/` 放雪亭這個地方本身擺著的東西，例如廣場上的七彩石、鍋子，倉庫的木箱推車，火爐裡的木刀木劍。
以後新做的 NPC、道具也照這份規則放；搬動檔案時照最後的「搬家程序」。

## 名詞

- **區域**：`d/` 底下的一個地圖資料夾，例如 `d/snow`（雪亭鎮）、`d/qiaoyin`（喬陰縣）。
  文國縣 `d/swaylan` 底下的冷梅莊 `lunmay`、步玄派 `buxuan`、樹林 `forest`、大悲寺 `temple` 是**子區**，
  各有自己的 `npc/`、`npc/obj/`、`obj/`。自成一區的系統（振武軍營 `custom/zhenwu`、家園 `custom/home`）也算一個區域。
- **用到**：房間的 `objects` 放了它、NPC `carry_object` / `new` 它、NPC 的販賣清單有它、任務或對話會給它。
  **還沒放進地圖的舊站 NPC（`custom/legacy_npc/`）不算**：它們還不屬於任何區域。

## 資料夾一覽

| 資料夾 | 放什麼 |
|---|---|
| `d/<區域>/npc/` | 只在這個區域出現的 NPC |
| `d/<區域>/npc/obj/` | 這個區域的 NPC **經手的東西**：穿戴的裝備、拿的兵器、隨身物品、**販售的商品**（連同商品裡裝的酒水）、抽獎獎品、交給玩家的任務物品 |
| `d/<區域>/obj/` | **房間裡擺著、或從房間裡找到的東西**：七彩石、水井、西瓜、骨骸、墓裡的箱子、搜溪找到的金牌、衙門的石鑰匙 |
| `/d/npc/` | 兩個以上區域都有的一般 NPC（路人、官兵、野獸、看門的…） |
| `/d/npc/obj/` | 兩個以上區域的 NPC 都經手的東西（烤雞、魚餌、鹽、糖、牛皮背心、白布衣…） |
| `/d/npc/ghost/` | 鬼怪（共用的 `std_ghost.c` 也在這裡） |
| `/d/obj/` | 兩個以上區域的房間都擺著的東西（例如水井） |

判斷順序：一件道具**有擺在房間裡**（房間載入、或在房間裡搜出來）就放 `obj/`；**只經過 NPC 的手**（穿、拿、賣、給）就放 `npc/obj/`。
再看用到它的有幾個區域：一個區域放該區，兩個以上放 `/d/npc/obj/` 或 `/d/obj/`。

## NPC

| 情況 | 放哪裡 | 例子 |
|---|---|---|
| 只在一個區域出現 | `d/<區域>/npc/`（子區放子區的 `npc/`） | 舊站 NPC 放進八寶樓 → `d/baobao/npc/` |
| 兩個以上區域都有的一般 NPC | `/d/npc/` | 路人、官兵、護院武師、野狗、山羊、松鼠、石獅子 |
| 有特殊功能（販賣、收購、擺渡、解謎、任務、師父…） | **一律放所屬區域**；別的區域也要，就複製一份放在那個區域的 `npc/` | 小黃 → 紫煙鎮；藥鋪掌櫃雪亭、孟家莊各一份 |
| 鬼怪 | `/d/npc/ghost/` | 餓鬼、魑魅、倀鬼、遊魂、魍魎、枉死鬼 |
| 舊站 NPC 還沒放進地圖 | 留在 `custom/legacy_npc/` | 放進地圖那天就搬到該區 `npc/`，身上裝備搬到該區 `npc/obj/`（別區也有人穿就放 `/d/npc/obj/`） |
| 系統召喚、巫師測試用（不在任何地圖） | 留在原本的系統資料夾 | 法術召出的黃狗 `custom/taoism/npc/maoshan_dog` |

「所屬區域」以 NPC 的身份和主要所在為準，例如：青衣漢子是雪吟莊的人（雪吟莊大門、後花園、雪亭東橋都有他）→ `d/snowkeep/npc/`；
冷梅莊二代弟子、梅影風是冷梅莊的人 → `d/swaylan/lunmay/npc/`（五堂鎮涼亭、文國縣十字路口照樣載入同一個檔案）。

## 不搬的

- 原版共用物件庫 `/obj/`（`STOCK_WEAPON`、`STOCK_ARMOR` 的長劍布衣、書、錢、食物、丹藥）維持原位。
- 系統程式（技能、法術等）也會用到的道具留在系統資料夾，例如 `custom/item/scroll/` 的符紙。
- 自訂裝備庫 `custom/armor/`、`custom/weapon/` 裡**還沒被任何區域用到**的裝備留在裝備庫；一旦被區域用到，就照上面搬出去。

## 搬家程序（以後搬檔案也照這樣做）

1. 要搬的檔案裡用 `__DIR__` 寫的路徑先改成完整路徑（`__DIR__` 是「檔案所在的資料夾」，搬家後意思會變）。
2. 用 `git mv` 搬檔，再把所有寫到舊路徑的地方改成新路徑：房間、NPC、道具、`docs/`、`tests/`、`catalog/`。
3. 把「舊路徑 新路徑」加到 `source/upstream/mudlib/adm/etc/moved_paths` 最後面（舊的不要刪）。
   玩家私人儲物箱、自動載入的物品存的是物品檔路徑；取出時 `/adm/daemons/moved_pathd.c` 會照這張表換成新路徑，玩家的東西不會不見。
4. 測試要找搬走的檔案，用 `tests/placement.py` 的 `resolve()`、`current()`、`LibDir`（它們讀同一張對照表）。
5. 跑 `pytest tests/`、`python3 tools/check_big5_text.py`。

## 2026-11-23 這次搬了哪些

NPC 搬了 71 個檔案（含鬼怪共用的基底 std_ghost），另複製 1 個；道具 252 件，其中 251 件放 `npc/obj/`。
雪亭鎮 `d/snow/npc/obj/` 裡原本擺在房間的鍋子、髮簪、木箱、推車、木刀、木劍也移到 `d/snow/obj/`。
完整的舊、新路徑對照見 `source/upstream/mudlib/adm/etc/moved_paths`。

### NPC

**/d/baihua/npc/**

| NPC | 原位置 |
|---|---|
| 公孫志 `gong_sun_zhi` | `/custom/legacy_npc/gong_sun_zhi` |

**/d/baobao/npc/**

| NPC | 原位置 |
|---|---|
| 白魚 `bai_yu` | `/custom/legacy_npc/bai_yu` |
| 崇白虎 `chong_bai_hu` | `/custom/legacy_npc/chong_bai_hu` |
| 公孫微 `gong_sun_wei` | `/custom/legacy_npc/gong_sun_wei` |
| 馬鍾聖 `ma_zhong_shen` | `/custom/legacy_npc/ma_zhong_shen` |
| 歐陽芝 `o_yan_zhi` | `/custom/legacy_npc/o_yan_zhi` |
| 司馬雷 `si_ma_lei` | `/custom/legacy_npc/si_ma_lei` |
| 軒轅劍月 `xun_yuan_jian_yue` | `/custom/legacy_npc/xun_yuan_jian_yue` |

**/d/fengcheng/npc/**

| NPC | 原位置 |
|---|---|
| 東方孤冥 `dong_fang_gu_ming` | `/custom/legacy_npc/dong_fang_gu_ming` |
| 李儒 `li_ru` | `/custom/legacy_npc/li_ru` |
| 司馬蔚 `si_ma_wei` | `/custom/legacy_npc/si_ma_wei` |

**/d/graveyard/npc/**

| NPC | 原位置 |
|---|---|
| 野人酋長 `barbarian_chief` | `/custom/legacy_npc/barbarian_chief` |
| 青衣女郎 `lady` | `/custom/legacy_npc/lady` |
| 劉乙忘玄 `liuye_the_master_of_grimace` | `/custom/legacy_npc/liuye_the_master_of_grimace` |
| 吳長貴 `wu_changuei` | `/custom/legacy_npc/wu_changuei` |

**/d/kangping/npc/**

| NPC | 原位置 |
|---|---|
| 柳淳風 `liuh_chuen_fon` | `/custom/legacy_npc/liuh_chuen_fon` |
| 安懶道人 `old_taoist` | `/custom/legacy_npc/old_taoist` |
| 歐陽無極 `ou_yan_wu_ji_2` | `/custom/legacy_npc/ou_yan_wu_ji_2` |

**/d/lee/npc/**

| NPC | 原位置 |
|---|---|
| 杜風凌 `du_feng_ling` | `/custom/legacy_npc/du_feng_ling` |

**/d/mengjia/npc/**

| NPC | 原位置 |
|---|---|
| 花興 `hua_xing` | `/custom/legacy_npc/hua_xing` |
| 林正陽 `lin_zheng_yang` | `/custom/legacy_npc/lin_zheng_yang` |
| 孟驚鴻 `meng_jiang_hong` | `/custom/legacy_npc/meng_jiang_hong` |
| 田由 `tian_yu` | `/custom/legacy_npc/tian_yu` |

**/d/npc/**

| NPC | 原位置 |
|---|---|
| 官兵 `garrison` | `/obj/area/garrison` |
| 山羊 `goat` | `/d/oldpine/npc/goat` |
| 護院武師 `guard` | `/d/wutang/npc/guard` |
| 路人 `man` | `/obj/area/man` |
| 松鼠 `squirrel` | `/d/oldpine/npc/squirrel` |
| 石獅子 `stone_lion` | `/d/baihua/npc/stone_lion` |
| 野狗 `wild_dog` | `/d/qiaoyin/npc/wild_dog` |

**/d/npc/ghost/**

| NPC | 原位置 |
|---|---|
| 餓鬼 `hungry_ghost` | `/custom/ghost/npc/hungry_ghost` |
| 魑魅 `mountain_sprite` | `/custom/ghost/npc/mountain_sprite` |
| 鬼怪共用基底 `std_ghost` | `/custom/ghost/std_ghost` |
| 倀鬼 `tiger_thrall` | `/custom/ghost/npc/tiger_thrall` |
| 遊魂 `wandering_soul` | `/custom/ghost/npc/wandering_soul` |
| 魍魎 `water_goblin` | `/custom/ghost/npc/water_goblin` |
| 枉死鬼 `wronged_ghost` | `/custom/ghost/npc/wronged_ghost` |

**/d/oldpine/npc/**

| NPC | 原位置 |
|---|---|
| 過路客 `traveller` | `/obj/area/traveller` |

**/d/qiaoyin/npc/**

| NPC | 原位置 |
|---|---|
| 查思古禮 `chaxigol` | `/custom/legacy_npc/chaxigol` |
| 韓文緒 `han_wen_suei` | `/custom/legacy_npc/han_wen_suei` |
| 蕭朗生 `hsiao_lang_sheng` | `/custom/legacy_npc/hsiao_lang_sheng` |
| 柳東蘆 `liuh_don_lu` | `/custom/legacy_npc/liuh_don_lu` |
| 市井無賴 `vagabond` | `/obj/area/vagabond` |
| 無慾師太 `wu_yu_nun` | `/custom/legacy_npc/wu_yu_nun` |
| 陰雨巖 `yin_euyen` | `/custom/legacy_npc/yin_euyen` |

**/d/qiaoyin_east/npc/**

| NPC | 原位置 |
|---|---|
| 雷同 `lay_ton` | `/custom/legacy_npc/lay_ton` |
| 武道通 `wu_dauton` | `/custom/legacy_npc/wu_dauton` |

**/d/snow/npc/**

| NPC | 原位置 |
|---|---|
| 朱衣派弟子 `fire_taoist` | `/custom/taoism/npc/fire_taoist` |
| 素衣派弟子 `freeze_taoist` | `/custom/taoism/npc/freeze_taoist` |
| 玄衣派弟子 `storm_taoist` | `/custom/taoism/npc/storm_taoist` |
| 紫衣派弟子 `thunder_taoist` | `/custom/taoism/npc/thunder_taoist` |

**/d/snowkeep/npc/**

| NPC | 原位置 |
|---|---|
| 褚商魂 `chu_xang_when` | `/custom/legacy_npc/chu_xang_when` |
| 青衣漢子 `guard` | `/d/snow/npc/guard` |
| 許彥之 `hsu_yen_chih` | `/custom/legacy_npc/hsu_yen_chih` |
| 哭無望 `ku_wu_wang` | `/custom/legacy_npc/ku_wu_wang` |
| 佛心 `phoxin` | `/custom/legacy_npc/phoxin` |
| 於蘭兼毅 `yu_lan_jian_yi` | `/custom/legacy_npc/yu_lan_jian_yi` |
| 魚平胤 `yu_pingyin` | `/custom/legacy_npc/yu_pingyin` |
| 魚鐵山 `yu_tieshan` | `/custom/legacy_npc/yu_tieshan` |

**/d/swaylan/buxuan/npc/**

| NPC | 原位置 |
|---|---|
| 駱易 `ro_yi` | `/custom/legacy_npc/ro_yi` |

**/d/swaylan/lunmay/npc/**

| NPC | 原位置 |
|---|---|
| 冷梅莊二代弟子 `apprentice` | `/d/wutang/npc/apprentice` |
| 梅嵐武 `may_lan_wu` | `/custom/legacy_npc/may_lan_wu` |
| 梅影風 `may_yin_fong` | `/d/wutang/npc/may_yin_fong` |

**/d/swaylan/npc/**

| NPC | 原位置 |
|---|---|
| 黃天霸 `huang_tien_ba` | `/custom/legacy_npc/huang_tien_ba` |
| 高風 `kao_fon` | `/custom/legacy_npc/kao_fon` |

**/d/taiyi/npc/**

| NPC | 原位置 |
|---|---|
| 白齊 `taoist_leader` | `/custom/legacy_npc/taoist_leader` |

**/d/tianshan/npc/**

| NPC | 原位置 |
|---|---|
| 桃仙 `mountain_god` | `/custom/legacy_npc/mountain_god` |

**/d/ziyan/npc/**

| NPC | 原位置 |
|---|---|
| 程槐 `cheng_huai` | `/custom/legacy_npc/cheng_huai` |
| 小黃 `huang` | `/d/wutang/npc/huang` |
| 林育崙 `lin_yu_lun` | `/custom/legacy_npc/lin_yu_lun` |
| 趙弘春 `zhao_hong_chun` | `/custom/legacy_npc/zhao_hong_chun` |

**/d/mengjia/npc/**（複製）

| NPC | 來源 |
|---|---|
| 藥鋪掌櫃 `herbalist` | 複製 `/d/snow/npc/herbalist`（雪亭的不動） |

### 道具

**/d/baihua/npc/obj/**（9 件）

龍骨槍 `dragon_bone_pike`、神羊帽 `goat_hat`、血靈芝粉 `ling_tzi`、虹緞帶 `rainbow_ribbon`、鎖子甲 `ringmail`、神農匕 `shennong_dagger`、牧羊杖 `shepherd_cane`、辛木杖 `sinia_staff`、草鞋 `straw_boots`

**/d/baobao/npc/obj/**（12 件）

\x1b[1;35m怒天鞭\x1b[m `angry_whip`、\x1b[1;31m邪刀•焱靈\x1b[m `blade_of_fire_spirit`、\x1b[1;30m闇之寶靴\x1b[m `dark_boots`、\x1b[1;30m闇之護手\x1b[m `dark_bracers`、龍吟指環 `dragon_ring`、\x1b[1;36m百鬒寒鳩劍\x1b[m `hundreds_poison_sword`、\x1b[1;37m霸王鎧\x1b[m `royal_armor`、\x1b[1;37m霸王銅冠\x1b[m `royal_helmet`、\x1b[1;37m霸王槍\x1b[m `royal_pike`、七星道袍 `seven_star_robe`、精鋼護腕 `steel_bracers`、\x1b[1;37m虎嘯旭日鎧\x1b[m `tiger_plate`

**/d/fengcheng/npc/obj/**（5 件）

虛靈劍 `numinous_sword`、供品 `offering`、\x1b[1;35m紫雲盔\x1b[m `purple_helmet`、\x1b[1;37m洗銀劍\x1b[m `silver_sword`、精鋼長劍 `steel_longsword`

**/d/graveyard/npc/obj/**（9 件）

黑獄服 `black_suit`、白骨杖 `bone_staff`、黃銅禪杖 `brass_zenstaff`、黃銅佛珠 `copper_rosary`、鬼面 `ghost_mask`、百鬼腰束 `ghosts_girdle`、九曲十彎 `god_cane`、念珠 `rosary`、軟麻青絲衣 `soft_cloth`

**/d/kangping/npc/obj/**（4 件）

法胄 `magic_armor`、\x1b[1;34m藍水晶戒指\x1b[m `sapphire_ring`、黃雀寶劍 `sword_of_raven`、杏黃道袍 `tao_robe`

**/d/lee/npc/obj/**（12 件）

大冰糖葫蘆 `big_candied_hawthorn`、齊眉棍 `brow_staff`、冰糖葫蘆 `candied_hawthorn`、\x1b[1;37m水晶戒指\x1b[m `crystal_ring`、麵粉 `flour`、天靈清露 `heaven_dew`、麻布鞋 `hemp_boots`、獵叉 `hunter_pike`、皮靴 `leather_boots`、小藥瓶 `medicine_bottle`、緊身衣 `tight_cloth`、柳葉刀 `willow_blade`

**/d/mengjia/npc/obj/**（5 件）

蝴蝶短刺 `butterfly_stiletto`、古銅重劍 `copper_sword`、\x1b[1;37m伏魔法衣\x1b[m `exorcist_cassock`、風塵腿護 `red_dust_legs`、星雲腿護 `star_studded_legs`

**/d/npc/obj/**（57 件）

魚餌 `bait`、\x1b[1;30m黑斗笠\x1b[m `black_doli`、黑鋼短刃 `black_iron_dagger`、征衣「血染」 `blood_stained_cloth`、貓眼戒指 `chrysoberyl_ring`、皂步靴 `clothboot`、流雲靴 `cloud_boots`、粗布衣 `coarse_cloth`、青銅道冠 `copper_hat`、牛皮背心 `cowhide_vest`、武魁龍轉 `dragon_pill`、飛天靴 `flying_boots`、\x1b[1;33m封神靴\x1b[m `forgod_boots`、毛皮帽 `fur_hat`、百鬼刀 `ghosts_blade`、金羽神盔 `golden_feather_helm`、\x1b[1;33m金絲長袍\x1b[m `golden_robe`、翠綠短杉 `green_cloth`、青衣道袍 `green_robe`、\x1b[1;32m漢玉戒指\x1b[m `han_jade_ring`、銅盔 `helmet`、麻布衣 `hemp_cloth`、鋤頭 `hoe`、\x1b[1;33m鐵布衫\x1b[m `iron_cloth`、精鐵環扣 `iron_girth`、鐵盔 `iron_helmet`、硬皮甲冑 `leather_armor`、獅蠻帶 `lion_belt`、肉塊 `meat`、軟櫬甲 `padded_armor`、桃木劍 `peachwood_sword`、金剛念珠 `psakaml`、紫色道袍 `purple_taoist_robe`、連身鎖子甲 `ring_armor`、\x1b[1;37m霸王指環\x1b[m `ring_of_mighty_lord`、紅燒雞 `roast_chicken`、鹽 `salt`、肩鎧 `side_armor`、\x1b[1;37m天蠶寶衣\x1b[m `silk_cloth`、銀針 `silver_needle`、姊姊的信 `sister_letter`、打鐵褂子 `smock`、玄蛛皂白靴 `spider_boots`、精鋼戰甲 `steel_armor`、精鋼戰靴 `steel_boots`、精鋼砍刀 `steelblade`、糖 `sugar`、肚兜 `tummy_cover`、骨灰罈 `urn`、蛟龍帶 `water_dragon_girdle`、牛皮水袋 `waterskin`、白長袍 `white_cloth`、白綢羽衫 `white_dress`、\x1b[1;37m流雲清玉帶\x1b[m `white_jade_girth`、白色長衫 `white_scholar_dress`、黃玉戒指 `yellow_jade_ring`、禪杖 `zenstaff`

**/d/obj/**（1 件）

水井 `well`

**/d/oldpine/npc/obj/**（9 件）

\x1b[1;31m無相福田\x1b[m `animitta_kasaya`、頭巾 `head_cloth`、皮背心 `leather_vest`、烤鹿肉 `venison`、\x1b[1;35m紫紗衫\x1b[m `violet_cloth`、\x1b[1;35m紫玉釵\x1b[m `violet_hairpin`、\x1b[1;35m紫紗靴\x1b[m `violet_shoes`、\x1b[1;35m紫雲玉珮\x1b[m `voliet_jade`、\x1b[1;36m枯禪杖\x1b[m `wither_zenstaff`

**/d/qiaoyin/npc/obj/**（17 件）

步軍戰鎧 `battle_armor`、步軍戰盔 `battle_helm`、\x1b[1;30m玄蘇劍\x1b[m `blackthorn`、青布官服 `cyan_cloth`、\x1b[1;33m金絲拂塵\x1b[m `golden_buddha_duster`、火鱗靴 `red_scale_boots`、火鱗衣 `red_scale_cloth`、火鱗腰帶 `red_scale_girth`、火鱗手套 `red_scale_gloves`、火鱗盔 `red_scale_helm`、火鱗脛甲 `red_scale_leggings`、火鱗胸鎧 `red_scale_plate`、\x1b[1;37m纏蛇護手\x1b[m `snake_bracers`、烏讎劍 `sword_of_black_justice`、\x1b[1;35m紫電紅纓槍\x1b[m `thunder_pike`、\x1b[1;33m虎首盔\x1b[m `tiger_helmet`、\x1b[1;37m白馬盔\x1b[m `white_helmet`

**/d/qiaoyin_east/npc/obj/**（7 件）

蜂尾針 `bee_needle`、\x1b[1;37m塵不沾\x1b[m `boots_of_cleanse`、青色道袍 `cyan_taoist_robe`、透骨釘 `iron_needle`、\x1b[1;30m附骨之蛆\x1b[m `needle_of_bone_maggot`、影匕 `shadow_dagger`、\x1b[0;33m虎紋戒指\x1b[m `tiger_ring`

**/d/shuiyue/npc/obj/**（3 件）

\x1b[0;35m古劍醒塵\x1b[m `au_han_sword`、大饅頭 `big_manto`、巨劍 `colosus_sword`

**/d/snow/npc/obj/**（1 件）

大刀 `large_blade`

**/d/snowkeep/npc/obj/**（24 件）

青竹腿護 `bamboo_legs`、蛟骨刀 `blade_of_hydra_bone`、黃呢鐵帽 `brass_hat`、黃銅鑰匙 `brass_key`、移殤杖 `change_cane`、寒鐵匕首 `cool_iron_dagger`、\x1b[1;30m闇之絲甲\x1b[m `dark_armor`、\x1b[1;31m怒龍錦冑\x1b[m `dragon_armor`、真元戰袍 `force_cloth`、金線僧袍 `gold_robe`、金絲八卦刀 `golden_blade`、掩心甲 `heart_armor`、護心鏡 `heart_plate`、雛鐵劍 `ironsword`、鑲珠束腰 `perl_girth`、\x1b[1;36m紫雲戰甲\x1b[m `purple_cloud_mail`、\x1b[1;33m巨龍指環\x1b[m `ring_of_mighty_dragon`、暗默珠 `silance_rosary`、\x1b[0;33m鹿皮手套\x1b[m `skin_gloves`、烈陽護膝 `sun_legs`、\x1b[1;37m長刀僉白\x1b[m `white_blade`、\x1b[1;37m素虹軟甲\x1b[m `white_rainbow_armor`、\x1b[1;34m「雨毒」\x1b[m `wicked_dagger`、舊長袍 `worn_robe`

**/d/swaylan/buxuan/npc/obj/**（5 件）

\x1b[1;30m玄晦戰甲\x1b[m `black_harness`、\x1b[1;36m落雲刃\x1b[m `cloudslay_sword`、紫紗逍遙巾 `headgear`、\x1b[0;32m青蟒靴\x1b[m `snakeskin_boots`、風泉之劍 `sword_of_wind_spring`

**/d/swaylan/forest/npc/obj/**（7 件）

璧玉甲 `bi_jade_armor`、玄玉墜 `black_jade_pendant`、\x1b[1;36m龍鱗璧玉袍\x1b[m `dragon_jade_robe`、\x1b[1;34m青龍\x1b[1;37m白虎斧\x1b[m `dragon_tiger_axe`、翠玉甲 `jade_armor`、厚柄斧 `large_axe`、\x1b[1;37m雙鬢鋏\x1b[m `needle_sword`

**/d/swaylan/lunmay/npc/obj/**（11 件）

\x1b[1;37m奔雲靴\x1b[m `boots_of_flying_cloud`、鎖鏈背心 `chain_shirt`、\x1b[1;37m冰雪匕\x1b[m `dagger_of_frost_edge`、珍珠指環 `pearl_ring`、\x1b[1;37m銀彎束腰\x1b[m `silver_girth`、\x1b[1;37m銀霜鎧\x1b[m `silver_platemail_of_frost`、\x1b[1;37m寒霜劍\x1b[m `sword_of_frost_edge`、繭綢長袍 `umber_robe`、\x1b[1;37m白玉腰帶\x1b[m `white_girth`、\x1b[1;37m白玉戒指\x1b[m `white_ring`、\x1b[1;37m梅花白襖\x1b[m `white_robe`

**/d/swaylan/npc/obj/**（12 件）

\x1b[1;36m九環霸王刀\x1b[m `blade_of_nine_rings`、菊花露 `chrysanthemum_dew`、菊花露袋 `chrysanthemum_skin`、甜菊花釀 `chrysanthemum_wine`、釣竿 `fishing_stick`、黃金指環 `golden_ring`、巨斧 `huge_axe`、銀絲麵 `noodle`、鎖子鎧 `ring_mail`、鑲釘皮鎧 `studded_armor`、虎鳴槍 `tiger_pike`、甜菊花釀 `white_wine`

**/d/swaylan/temple/npc/obj/**（2 件）

大悲法衣 `dabei_robe`、念珠 `rosary`

**/d/taiyi/npc/obj/**（2 件）

黑布鞋 `black_cloth_boots`、\x1b[1;33m少眉劍\x1b[m `shome_sword`

**/d/tianshan/npc/obj/**（1 件）

天山野蔘鬚 `senxu`

**/d/wutang/npc/obj/**（24 件）

竹釣竿 `bamboo_fishing_rod`、黑醬色馬褂 `black_mandarin_jacket`、黑劍 `black_sword`、青布衣 `blue_cloth`、盤龍針 `dragon_needle`、飲血 `drinkblood`、繡花旗袍 `embroidery_dress`、\x1b[1;36m魚腸\x1b[m `fishy_sword`、鑲玉短劍 `jeweled_shortsword`、餡餅 `pie`、淡紅女衫 `pink_dress`、鮮紅道冠 `red_hat`、鮮紅道袍 `red_robe`、小紅巾 `red_scarf`、\x1b[1;31m血月短斧\x1b[m `short_axe_of_bloodmoon`、青絲釣竿 `silk_fishing_stick`、\x1b[1;32m谷玉\x1b[m `staff_of_wisdom`、簑衣 `straw_cloth`、\x1b[1;31m咒劍紅羽\x1b[m `sword_of_redrune`、戰神劈天刀 `warlord_blade`、寒玉戒指 `white_jade_ring`、純白道袍 `white_taoist_robe`、狼皮靴 `wolf_boots`、狼皮帽 `woof_hat`

**/d/ziyan/npc/obj/**（13 件）

白干 `baijiu`、\x1b[1;37m闇雲雙刃斧\x1b[m `blackcloud_axe`、鐵佛珠 `iron_rosary`、桑柿汁 `juice`、縣令官印 `magistrate_seal`、\x1b[1;37m偃月刀\x1b[m `moon_blade`、豬心 `pig_heart`、密函 `secret_letter`、\x1b[1;35m烏蠶寶衣\x1b[m `silkworm_tunic`、鋼戰甲 `steel_chain_armor`、果汁瓶 `vase`、白干酒 `white_wine`、\x1b[1;35m驂龍翔\x1b[m `wyvern_axe`
