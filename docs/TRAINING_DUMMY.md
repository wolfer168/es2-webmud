# 練武假人（training dummy）

使用者指示（2026-11-02）。振武軍營假人、冷梅莊假人、百花村石獅子等練武用的死物，
全部繼承同一份底本 `source/upstream/mudlib/feature/npc/training_dummy.c`，以後調整改一處就全部生效。

## 為什麼做成人物而不是物件

遊戲只有「人物」才能被比劃、攻擊（fight、kill、出招輪替、命中部位、招架都要對方是人物）。
做成物件就打不了，所以假人是「死物的人物」：外表是人物，生物才有的反應全部關掉。

## 假人的規則

| 項目 | 規則 | 在哪裡做到 |
|---|---|---|
| 反擊 | 不還手 | 底本：`fight_ob()`、`kill_ob()` 留空 |
| 命中 | 必定命中，不閃躲、不招架、不減傷 | `adm/daemons/combatd.c` 依 `training_dummy` 跳過防禦；底本的 `defend()`、`absorb()` 傳回 0 |
| 損壞 | 打不壞、不會死，精氣神不會被扣 | 底本：`receive_damage()` 只傳回數值、不扣；`consume_stat()`、`damage_stat()`、`die()` 不做事 |
| 特攻 | 按機率觸發 | 每一擊都算命中有傷害，靠命中觸發的特效照樣按機率發動；要「對方體力低於幾成」的特效不會出現（假人體力永遠是滿的） |
| 中毒、流血、任何狀態 | 不會有 | `feature/char/condition.c` 的 `set_condition()` 擋下；武器上毒（`custom/condition/weapon_poison.c`、`daemon/condition/blue_venom.c`）與黑齒啃咬（`daemon/race/blackteeth/gnaw.c`）連中毒敘述都不顯示 |
| 偷竊 | 不能偷 | `cmds/std/steal.c`：「假人空空如也，你無從下手。」 |
| 針灸 | 不能下針 | `cmds/std/acupuncture.c`（指定對象時）、`daemon/skill/wuto-needle.c`（對交手中的假人下針時）：「假人沒有經脈穴道，你無從下手。」 |
| 背刺 | 可以練粗淺的偷襲暗算 | `cmds/std/backstab.c`，見下節 |

敘述中的「假人」會換成實際名稱（例如石獅子）。

## 背刺

- 假人是死物，不會察覺偷襲，也不會反擊。
- 偷襲暗算技倆（backstab）在 40 級以前，對假人偷襲照常增長；到 40 級以後不再增長，
  也不給任何提示（使用者指示，2026-11-02）。
- 對假人偷襲不增加殺手本能（killerhood），也不增加罪孽（mortal sin）。
- 原本以 `TARGET_STAKE` 標記假人、超過 40 級就不准偷襲的舊寫法已移除（沒有任何物件使用這個標記）；現在超過 40 級仍可偷襲，只是不再增長。

## 新增假人

```
// 檔案開頭不要再 #include <npc.h>：底本已經繼承 NPC 標準物件。
inherit "/feature/npc/training_dummy";

void create()
{
    set_name("木人", ({"wooden man","man","木人"}));
    set("long", "……\n");
    setup();
}
```

底本的 `setup()` 會補上種族（人類）、職業（平民）、等級（20）與 `training_dummy` 標記；
要不同的種族或等級時，在 `setup()` 之前自己設定即可。
