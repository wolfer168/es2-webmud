// foreman.c

#include <npc.h>

inherit F_VILLAGER;

void new_crate();


void create()
{
	set_name("工頭", ({ "foreman" }) );
	set_race("human"); set_class("commoner");
	set_level(8);

	set("age", 48);
	set("long",
		"這位就是這家貨棧的工頭﹐負責指揮工人將貨物搬進搬出﹐如果\n"
		"你想打工賺些錢﹐可以跟他談談看。\n");
	set("chat_chance", 10);
	set("chat_msg", ({
		(: new_crate :),
		"工頭大聲吆喝著工人將貨物從倉庫搬出來。\n",
		"工頭大叫﹕小王呢﹖今天有沒有來﹖\n",
		"工頭說道﹕誰再去多找些人手﹐唉﹐忙死了。\n",
		"工頭說道﹕要算工錢的一個個來 ... 別急 ...\n"
	}) );
		
	set_power("C");
	setup();
	carry_money("coin", 220);
}

int accept_fight()
{
	do_chat("工頭說道﹕比武﹖你瘋了嗎﹖我才沒那種閒功夫。\n");
	return 0;
}

void relay_say(object me, string msg)
{
	if( is_fighting() || is_chatting() ) return;

	if( strsrch(msg, "工錢") >= 0 ) {
		int amount, crates;
		object money;

		/* Pay by delivered crate count: 25 coins per crate. */
		crates = me->query_temp("wage_crates");
		amount = crates > 0 ? crates * 25 : me->query_temp("wage_deserved");

		if( amount > 0 ) {
			money = new("/obj/money/coin");
			money->set_amount(amount);

			/*
			 * CUSTOM WebMUD fix:
			 * Never put wages into the foreman's inventory before paying.
			 * Combined money objects auto-merge, so the old flow merged the
			 * 25-coin wage with his carried 220 coins and `give coin` handed
			 * the whole 245-coin stack to the player. Pay the freshly-created
			 * wage object directly to the worker instead.
			 */
			if( !money->move(me) ) {
				destruct(money);
				command("say 你身上東西太多了﹐先騰出些地方再來領工錢。");
				return;
			}

			command("say 好﹐好 ... 總共搬了" + chinese_number(crates > 0 ? crates : amount / 25)
				+ "個箱子﹐工錢是" + chinese_number(amount) + "文錢﹐哪﹐給你。");
			me->delete_temp("wage_crates");
			me->delete_temp("wage_deserved");
		}
		else do_chat("工頭說道﹕搬一個箱子二十五文錢﹐損壞的賠三倍。\n");
		return;
	}
}

void new_crate()
{
	object ob;
	
	if( !environment()
	||	sizeof(all_inventory(environment())) >= 15 ) return;

	ob = new("/d/snow/obj/crate");
	ob->move(environment());
	say("工頭說道﹕喂﹗那邊卸貨的小心一點﹐別給摔壞了﹗\n");
}
