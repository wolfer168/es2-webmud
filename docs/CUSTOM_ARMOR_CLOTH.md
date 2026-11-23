# 衣服類護具（custom/armor/cloth）

依使用者提供的 ES2 原始護具資料（Big5 文字檔，共 65 件）製作。名稱、顏色碼、敘述與護具特性照原資料；
所屬 NPC 與放置位置另行設定。

## 規則

- **穿戴位置**：全部穿在「衣服（cloth）」位置，可以和「鎧甲（armor）」位置同時穿。
- **指令名稱**：英文全名或英文最後一個字都可以指定，例如 `wear white robe`、`wear robe`。
- **重量**（依材質，穿戴沒有膂力限制）：絲、紗 1000；一般布衣、道袍、長袍 2000；
  皮、毛、鱗 4000；金屬（鐵布衫、殘鐵衣、金線僧袍、內縫金屬絲網的灰袍）6000。
- **價值**：原資料有紀錄的照紀錄；沒有的依強度分級，在範圍內取一次固定：
  - 普通（防禦力低、沒有其他特性）：10～50 兩
  - 中等：100～300 兩
  - 珍品（六靈玄衣、烏蠶寶衣、金線僧袍、水慾羽衣、天之哀思、天龍鱗）：依重量越重越貴，
    絲 300～450、布 450～600、皮鱗 600～800、金屬 800～1000 兩
- **咒文能力**：即法力（`query_ability("spell")` = 靈性 × 慧根 / 10 + 神 / 32 + 額外附加）的額外附加，
  代碼 `spell`。`identify` 顯示為「咒文能力」。
- **遊戲中尚未實作的技能**：代碼與中文名稱依 `docs/SKILL_NAMES.md`（已登記到 `data/chinese.o`），
  技能做出來後沿用同一代碼即生效：大悲咒 `compassion`、善想禪要 `absorption`、
  茅山幻術 `taoism of nature`、天師道法【桃山密籙】 `taoism of conviction`、
  幽冥三箭 `taoism of purify`、天師道法【素雲書】 `taoism-cloud`。
- **闇之絲衣**：原資料「職業限制：盜賊」，只有盜賊能穿。
- **西巫袍**：敘述提到其他種族穿起來不便，依使用者指定不另加限制。
- **皮背心**：原資料有兩件同名；防禦力 7 的改名為「牛皮背心」（`cowhide_vest.c`）。
- **沿用或修改既有物品**：白綢羽衫沿用 `d/npc/obj/white_dress.c`（數值相同）；
  緊身衣改寫 `d/lee/npc/obj/tight_cloth.c` 的敘述與特性（防禦能力值 5、防禦力 4）。
- **黑龍戰袍**：原資料沒有敘述，依使用者提供：「墨黑的綢緞繡上黑龍麟作為裝飾，具有相當的殺傷力與保護效果。」
- **只做物品**：六靈玄衣（五陵客棧解謎）、天之哀思（冥靈子換物）的取得劇情另行製作。
- **沒有唯一裝備**。

## 一覽

