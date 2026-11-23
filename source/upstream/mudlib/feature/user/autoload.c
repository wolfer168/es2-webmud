// autoload.c

string *autoload;

void clean_up_autoload() { autoload = 0; }

// new_owned_object(): create a fresh object that genuinely belongs to this
// player (this_object()), for callers that need the new object to be able
// to write back into the player's own protected properties (USER_PROTECT()
// requires the caller's euid to match the player's).
//
// export_uid() only succeeds when called by an object running under its
// own real identity (getuid()==geteuid()) -- a room that seteuid()'d to
// borrow the player's identity does not qualify, which is why this must be
// called on the player object itself, not from the room. It also only sets
// the new object's uid, not its euid (which ITEM::setup() -- already run
// once, before export_uid, as part of the object's own create() -- already
// latched in as unset); re-running setup() re-adopts euid from the uid
// export_uid just granted.
object new_owned_object(string file)
{
	object ob;

	ob = new(file);
	if( !ob ) return 0;
	export_uid(ob);
	ob->setup();
	return ob;
}

void save_autoload()
{
	object *inv;
	int i, j;
	mixed param;

	inv = all_inventory();
	autoload = allocate(sizeof(inv));
	for(i=0, j=0; i<sizeof(inv); i++) {
		if( !(param = inv[i]->query_autoload()) ) continue;
		autoload[j] = base_name(inv[i]);
		if( stringp(param) ) autoload[j] += ":" + param;
		j++;
	}
	autoload = autoload[0..j-1];
}

void restore_autoload()
{
	int i;
	object ob;
	string file, param, err;

	if( !pointerp(autoload) ) return;

	for(i=0; i<sizeof(autoload); i++) {
		if( sscanf(autoload[i], "%s:%s", file, param)!=2 ) {
			file = autoload[i];
			param = 0;
		}
		// 檔案搬過家的，存檔裡的舊路徑先換成新路徑（docs/NPC_ITEM_PLACEMENT.md）。
		file = MOVED_PATH_D->resolve(file);
		err = catch(ob = new(file, this_object()));
		if( err || !ob ) {
			write("你覺得似乎失落了什麼重要的東西﹐最好通知一下巫師。\n");
			log_file("AUTOLOAD", sprintf("Fail to autoload %s of %s, error %s\n",
				file, this_object()->query("name"), err));
			continue;
		}
		export_uid(ob);
		ob->move(this_object());
		ob->autoload(param);
	}
	clean_up_autoload();		// To save memory.
}
