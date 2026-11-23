/* 舊站 NPC 共用基底（custom/legacy_npc/）。NEW
 *
 * 舊站 NPC 依使用者提供的「舊有 NPC 待製作清單」（2026-10-15）製作，先不放入地圖。
 * 放進地圖的舊站 NPC 搬到所在區域的 npc 資料夾（例如 d/baobao/npc/），仍繼承這個基底；
 * 這裡只留還沒放進地圖的（使用者指示，2026-11-23，docs/NPC_ITEM_PLACEMENT.md）。
 * 清單見 docs/LEGACY_NPC_LIST.md。
 *
 * 在 create() 裡設定：
 *   set("legacy_aggressive", 1);   看到玩家就下殺手（土匪型）。
 *   set("legacy_patrol", 1);       巡邏：只在同一區域（房間的 map/area 相同）內走動，
 *                                  每 2 tick（4 秒）擲一次，10% 機率移動。
 */
#include <npc.h>
#include <command.h>

inherit F_FIGHTER;

#define PATROL_INTERVAL 4
#define PATROL_CHANCE   10

void init()
{
    object ob = this_player();

    ::init();
    if( query("legacy_aggressive") && objectp(ob) && userp(ob)
    &&  living(this_object()) && !is_fighting(ob)
    &&  environment() && !environment()->query("no_fight") && visible(ob) )
        kill_ob(ob);
}

void setup()
{
    ::setup();
    if( query("legacy_patrol") && clonep() )
        call_out("patrol", PATROL_INTERVAL);
}

void patrol()
{
    object env, room;
    mapping exits;
    string area, *dirs = ({});

    call_out("patrol", PATROL_INTERVAL);

    if( !living(this_object()) || is_fighting() || is_busy() ) return;
    if( !objectp(env = environment()) ) return;
    if( !stringp(area = env->query("map/area")) ) return;
    if( random(100) >= PATROL_CHANCE ) return;
    if( !mapp(exits = env->query("exits")) ) return;

    foreach( string dir, mixed dest in exits ) {
        if( !stringp(dest) ) continue;
        if( !objectp(room = find_object(dest)) && catch(room = load_object(dest)) ) continue;
        if( objectp(room) && room->query("map/area") == area )
            dirs += ({ dir });
    }
    if( sizeof(dirs) )
        GO_CMD->main(this_object(), dirs[random(sizeof(dirs))]);
}