| 名稱 | 檔案 | 英文 | 重量 | 價值（兩） | 價值來源 |
|---|---|---|---|---|---|
| 無相福田 | `animitta_kasaya.c` | animitta kasaya | 2000 | 450 | 原資料 |
| 墨色布衣 | `black_cloth.c` | black cloth | 2000 | 80 | 原資料 |
| 黑龍戰袍 | `black_dragon_dress.c` | black-dragon dress | 2000 | 300 | 中等 |
| 黑醬色馬褂 | `black_mandarin_jacket.c` | black robe | 2000 | 15 | 普通 |
| 黑袍 | `black_robe.c` | black robe | 2000 | 250 | 中等 |
| 黑獄服 | `black_suit.c` | black suit | 2000 | 100 | 中等 |
| 浴血戰袍 | `blood_cloth.c` | blood cloth | 2000 | 150 | 原資料 |
| 征衣「血染」 | `blood_stained_cloth.c` | blood cloth | 2000 | 1000 | 原資料 |
| 藍鏤衣 | `blue_dress.c` | blue dress | 2000 | 300 | 中等 |
| 殘鐵衣 | `broken_iron_cloth.c` | broken iron cloth | 6000 | 50 | 原資料 |
| 仙符鏽袍 | `charm_robe.c` | charm robe | 2000 | 300 | 中等 |
| 天之哀思 | `cloth_of_sorrow.c` | cloth of sorrow | 2000 | 450 | 珍品 |
| 雲羅絲衣 | `cloudy_silk_cloth.c` | cloudy silk cloth | 1000 | 300 | 中等 |
| 牛皮背心 | `cowhide_vest.c` | leather vest | 4000 | 150 | 中等 |
| 鱷神戰袍 | `crocodile_dress.c` | crocodile dress | 4000 | 300 | 原資料 |
| 闇之絲衣 | `dark_cloth.c` | dark cloth | 1000 | 200 | 中等 |
| 水慾羽衣 | `devilish_dress.c` | devilish dress | 1000 | 400 | 珍品 |
| 蟠龍朝服 | `dragon_cloth.c` | dragon cloth | 2000 | 200 | 原資料 |
| 繡花旗袍 | `embroidery_dress.c` | embroidery dress | 2000 | 200 | 中等 |
| 伏魔法衣 | `exorcist_cassock.c` | exorcist cassock | 2000 | 250 | 中等 |
| 雷火天狼罩 | `fire_wolf_cloak.c` | fire-wolf cloak | 2000 | 100 | 原資料 |
| 焚羽護衣 | `firewu_cloth.c` | firewu cloth | 4000 | 5 | 原資料 |
| 真元戰袍 | `force_cloth.c` | force cloth | 2000 | 30 | 原資料 |
| 獸皮圍裙 | `fur_sarong.c` | fur sarong | 4000 | 250 | 中等 |
| 金線僧袍 | `gold_robe.c` | gold robe | 6000 | 850 | 珍品 |
| 金絲長袍 | `golden_robe.c` | golden robe | 2000 | 158 | 原資料 |
| 灰袍 | `gray_robe.c` | gray robe | 6000 | 250 | 原資料 |
| 灰衣道袍 | `gray_taoist_robe.c` | gray robe | 2000 | 10 | 普通 |
| 青衣道袍 | `green_robe.c` | green robe | 2000 | 40 | 普通 |
| 青綠軍袍 | `green_suit.c` | green suit | 2000 | 300 | 中等 |
| 鐵布衫 | `iron_cloth.c` | iron cloth | 6000 | 95 | 原資料 |
| 陰判官袍 | `judge_robe.c` | judge robe | 2000 | 300 | 原資料 |
| 皮背心 | `leather_vest.c` | leather vest | 4000 | 10 | 普通 |
| 西巫袍 | `malik_robe.c` | malik robe | 2000 | 50 | 原資料 |
| 六靈玄衣 | `omega_dress.c` | omega dress | 4000 | 750 | 珍品 |
| 淡紅女衫 | `pink_dress.c` | pink dress | 2000 | 50 | 普通 |
| 紫色道袍 | `purple_taoist_robe.c` | robe | 2000 | 35 | 普通 |
| 天龍鱗 | `rain_dragon_skin.c` | rain dragon skin | 4000 | 650 | 珍品 |
| 霓虹采裳 | `rainbow_gown.c` | rainbow gown | 1000 | 250 | 中等 |
| 紅色武道衣 | `red_cloth.c` | red cloth | 2000 | 30 | 普通 |
| 鮮紅道袍 | `red_robe.c` | red robe | 2000 | 8 | 原資料 |
| 火鱗衣 | `red_scale_cloth.c` | red_scale cloth | 4000 | 200 | 原資料 |
| 七星道袍 | `seven_star_robe.c` | seven star robe | 1000 | 100 | 原資料 |
| 天蠶寶衣 | `silk_cloth.c` | silk cloth | 1000 | 150 | 中等 |
| 烏蠶寶衣 | `silkworm_tunic.c` | silkworm tunic | 1000 | 300 | 珍品 |
| 銀絲戰袍 | `silver_cloth.c` | silver cloth | 1000 | 20 | 原資料 |
| 天地雲衫 | `sky_earth_cloth.c` | sky_earth cloth | 2000 | 500 | 原資料 |
| 軟麻青絲衣 | `soft_cloth.c` | soft cloth | 2000 | 15 | 原資料 |
| 簑衣 | `straw_cloth.c` | cloth | 2000 | 1.2 | 原資料 |
| 杏黃道袍 | `tao_robe.c` | tao robe | 2000 | 30 | 原資料 |
| 道袍 | `taoist_robe.c` | robe | 2000 | 300 | 中等 |
| 絲綢小服 | `tender_cloth.c` | tender cloth | 1000 | 30 | 原資料 |
| 斑斕虎氅 | `tiger_coat.c` | tiger coat | 4000 | 200 | 原資料 |
| 虎皮長袍 | `tigerish_robe.c` | tigerish robe | 4000 | 35 | 原資料 |
| 窮奇皮 | `tigerish_skin.c` | tigerish skin | 4000 | 20 | 原資料 |
| 紫紗衫 | `violet_cloth.c` | violet cloth | 1000 | 100 | 中等 |
| 白長袍 | `white_cloth.c` | white cloth | 1000 | 100 | 中等 |
| 梅花白襖 | `white_robe.c` | white robe | 1000 | 190 | 原資料 |
| 白色長衫 | `white_scholar_dress.c` | white dress | 2000 | 40 | 普通 |
| 純白道袍 | `white_taoist_robe.c` | white robe | 2000 | 10 | 普通 |
| 虎紋黃衣 | `yellow_and_black_cloth.c` | yellow and black cloth | 1000 | 100 | 中等 |
| 黃綢汗衫 | `yellow_cloth.c` | yellow cloth | 1000 | 45 | 普通 |
| 黃短衫 | `yellow_suit.c` | yellow suit | 2000 | 45 | 普通 |
