// /custom/legacy_npc/bai_jian_fei.c — 舊站 NPC：白劍飛（Bai jian fei）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：漕幫；房間：小船。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("白劍飛", ({ "bai jian fei", "bai", "fei" }));
    set("title", "漕幫仁堂分舵主");
    set_race("yaksa");
    set_class("fighter");
    set_level(25);
    set("gender", "male");
    set("age", 55);
    set("long",
        "白劍飛是水路第一大幫 \"漕幫\" 的仁堂分舵主，也是漕幫總舵主蕭尹的長子，白\n"
        "劍飛自幼師從蕭尹的義兄 \"玉面劍儒  白靖堂\" 門下，由於白靖堂膝下無子，對\n"
        "白劍飛視如己出，並將其一生鑽研劍術之精華豪不藏私的教授於白劍飛，蕭尹感\n"
        "其恩情，並體念其義兄年歲已高，遂令白劍飛改從白姓。\n"
        "白劍飛一方面因血緣因素，另一方面也因其精湛的劍法及輕功成為漕幫 \"仁義禮\n"
        "智信\" 五個堂口中為首位的仁堂舵主。\n");
    set("custom_faction", "fighter.fonxan");   // 封山派（docs/martial_arts/門派武功對照表.md）
    set_power("B");
    setup();
    carry_object("/d/qiaoyin_east/npc/obj/boots_of_cleanse")->wear();   // 塵不沾
    carry_object("/d/swaylan/lunmay/npc/obj/silver_girth")->wear();   // 銀彎束腰
    carry_object("/custom/armor/armor/white_dragon_plate")->wear();   // 混天白龍
    carry_object("/custom/weapon/sword/cherry_blossoms_sword")->wield();   // 櫻吹雪
    carry_object("/custom/weapon/sword/white_dragon_fang");   // 白龍牙
}
