# 戒指與腰帶（custom/armor/finger、custom/armor/waist）

依使用者提供的 ES2 原始護具資料（Big5 文字檔）製作：戒指 42 筆（霸王指環重複一次，實際 41 件）、腰帶 20 件。
名稱、顏色碼、敘述與護具特性照原資料；所屬 NPC 與放置位置另行設定。

## 規則

- **穿戴位置**：戒指穿在 `finger_eq`、腰帶（含玉珮、尾巴）穿在 `waist_eq`，各只能戴一件。
- **指令名稱**：戒指為英文全名或 `ring`；腰帶為英文全名或主詞（`X of Y` 取 X，否則取最後一字，例如 `girth`、`belt`、`girdle`、`jade`、`tail`）。
- **重量**（穿戴沒有膂力限制）：戒指一般 100、敘述寫「沉重」的霸王指環與巨龍指環 300、暴龍尾骨 500；
  腰帶布、絲、銀絲 300，皮、玉、珠、鐵 800，尾巴 1000。
- **價值**：原資料有紀錄的照紀錄。沒有紀錄的：
  - 戒指：600～1500 兩，依附加屬性多寡與稀有度判斷。
  - 腰帶：比照衣服分級（普通 ≤50、中等 100～300、珍品依重量越重越貴：300 → 300～500、800 → 500～750、1000 → 750～1000 兩）。
- **唯一性**（`F_UNIQUE`）：虎紋戒指、白玉腰帶、紫雲玉珮。世上已經有一件時，NPC 重生不會拿到，也沒有替代品。
- **穿戴限制**（職業縮寫 sr=soldier、fr=fighter、tf=thief、tt=taoist、at=alchemist、bn=monk）：
  霸王指環、霸王腰帶（原註 sr only）限軍人；巨龍指環限武者；七幻寶戒限道士；形天之怒限形天族。
- **改名與新名稱**：兩件同名的「珍珠指環」都做；靈性 1、悟性 2 的那件改名「青金指環」（藍色，`lapis ring`）。
  「太乙七絕　戒」照原資料保留中間的全形空白。
- **封印冰環 clutch**（`daemon/condition/rain_blessing.c`）：身上帶著封印冰環時 `clutch ring` 或 `clutch freeze ring`。
  - 咒文能力（`apply/spell`）增加 慧根 + random(咒術 / 20)，持續 慧根 個 tick（1 tick = 2 秒）。
  - 冷卻 60 tick，從祝禱那一刻起算（記在玩家資料 `rain_blessing_cd`，重新登入不會重置）。
  - 訊息：使用「你受到雨神祝福，感覺體內靈力暴增。」；作用中再用「雨神的祝福依然庇蔭著你。」；
    結束「你心神一怔，似乎有些神力消散了。」；冷卻中「你持續喃喃祝禱，但似乎沒有任何感應。」
- **沿用既有物品**：水晶戒指改寫李家村 `d/lee/npc/obj/crystal_ring.c`（聶晟身上那枚），敘述、顏色與特性依原資料
  （防禦力 1、靈性 1、根骨 1），價值與重量維持原值。
- **只做物品**：星光指環（四神印記重塑天賦）先不做功能；星光指環、鑲玉指環、龍戒、冥思指環、藍水晶戒指、
  封龍鎖、龍吟指環、相思環、寒梅玉珮、形天之怒等的取得劇情另行製作。

## 戒指

