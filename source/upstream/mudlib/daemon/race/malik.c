/* CUSTOM RACE: 巫首 (malik). Original race data 2006/09/15. */
#define BASE_WEIGHT 40000
#include <race.h>
inherit HUMANOID;

private void create() {
    ::create(); seteuid(getuid());
    set("karma", 30); set("civilized", 1); set("commoner_score_base", 150);
    set("class_level_cap", ([
        "commoner":1, "fighter":50, "taoist":60, "alchemist":50,
        "soldier":50, "scholar":60, "monk":65, "thief":50
    ]));
    // 巫首沒有腳：身體部位不含左腳、右腳，戰鬥敘述也不會出現腳部。
    set("limbs", ({
        "頭部", "頸部", "胸口", "後心", "左肩", "右肩", "左臂",
        "右臂", "左手", "右手", "腰間", "小腹", "左腿", "右腿"
    }));
    // 徒手招式移除「踢了一腳」。
    combat_action = ({
        ([ "action": "$N揮拳攻擊$n的$l", "damage_type": "瘀傷" ]),
        ([ "action": "$N往$n的$l一抓", "damage_type": "抓傷" ]),
        ([ "action": "$N提起拳頭往$n的$l捶去", "damage_type": "瘀傷" ]),
        ([ "action": "$N對準$n的$l用力揮出一拳", "damage_type": "瘀傷" ]),
    });
    set("default_actions", (: call_other, __FILE__, "query_action" :));
    DAEMON_D->register_race_daemon("malik");
}
void setup(object ob) {
    ::setup(ob); ob->set_default_object(__FILE__);
    if (!ob->query_weight()) ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str",1)-13)*5000);
    ob->add_temp("apply/armor", 40);
    ob->add_temp("apply/attack", 30);
    ob->add_temp("apply/defense", 30);
}
// 巫首沒有腳：不能穿鞋子（feet_eq）與護腿（leg_eq）。
int valid_wear(object me, object ob, string part) {
    if (part == "feet_eq")
        return notify_fail("巫首沒有腳，無法穿鞋子。\n");
    if (part == "leg_eq")
        return notify_fail("巫首沒有腳，無法穿戴護腿。\n");
    return ::valid_wear(me, ob, part);
}
void initialize(object ob) {
    ::initialize(ob);
    ob->init_attribute(([
        "str":8+random(4), "cor":8+random(4), "int":25+random(6), "spi":25+random(6),
        "cps":23+random(6), "dex":20+random(6), "con":10+random(6), "wis":20+random(6)
    ]));
    ob->init_statistic(([ "gin":70, "kee":40, "sen":100 ]));
    if (!ob->query("age")) ob->set("age", 14+random(4));
    ob->set_default_object(__FILE__);
}