| 名稱 | 檔案 | 英文 | 重量 | 價值（兩） | 價值來源 | 備註 |
|---|---|---|---|---|---|---|
| 修羅戒 | `finger/ashura_ring.c` | ashura ring | 100 | 800 | 依屬性與稀有度 |  |
| 獸面玉戒 | `finger/beast_ring.c` | beast ring | 100 | 50 | 原資料 |  |
| 血玉戒指 | `finger/bloodjade_ring.c` | bloodjade ring | 100 | 500 | 原資料 |  |
| 淨身戒 | `finger/clear_ring.c` | clear ring | 100 | 500 | 原資料 |  |
| 闇之魔戒 | `finger/dark_ring.c` | dark ring | 100 | 1300 | 依屬性與稀有度 |  |
| 龍吟指環 | `finger/dragon_ring.c` | dragon ring | 100 | 800 | 依屬性與稀有度 |  |
| 龍戒 | `finger/dragon_soul_ring.c` | dragon-soul ring | 100 | 1000 | 依屬性與稀有度 |  |
| 暴龍尾骨 | `finger/dragon_tail_ring.c` | dragon tail | 500 | 1 | 原資料 |  |
| 手指虎 | `finger/finger_ring.c` | finger ring | 100 | 650 | 依屬性與稀有度 |  |
| 封印冰環 | `finger/freeze_ring.c` | freeze ring | 100 | 1400 | 依屬性與稀有度 | clutch |
| 寒蟾指環 | `finger/frost_frog_ring.c` | frost frog ring | 100 | 200 | 原資料 |  |
| 黃金戒 | `finger/gold_ring.c` | gold ring | 100 | 700 | 依屬性與稀有度 |  |
| 黃金指環 | `finger/golden_ring.c` | golden ring | 100 | 70 | 原資料 |  |
| 漢玉戒指 | `finger/han_jade_ring.c` | jade ring | 100 | 400 | 原資料 |  |
| 鑲玉指環 | `finger/jade_ring.c` | jade ring | 100 | 650 | 依屬性與稀有度 |  |
| 青金指環 | `finger/lapis_ring.c` | lapis ring | 100 | 900 | 依屬性與稀有度 |  |
| 豹耳襄王戒 | `finger/leopard_ring.c` | leopard ring | 100 | 850 | 依屬性與稀有度 |  |
| 雷光指環 | `finger/lightning_ring.c` | lightning ring | 100 | 900 | 依屬性與稀有度 |  |
| 七幻寶戒 | `finger/magicians_ring.c` | magician's ring | 100 | 1000 | 依屬性與稀有度 | 限道士 |
| 冥思指環 | `finger/meditation_ring.c` | meditation ring | 100 | 500 | 原資料 |  |
| 珍珠指環 | `finger/pearl_ring.c` | pearl ring | 100 | 750 | 依屬性與稀有度 |  |
| 天龍珠 | `finger/rain_dragon_ring.c` | rain dragon ring | 100 | 1500 | 依屬性與稀有度 |  |
| 巨龍指環 | `finger/ring_of_mighty_dragon.c` | ring of mighty dragon | 300 | 900 | 依屬性與稀有度 | 限武者 |
| 霸王指環 | `finger/ring_of_mighty_lord.c` | ring of mighty lord | 300 | 200 | 原資料 | 限軍人 |
| 潤神幻戒 | `finger/ring_of_summon.c` | ring of summon | 100 | 1500 | 依屬性與稀有度 |  |
| 相思環 | `finger/romantic_ring.c` | romantic ring | 100 | 700 | 依屬性與稀有度 |  |
| 藍水晶戒指 | `finger/sapphire_ring.c` | sapphire ring | 100 | 700 | 依屬性與稀有度 |  |
| 封龍鎖 | `finger/sealed_dragon_ring.c` | sealed-dragon ring | 100 | 1000 | 依屬性與稀有度 |  |
| 旋芒戒 | `finger/sparkling_ring.c` | sparkling ring | 100 | 60 | 原資料 |  |
| 星光指環 | `finger/star_ring.c` | star ring | 100 | 1500 | 依屬性與稀有度 |  |
| 邪骨指環 | `finger/symbol_of_dao.c` | symbol of dao | 100 | 900 | 依屬性與稀有度 |  |
| 茅山信物 | `finger/symbol_of_mao_shan.c` | symbol of mao-shan | 100 | 800 | 依屬性與稀有度 |  |
| 封印雷環 | `finger/thunder_ring.c` | thunder ring | 100 | 1000 | 依屬性與稀有度 |  |
| 虎紋戒指 | `finger/tiger_ring.c` | tiger ring | 100 | 1200 | 依屬性與稀有度 | 唯一 |
| 黃玉指環 | `finger/topaz_symbol.c` | topaz symbol | 100 | 600 | 依屬性與稀有度 |  |
| 寒玉戒指 | `finger/white_jade_ring.c` | white ring | 100 | 600 | 依屬性與稀有度 |  |
| 白玉戒指 | `finger/white_ring.c` | white ring | 100 | 250 | 原資料 |  |
| 舞璃戒指 | `finger/wuzin_ring.c` | wuzin ring | 100 | 600 | 依屬性與稀有度 |  |
| 太乙七絕　戒 | `finger/yimo_ring.c` | yimo ring | 100 | 900 | 依屬性與稀有度 |  |

## 腰帶

| 名稱 | 檔案 | 英文 | 重量 | 價值（兩） | 價值來源 | 備註 |
|---|---|---|---|---|---|---|
| 萬福寶玉 | `waist/blessed_jade.c` | blessed jade | 800 | 100 | 原資料 |  |
| 雍和尾 | `waist/brutal_beasts_tail.c` | brutal beast's tail | 1000 | 1000 | 珍品 |  |
| 鱷神束帶 | `waist/crocodile_girth.c` | crocodile girth | 800 | 100 | 原資料 |  |
| 獒尾帶 | `waist/dog_tail_belt.c` | dog tail belt | 1000 | 100 | 中等 |  |
| 靈惑之尾 | `waist/dragon_tail.c` | dragon tail | 1000 | 1000 | 珍品 |  |
| 百鬼腰束 | `waist/ghosts_girdle.c` | ghosts girdle | 300 | 200 | 中等 |  |
| 形天之怒 | `waist/girdle_of_headless.c` | girdle of headless | 800 | 700 | 珍品 | 限形天族 |
| 霸王腰帶 | `waist/girdle_of_mighty_lord.c` | girdle of mighty lord | 300 | 250 | 中等 | 限軍人 |
| 束腰帶 | `waist/girl_girth.c` | girl girth | 300 | 5 | 原資料 |  |
| 精鐵環扣 | `waist/iron_girth.c` | iron girth | 800 | 6 | 原資料 |  |
| 獅蠻帶 | `waist/lion_belt.c` | lion belt | 300 | 150 | 中等 |  |
| 寒梅玉珮 | `waist/lunmay_jade.c` | lunmay jade | 800 | 650 | 珍品 |  |
| 鑲珠束腰 | `waist/perl_girth.c` | perl girth | 800 | 900 | 原資料 |  |
| 赤煌靈索 | `waist/red_belt.c` | red belt | 300 | 100 | 中等 |  |
| 火鱗腰帶 | `waist/red_scale_girth.c` | red_scale girth | 800 | 100 | 原資料 |  |
| 銀彎束腰 | `waist/silver_girth.c` | silver girth | 300 | 6 | 原資料 |  |
| 紫雲玉珮 | `waist/voliet_jade.c` | voliet jade | 800 | 650 | 珍品 | 唯一 |
| 蛟龍帶 | `waist/water_dragon_girdle.c` | water dragon girdle | 300 | 10 | 原資料 |  |
| 白玉腰帶 | `waist/white_girth.c` | white girth | 800 | 500 | 原資料 | 唯一 |
| 流雲清玉帶 | `waist/white_jade_girth.c` | white-jade girth | 800 | 300 | 原資料 |  |
