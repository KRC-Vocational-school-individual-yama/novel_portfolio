#include"game.h"
#include<DxLib.h>
#include<string>
#include"keyboard.h"

void DebugDraw();

namespace {
	std::string selecttext[6] = {};
	std::string messegetext = "";
	std::string middletext = "";
	std::string undertext = "";
	std::string uptext = "";
	std::string choicetext = "";

	int selectnox = 0;
	int selectnoy = 0;
	int selectcolor = 0;
	int mozicount = 0;
	bool moziflug = false;
	int mozisize = 0;

	int ldowncount = -1;
	int lmidcount = -1;
	int lupcount = -1;
	int page = 0;
	enum page {
		foolenter,
		start_page,
		select_pagestart,
		select_page,
		select_pageend,
		lup,
		lmid,
		ldown,
		rup,
		rmid,
		rdown,

	};

	int debugcount = 0;
	bool debugflug = false;
	class Player {
	public:
		Player() {
			for (int i = 0; i < kazu; i++) {
				format[i] = "";
			}
			fontsize = 16;
			needexp = 30;
			status[lv  ] = 1;
			status[hp  ] = 100;
			status[mp  ] = 10;
			status[ap  ] = 5;
			status[df  ] = 5;
			status[luck] = 3;
			status[exp] = 0;
			status[gold] = 0;
		}
		void Debug() {
			if (CheckHitKey(KEY_INPUT_NUMPAD9)) {
				GetExp(100);
			}
		}
		void Drawstatus() {
			SetFontSize(fontsize);
			for (int i = 0; i < kazu; i++) {
				switch (i) {
				case lv:
					format[i] = "Lv   :" + std::to_string(status[i]);
					break;
				case exp:
					format[i] = "EXP  :" + std::to_string(status[i]);
					break;
				case hp:
					format[i] = "HP   :" + std::to_string(status[i]);
					break;
				case mp:
					format[i] = "MP   :" + std::to_string(status[i]);
					break;
				case ap:
					format[i] = "ATC  :" + std::to_string(status[i]);
					break;
				case df:
					format[i] = "DEF  :" + std::to_string(status[i]);
					break;
				case luck:
					format[i] = "Luck :" + std::to_string(status[i]);
					break;
				case gold:
					format[i] = "Gold :"+std::to_string(status[i]);
					break;
				default:
					format[i] = "";
				}

				DrawFormatString(5+1, 5+fontsize*i+1+i, GetColor(0,0,0), format[i].c_str());
				DrawFormatString(5-1, 5+fontsize*i-1+i, GetColor(0,0,0), format[i].c_str());
				DrawFormatString(5+1, 5+fontsize*i-1+i, GetColor(0,0,0), format[i].c_str());
				DrawFormatString(5-1, 5+fontsize*i+1+i, GetColor(0,0,0), format[i].c_str());
								 
				DrawFormatString(5, 5+fontsize*i+i, GetColor(255,255,255), format[i].c_str());
			}
			SetFontSize(24);
		}
		int GetGold(int num) {
			status[gold]= num + status[gold];
			if (status[gold] >= 10000)status[gold] = 10000;
			if (status[gold] <= 0)status[gold]=0;
			return status[gold];
		}
		int GetHp(int num) {
			status[hp] = status[hp] - num;
			if (status[hp] >= 999)status[hp] = 999;
			if (status[hp] <= 0)status[hp] = 0;
			return status[hp];
		}
		int GetExp(int num) {
			status[exp] += num;
			LvUp();
			return status[exp];
		}
	private:
		static const int kazu = 10;
		std::string format[kazu] = {};
		int status[kazu] = {};
		int fontsize = 0;
		enum status {
			lv,
			akerutoko,
			hp,
			mp,
			ap,
			df,
			luck,
			exp,
			akerutoko_2,
			gold,
		};
		int needexp = 0;

		void LvUp() {
			int lv_exp = needexp + needexp * 0.6;
			if (status[exp] >= lv_exp) {
				status[lv] += 1;
				needexp=lv_exp;
			}
		}
	}soro;
	class gameCircle {
	public:
		gameCircle() {
			onoff = true;
			x = 400;
			y = 300;
			r = 24;
			onex = 1;
			oney = 1;
			color[sinnku] = GetColor(182, 0, 51);
			color[kihada] = GetColor(254, 242, 99);
			color[seizi] = GetColor(104, 183, 161);
			color[ruri] = GetColor(29, 80, 162);
			color[kakitubata] = GetColor(77, 67, 152);
			color[ama] = GetColor(239, 229, 202);
			color[namari] = GetColor(122, 124, 125);
			moverand = GetRand(3);
		}
		void Draw() {
			if (onoff == true) {
				DrawCircle(x, y, r, color[colorselect], true);
			}
		}
		void Move() {
			if (CheckHitKey(KEY_INPUT_2))onoff = false;
			if (CheckHitKey(KEY_INPUT_3))onoff = true;
			if (onoff == true) {
				entertask();
				if (moverand == 0) {
					x += onex;
					y -= oney;
				}
				if (moverand == 1) {
					x -= onex;
					y -= oney;
				}
				if (moverand == 2) {
					x += onex;
					y += oney;
				}
				if (moverand == 3) {
					x -= onex;
					y += oney;
				}
				if (x + r >= 600)onex = -onex;
				if (x - r <= 200)onex = -onex;
				if (y + r >= 500)oney = -oney;
				if (y - r <= 200)oney = -oney;
			}
		}
		void entertask() {
			if (CheckHitKey(KEY_INPUT_RETURN) && keystop == false &&
				600 >= x && x >= 200 &&
				500 >= y && y >= 200
				) {
				//moverand = GetRand(3);
				colorselect++;
				if (colorselect > colormax - 1)colorselect = 0;
				keystop = true;
			}
			else if (CheckHitKey(KEY_INPUT_RETURN) == 0) {
				keystop = false;
			}
		}
		bool Debug() {
			return onoff;
		}
	private:
		int x = 0;
		int y = 0;
		int r = 0;
		static const int colormax = 7;
		int color[colormax] = {};
		int colorselect = 0;
		int moverand = 0;
		int onex = 0;
		int oney = 0;
		bool keystop = false;
		bool onoff = false;
		enum color {
			sinnku,
			kihada,
			seizi,
			ruri,
			kakitubata,
			ama,
			namari,
		};

	}midcircle;
}

//wstringをstringへ変換
std::string WStringToString(std::wstring oWString)
{
	// wstring → SJIS
	int iBufferSize = WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str()
		, -1, (char*)NULL, 0, NULL, NULL);
	// バッファの取得
	CHAR* cpMultiByte = new CHAR[iBufferSize];
	// wstring → SJIS
	WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str(), -1, cpMultiByte
		, iBufferSize, NULL, NULL);
	// stringの生成
	std::string oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);
	// バッファの破棄
	delete[] cpMultiByte;
	// 変換結果を返す
	return(oRet);
}
std::wstring StringToWString(std::string oString)
{
	//  SJIS→wstring
	std::wstring ws;
	int iBufferSize = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, oString.c_str()
		, -1, (wchar_t*)NULL, 0);

	// バッファの取得
	wchar_t* cpMultiByte = new wchar_t[iBufferSize];
	// wstring → SJIS
	MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, cpMultiByte
		, iBufferSize);
	// wstringの生成
	std::wstring oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);
	// バッファの破棄
	delete[] cpMultiByte;
	// 変換結果を返す
	return(oRet);
}

void gameDebug() {
	if (CheckHitKey(KEY_INPUT_1)) {
		gameInit();
	}
	if (CheckHitKey(KEY_INPUT_BACK) && keystop == false) {
		keystop = true;
		page--;
	}
	DebugDraw();
}
void DebugDraw() {
	printfDx("\nselectnox;%d\nselectnoy;%d\n", selectnox, selectnoy);
	printfDx("page;%d\n", page);
	printfDx("lmidcount;%d\n", lmidcount);
	printfDx("ldowncount;%d\n", ldowncount);
	printfDx("mozicount;%d\n", mozicount / 3);
	printfDx("mozisize;%d\n", mozisize);
	printfDx("ball,onoff;%d\n", midcircle.Debug());
	soro.Debug();
}
void gameInit() {
	SetFontSize(24);
	selectnox = 0;
	selectnoy = 0;
	page = 0;
	lupcount = -1;
	lmidcount = -1;
	ldowncount = -1;
	messegetext = "";
	middletext = "";
	undertext = "";
	uptext = "";
	choicetext = "";
	for (int i = 0; i < 6; i++) {
		selecttext[i] = {};
	}
}
void gameUpdete() {
	if (page == start_page) {
		gameInit();
		middletext = "ここは広場";
		page++;
	}
	if (page == select_pagestart) {
		choicetext = "";
		middletext = "";
		uptext = "広場";
		undertext = "十字キーで選択しよう";
		/*ここから下__仮- - - - - - - - - - - - - - -*/
		selecttext[0] = "左上";
		selecttext[1] = "左真ん中";
		selecttext[2] = "左下";
		selecttext[3] = "右上";
		selecttext[4] = "右真ん中";
		selecttext[5] = "右下";
		/*- - - - - - - - - - - - - - - - - - - - - -*/
		page++;
	}
	if (page == select_page) {

		if (selectnox == 0 && selectnoy == 0) {
			selecttext[0] = "左上";
			messegetext = "ここは報告するため行く";
		}
		if (selectnox == 0 && selectnoy == 1) {
			selecttext[1] = "左真ん中";
			messegetext = "ここには道具系を";
		}
		if (selectnox == 0 && selectnoy == 2) {
			selecttext[2] = "左下";
			messegetext = "ここは体力回復を";
		}
		if (selectnox == 1 && selectnoy == 0) {
			selecttext[3] = "右上";
			messegetext = "ここはお金を稼ぐ";
		}
		if (selectnox == 1 && selectnoy == 1) {
			selecttext[4] = "右真ん中";
			messegetext = "ここはその他関連で";
		}
		if (selectnox == 1 && selectnoy == 2) {
			selecttext[5] = "右下";
			messegetext = "探索するための";
		}
	}
	if (page == select_pageend) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				if (selectnox == i && selectnoy == j) {
					page = ((selectnox * 3) + selectnoy + (select_pageend + 1));
				}
			}
		}
		selecttext[0] = "";
		selecttext[1] = "";
		selecttext[2] = "";
		selecttext[3] = "";
		selecttext[4] = "";
		selecttext[5] = "";
		messegetext = "";
		middletext = "";
		undertext = "";
		uptext = "";
	}
	if (page == lup) {
		uptext = "報告間";

		if (lupcount == -1) {
			moziflug = false;
			lupcount++;
		}
		if (lupcount == 0)middletext = "エンターキーで\n次の文を読むことができるぞい";
		if (lupcount == 1)middletext = "ここでは此度の成果を\n儂に報告してもらう";
		if (lupcount == 2)middletext = "汝、 . . . .";
		if (lupcount == 3) {
			choicetext = "";
			middletext = "";
			undertext = "十字キーで選択しよう";
			messegetext = "これまでに何事を果たした？";
			selecttext[0] = "真っ直ぐにここにきた";
			selecttext[1] = "敵を倒した。";
			selecttext[2] = "買い物をした。";
			selecttext[3] = "これからするのさ";
			selecttext[4] = "黙っている。";
			selecttext[5] = "広間に戻る";
		}
		if (lupcount == 4) {
			if (selectnox == 0 && selectnoy == 0) {
				lupcount = 10;
				choicetext = "真っ直ぐにここにきた";
			}
			if (selectnox == 0 && selectnoy == 1) {
				lupcount = 20;
				choicetext = "敵を倒した。";
			}
			if (selectnox == 0 && selectnoy == 2) {
				lupcount = 30;
				choicetext = "買い物をした。";
			}
			if (selectnox == 0 && selectnoy == 3) {
				lupcount = 40;
				choicetext = "これからするのさ";
			}
			if (selectnox == 0 && selectnoy == 4) {
				lupcount = 50;
				choicetext = "黙っている。";
			}
			if (selectnox == 1 && selectnoy == 0)lupcount = 60;

			selecttext[0] = "";
			selecttext[1] = "";
			selecttext[2] = "";
			selecttext[3] = "";
			selecttext[4] = "";
			selecttext[5] = "";
			messegetext = "";
			undertext = "";
			moziflug = false;
		}
		if (lupcount == 10)middletext = "ふむ、真っ直ぐ来るとは、\n 素直な性格をしているな";
		if (lupcount == 11)middletext = "その言い方から察するに";
		if (lupcount == 12)middletext = "ここに来るのは\n 初めてなのだろうな、";
		if (lupcount == 13)middletext = "ここでは儂に";
		if (lupcount == 14)middletext = "報告をしてもらう場である";
		if (lupcount == 15)middletext = "戦闘、買い物、";
		if (lupcount == 16)middletext = "汝は何をしたか";
		if (lupcount == 17)middletext = "それを報告してもらいたい";
		if (lupcount == 18)middletext = "以上だ";
		if (lupcount == 19) lupcount = 3;

		if (lupcount == 20)middletext = "そうか、";
		if (lupcount == 21)middletext = "もう現在敵対してる者について\n 説明する必要はなさそうじゃな";
		if (lupcount == 22)middletext = "倒した敵から\n ドロップするアイテムを";
		if (lupcount == 23)middletext = "道具屋などのお店に売りはらい";
		if (lupcount == 24)middletext = "自身の装備を整えるがよい";
		if (lupcount == 25)middletext = "一応、戦闘のコツを伝授しよう";
		if (lupcount == 26)middletext = "※現在、戦闘がありません";
		if (lupcount == 27)middletext = "※追加するかも不明です";
		if (lupcount == 28)middletext = "※気ままに作成中でございます。";
		if (lupcount == 29)lupcount = 3;

		if (lupcount == 30)middletext = "買い物とは\n マイペースに歩んでおるの";
		if (lupcount == 31)middletext = "どんな物が買えたのかのう";
		if (lupcount == 32)middletext = "武器や防具、";
		if (lupcount == 33)middletext = "消耗品などを買うと";
		if (lupcount == 34)middletext = "その後の冒険に役立つであろう";
		if (lupcount == 35)middletext = "今は序盤じゃから、";
		if (lupcount == 36)middletext = "必要ないかもしれんな";
		if (lupcount == 37)middletext = "そのうち、\n 追加される物もあるかもしれぬ";
		if (lupcount == 38)middletext = "ちょくちょく寄るとよいぞ";
		if (lupcount == 39)lupcount = 3;

		if (lupcount == 40)middletext = "うむ、その意気や良し";
		if (lupcount == 41)middletext = "これからは色々探索し";
		if (lupcount == 42)middletext = "様々なところへ\n 冒険するであろう";
		if (lupcount == 43)middletext = "その冒険を一つ一つ";
		if (lupcount == 44)middletext = "楽しんでくるがよい";
		if (lupcount == 45)middletext = "じゃが、\n 行き詰まるとき、";
		if (lupcount == 46)middletext = "如何したら良いか\n 分からない時が";
		if (lupcount == 47)middletext = "あるやもしれぬ";
		if (lupcount == 48)middletext = "その時は、\n またここへ来るとよいぞ";
		if (lupcount == 49)lupcount = 3;

		if (lupcount == 50)middletext = "寡黙なのだな";
		if (lupcount == 51)middletext = "うむ......";
		if (lupcount == 52)middletext = "...";
		if (lupcount == 53)lupcount = 59;
		if (lupcount == 59)lupcount = 3;

		if (lupcount == 60) {
			page = select_pagestart;
			lupcount = -1;
			selectnox = 0;
			selectnoy = 0;
		}

		if (CheckHitKey(KEY_INPUT_RIGHT)) {
			if (lupcount == 3)selectnoy = 0;
		}
		if (CheckHitKey(KEY_INPUT_RETURN) && keystop == false) {

			mozicount = mozisize * 3;
			if (moziflug == true) {
				mozicount = 0;
				lupcount++;
				moziflug = false;
			}
			keystop = true;
		}
		
	}
	if (page == lmid) {
		uptext = "お店";
		if (lmidcount == -1) {
			moziflug = false;
			selectnox = 0;
			selectnoy = 0;
			lmidcount++;
		}
		if (lmidcount == 0) {
			choicetext = "";
			middletext = "";
			undertext = "十字キーで選択しよう";
			messegetext = "どこに行こうかな？";
			selecttext[0] = "道具屋";
			selecttext[1] = "武器屋";
			selecttext[2] = "防具屋";
			selecttext[3] = "占い屋";
			selecttext[4] = "辺りを見る";
			selecttext[5] = "広間に戻る";
		}
		if (lmidcount == 1) {
			moziflug = false;
			if (selectnox == 0 && selectnoy == 0) {
				lmidcount = 10;
				choicetext = "道具屋";
			}
			if (selectnox == 0 && selectnoy == 1) {
				lmidcount = 20;
				choicetext = "武器屋";
			}
			if (selectnox == 0 && selectnoy == 2) {
				lmidcount = 30;
				choicetext = "防具屋";
			}
			if (selectnox == 1 && selectnoy == 0) {
				lmidcount = 40;
				choicetext = "占い屋";
			}
			if (selectnox == 1 && selectnoy == 1) {
				lmidcount = 50;
				choicetext = "辺りを見る（説明）";
			}
			if (selectnox == 1 && selectnoy == 2)lmidcount = 60;

			selecttext[0] = "";
			selecttext[1] = "";
			selecttext[2] = "";
			selecttext[3] = "";
			selecttext[4] = "";
			selecttext[5] = "";
			messegetext = "";
			undertext = "";

			selectnox = 1;
			selectnoy = 0;
		}


		if (lmidcount == 10) {
			
			undertext = "「ここは道具屋だよ！」";
			middletext = "";
			selecttext[0] = "回復薬(普通)";
			selecttext[1] = "マナぽ";
			selecttext[2] = "回復薬(高級)";
			selecttext[3] = "白い粉";
			selecttext[4] = "おすすめは？";
			selecttext[5] = "お店を出る";
			if (selectnox == 0 && selectnoy == 0)messegetext = "体力を回復する薬\n　防腐剤が入っている";
			if (selectnox == 0 && selectnoy == 1)messegetext = "気持ちの切り替えができる薬\n　いかがわしい..."; 
			if (selectnox == 0 && selectnoy == 2)messegetext = "体力を大きく回復する薬\n　徹夜も完璧！"; 
			if (selectnox == 0 && selectnoy == 3)messegetext = "状態を上げる粉\n　ペロっ..これは!せいｓnk...."; 
			if (selectnox == 0 && selectnoy == 4)messegetext = "目移りしてしまった\n　おすすめを聞いてみる"; 
			if (selectnox == 1 && selectnoy == 0)messegetext = "お店を離れる"; 
		}
		if (lmidcount == 11) {
			lmidcount++;
			for (int i = 0; i < 6; i++) {
				selecttext[i] = "";
			}
			moziflug = false;
			messegetext = "";
			undertext = "";
		}
		if (lmidcount == 12) {
			if (selectnox == 0 && selectnoy == 0) {
				middletext = "回復薬ね毎度あり！";
				undertext = "回復薬を手に入れた";
			}
			if (selectnox == 0 && selectnoy == 1) {
				middletext = "あいよ！正真正銘のマナぽだよ！";
				undertext = "マナぽを手に入れた";
			}
			if (selectnox == 0 && selectnoy == 2) {
				middletext = "これを買うとは\n お客さんお目が高いね！";
				undertext = "回復薬（上）を手に入れた";
			}
			if (selectnox == 0 && selectnoy == 3) {
				middletext = "あんた、\n これを買うのは、大体悪い時さ";
				undertext = "白い粉を手に入れた";
			}
			if (selectnox == 0 && selectnoy == 4) {
				middletext = "そりゃ、回復薬よ\n　傷ついてもこれ一振りで\n　　元気さね";
				undertext = "回復薬がおすすめだそうだ";
			}
			if (selectnox == 1 && selectnoy == 0) {
				lmidcount = -1;
			}
		}
		if (lmidcount == 13) {
			selectnox = 1;
			selectnoy = 0;
			lmidcount = 10;
		}
		if (lmidcount == 18)lmidcount = 19;
		if (lmidcount == 19) lmidcount = 0;

		if (lmidcount == 20) {
			undertext = "「武器だ、切れ物ならここに来な」";
			middletext = "";
			selecttext[0] = "ナイフ";
			selecttext[1] = "包丁";
			selecttext[2] = "長剣";
			selecttext[3] = "刀";
			selecttext[4] = "おすすめは？";
			selecttext[5] = "お店を出る";
			if (selectnox == 0 && selectnoy == 0)messegetext = "手ごろなナイフ\n　実は果物ナイフ";
			if (selectnox == 0 && selectnoy == 1)messegetext = "切れ味抜群な包丁\n　出刃包丁だ";
			if (selectnox == 0 && selectnoy == 2)messegetext = "見事な剣\n　叩き切るタイプのやつ";
			if (selectnox == 0 && selectnoy == 3)messegetext = "綺麗な波紋の刀\n　反り具合がカッコいい";
			if (selectnox == 0 && selectnoy == 4)messegetext = "武器は何が合うのか、\n　おすすめを聞いてみる";
			if (selectnox == 1 && selectnoy == 0)messegetext = "お店を離れる";
		}
		if (lmidcount == 21) {
			lmidcount++;
			for (int i = 0; i < 6; i++) {
				selecttext[i] = "";
			}
			moziflug = false;
			messegetext = "";
			undertext = "";
		}
		if (lmidcount == 22) {
			if (selectnox == 0 && selectnoy == 0) {
				middletext = "ナイフだ,錆びに気をつけな";
				undertext = "ナイフを手に入れた";
			}
			if (selectnox == 0 && selectnoy == 1) {
				middletext = "包丁だ,ちゃんと手入れしな";
				undertext = "包丁を手に入れた";
			}
			if (selectnox == 0 && selectnoy == 2) {
				middletext = "長剣だ,余り乱暴に扱うなよ";
				undertext = "長剣を手に入れた";
			}
			if (selectnox == 0 && selectnoy == 3) {
				middletext = "刀だ,丁寧に扱えよ";
				undertext = "刀を手に入れた";
			}
			if (selectnox == 0 && selectnoy == 4) {
				middletext = "そしたら包丁だな";
				undertext = "武器以外も使うらしい";
			}
			if (selectnox == 1 && selectnoy == 0) {
				lmidcount = -1;
			}
		}
		if (lmidcount == 23) {
			selectnox = 1;
			selectnoy = 0;
			lmidcount = 20;
		}
		if (lmidcount == 28) lmidcount = 29;
		if (lmidcount == 29) lmidcount = 0;

		if (lmidcount == 30) {
			undertext = "「防具だよー　服は着るよねー？」";
			middletext = "";
			selecttext[0] = "麻の服";
			selecttext[1] = "布の服";
			selecttext[2] = "鎧";
			selecttext[3] = "鎖帷子";
			selecttext[4] = "おすすめは？";
			selecttext[5] = "お店を出る";
			if (selectnox == 0 && selectnoy == 0)messegetext = "麻でできた服\n　ごわごわしている";
			if (selectnox == 0 && selectnoy == 1)messegetext = "手触りがいい服\n　着心地がよさそうだ";
			if (selectnox == 0 && selectnoy == 2)messegetext = "しっかりした鎧\n　１日着ているのは重そうだ";
			if (selectnox == 0 && selectnoy == 3)messegetext = "くさりかたびらだ\n　簡単には切れないだろう";
			if (selectnox == 0 && selectnoy == 4)messegetext = "どの服を買おう？\n　おすすめを聞いてみる";
			if (selectnox == 1 && selectnoy == 0)messegetext = "お店を離れる";
		}
		if (lmidcount == 31) {
			lmidcount++;
			for (int i = 0; i < 6; i++) {
				selecttext[i] = "";
			}
			moziflug = false;
			messegetext = "";
			undertext = "";
		}
		if (lmidcount == 32) {
			if (selectnox == 0 && selectnoy == 0) {
				middletext = "麻の服はここだよー";
				undertext = "麻の服を手に入れた";
			}
			if (selectnox == 0 && selectnoy == 1) {
				middletext = "はいTシャツねー";
				undertext = "布の服を手に入れた";
			}
			if (selectnox == 0 && selectnoy == 2) {
				middletext = "よろいって着づらいよねー";
				undertext = "鎧を手に入れた";
			}
			if (selectnox == 0 && selectnoy == 3) {
				middletext = "くさりかたびらだよー\n 戦うんだねー";
				undertext = "鎖帷子を手に入れた";
			}
			if (selectnox == 0 && selectnoy == 4) {
				middletext = "布の服はおすすめだよー";
				undertext = "他の服より着やすいらしい";
			}
			if (selectnox == 1 && selectnoy == 0) {
				lmidcount = -1;
			}
		}
		if (lmidcount == 33) {
			selectnox = 1;
			selectnoy = 0;
			lmidcount = 30;
		}
		if (lmidcount == 38) lmidcount = 39;
		if (lmidcount == 39) lmidcount = 0;

		if (lmidcount == 40) {
			messegetext = "あんた、占うかい？";
			selecttext[0] = "はい";
			selecttext[1] = "いいえ";
		}
		if (lmidcount == 41) {
			moziflug = false;
			for (int i = 0; i < 2; i++) {
				selecttext[i] = "";
			}
			if (selectnox == 0) lmidcount = 45;
			if (selectnox == 1) lmidcount = 42;
		}
		if (lmidcount == 42) {
			middletext = "なら帰ることだね";
		}
		if (lmidcount == 43) {
			lmidcount = 0;
		}
		if (lmidcount == 44) lmidcount = 49;
		if (lmidcount == 45) middletext = "うーーーーーーむ";
		if (lmidcount == 46) middletext = "そのままでも\n うまくやっていけそうな\n　　星の巡りをしているね、";
		if (lmidcount == 47) middletext = "こんな館きて占いをするほど\n　悪い状況じゃないみたいよ";
		if (lmidcount == 48) middletext = "新しいことに挑戦するのを\n　忘れずにね";
		if (lmidcount == 49) lmidcount = 0;

		if (lmidcount == 50)middletext = "ここは\n 多くのお店が立ち並ぶ路地";
		if (lmidcount == 51)middletext = "武器屋、防具屋、\n 道具屋、占い屋がある。";
		if (lmidcount == 52)middletext = "それぞれのお店の店主は";
		if (lmidcount == 53)middletext = "個性的な人が多いみたい";
		if (lmidcount == 54) lmidcount = 59;
		if (lmidcount == 59) lmidcount = 0;

		if (lmidcount == 60) {
			page = select_pagestart;
			lmidcount = -1;
			selectnox = 0;
			selectnoy = 0;
		}



		if (CheckHitKey(KEY_INPUT_RIGHT)) {
			if (lmidcount == 10||
				lmidcount==20||
				lmidcount==30
				)
				selectnoy = 0;
			
		}

		if (CheckHitKey(KEY_INPUT_RETURN) && keystop == false) {
			mozicount = mozisize * 3;
			if (moziflug == true) {
				mozicount = 0;
				lmidcount++;
				moziflug = false;
			}
			keystop = true;
		}
		
	}
	if (page == ldown) {
		uptext = "宿";
		if (ldowncount == -1) {
			moziflug = false;
			selectnox = 1;
			selectnoy = 0;
			ldowncount++;
		}
		if (ldowncount == 0)middletext = "ここは宿屋だよ！\n 止まっていくかい？";
		if (ldowncount == 1) {
			undertext = "どうする？";
			middletext = "";
			selecttext[0] = "泊ってく";
			selecttext[1] = "御飯食べてく";
			selecttext[2] = "少し休んでく";
			selecttext[3] = "辺りを見てみる";
			selecttext[4] = "椅子に座る";
			selecttext[5] = "宿を出る";
			if (selectnox == 0 && selectnoy == 0)messegetext = "体力が全回復する";
			if(selectnox==0&&selectnoy==1)messegetext = "体力が半分回復";
			if(selectnox==0&&selectnoy==2)messegetext = "体力が少し回復";
			if(selectnox==0&&selectnoy==3)messegetext = "この宿を少し見て行こう";
			if(selectnox==0&&selectnoy==4)messegetext = "すぐ近くの椅子に座ろう";
			if(selectnox==1&&selectnoy==0)messegetext ="宿屋から出ていく";
		}
		if (ldowncount == 2) {
			moziflug = false;
			if (selectnox == 0 && selectnoy == 0) {
				choicetext = "泊ってく";
				ldowncount = 10; 
			}
			if (selectnox == 0 && selectnoy == 1) {
				choicetext = "御飯食べてく";
				ldowncount = 20;
			}
			if (selectnox == 0 && selectnoy == 2) {
				choicetext = "少し休んでく";
				ldowncount = 30;
			}
			if (selectnox == 0 && selectnoy == 3) {
				choicetext = "辺りを見てみる";
				ldowncount = 40;
			}
			if (selectnox == 0 && selectnoy == 4) {
				choicetext = "椅子に座る";
				ldowncount = 50;
			}
			if (selectnox == 1 && selectnoy == 0) {
				choicetext = "";
				ldowncount = 60;
			}
			messegetext = "";
			undertext = "";
			selecttext[0] = "";
			selecttext[1] = "";
			selecttext[2] = "";
			selecttext[3] = "";
			selecttext[4] = "";
			selecttext[5] = "";
		}
		if (ldowncount == 10)middletext = "体力が全回復した！";
		if(ldowncount==11)ldowncount = 19;
		if(ldowncount==19)ldowncount = 60;
		if (ldowncount == 20)middletext = "体力が中回復した！";
		if(ldowncount==21)ldowncount = 29;
		if(ldowncount==29)ldowncount = 60;
		if (ldowncount == 30)middletext = "体力が少し回復した。";
		if(ldowncount==31)ldowncount = 39;
		if(ldowncount==39)ldowncount = 60;
		if(ldowncount==40)middletext = "少し周りを見渡してみたが、";
		if(ldowncount==41)middletext = "あまり賑やかな宿屋\n　では無いみたいだ。";
		if(ldowncount==42)ldowncount = 49;
		if(ldowncount==49)ldowncount = 60;
		if(ldowncount==50)middletext = "近くにある\n　手ごろな椅子に腰を下ろした";
		if(ldowncount==51)middletext = "少し休憩したら、また動こう。";
		if(ldowncount==52)ldowncount = 59;
		if(ldowncount==59)ldowncount = 60;
		if(ldowncount==60){
			page = select_pagestart;
			ldowncount = -1;
			selectnox = 0;
			selectnoy = 0;
		}

		if (CheckHitKey(KEY_INPUT_RIGHT)) {
			if (ldowncount == 1
				)selectnoy = 0;
		}
		if (CheckHitKey(KEY_INPUT_RETURN) && keystop == false) {
			mozicount = mozisize * 3;
			if (moziflug == true) {
				mozicount = 0;
				ldowncount++;
				moziflug = false;
			}
			keystop = true;
		}
	}



	mozisize = middletext.size() / 2;
	if (mozicount / 3 >= mozisize) {
		moziflug = true;
	}

	if (CheckHitKey(KEY_INPUT_UP) && keystop == false) {
		if (page == select_page && selectnoy > 0)selectnoy--;
		if (page == lup && lupcount == 3 && selectnoy > 0&&selectnox!=1)selectnoy--;
		if (page == lmid && lmidcount == 0 && selectnoy > 0)selectnoy--;
		if (page == lmid && lmidcount == 10 && selectnoy > 0&&selectnox!=1)selectnoy--;
		if (page == lmid && lmidcount == 20 && selectnoy > 0&&selectnox!=1)selectnoy--;
		if (page == lmid && lmidcount == 30 && selectnoy > 0&&selectnox!=1)selectnoy--;
		if (page == ldown && ldowncount == 1 && selectnoy > 0&&selectnox!=1)selectnoy--;

		keystop = true;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) && keystop == false) {
		if (page == select_page && selectnoy < 2)selectnoy++;
		if (page == lup && lupcount == 3 && selectnoy < 4 && selectnox != 1)selectnoy++;
		if (page == lmid && lmidcount == 0 && selectnoy < 2)selectnoy++;
		if (page == lmid && lmidcount == 10 && selectnoy < 4 && selectnox != 1)selectnoy++;
		if (page == lmid && lmidcount == 20 && selectnoy < 4 && selectnox != 1)selectnoy++;
		if (page == lmid && lmidcount == 30 && selectnoy < 4 && selectnox != 1)selectnoy++;
		if (page == ldown && ldowncount == 1 && selectnoy < 4 && selectnox != 1)selectnoy++;

		keystop = true;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) && keystop == false) {
		if (page == select_page && selectnox > 0)selectnox--;
		if (page == lup && lupcount == 3 && selectnox > 0)selectnox--;
		if (page == lmid && lmidcount == 0 && selectnox > 0)selectnox--;
		if (page == lmid && lmidcount == 10 && selectnox > 0)selectnox--;
		if (page == lmid && lmidcount == 20 && selectnox > 0)selectnox--;
		if (page == lmid && lmidcount == 30 && selectnox > 0)selectnox--;
		if (page == lmid && lmidcount == 40 && selectnox > 0)selectnox--;
		if (page == ldown && ldowncount == 1 && selectnox > 0)selectnox--;

		keystop = true;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) && keystop == false) {
		if (page == select_page && selectnox < 1)selectnox++;
		if (page == lup && lupcount == 3 && selectnox < 1)selectnox++;
		if (page == lmid && lmidcount == 0 && selectnox < 1)selectnox++;
		if (page == lmid && lmidcount == 10 && selectnox < 1)selectnox++;
		if (page == lmid && lmidcount == 20 && selectnox < 1)selectnox++;
		if (page == lmid && lmidcount == 30 && selectnox < 1)selectnox++;
		if (page == lmid && lmidcount == 40 && selectnox < 1)selectnox++;
		if (page == ldown && ldowncount == 1 && selectnox < 1)selectnox++;

		keystop = true;
	}

	if (CheckHitKey(KEY_INPUT_RETURN) && keystop == false) {
		mozicount = 0;
		page++;
		keystop = true;
	}
	if (CheckHitKey(KEY_INPUT_RETURN) == 0 &&
		CheckHitKey(KEY_INPUT_UP) == 0 &&
		CheckHitKey(KEY_INPUT_DOWN) == 0 &&
		CheckHitKey(KEY_INPUT_LEFT) == 0 &&
		CheckHitKey(KEY_INPUT_RIGHT) == 0 &&
		CheckHitKey(KEY_INPUT_BACK) == 0
		) {
		keystop = false;
	}
	
}
void gameDraw() {
	
		midcircle.Move();
	midcircle.Draw();

	int greencolor = GetColor(7,135,60);
	int moegigreencolor = GetColor(0,109,77);
	int nadotyabluecolor = GetColor( 49,114,112);
	int ashbluecolor = GetColor(45,86,103);
	//DrawBox(0, 0, 800, 600, GetColor(7, 135, 60), true);
	/*- - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
	DrawBox(0, 0, 200, 600, nadotyabluecolor, true);
	DrawBox(600, 0, 800, 600, nadotyabluecolor, true);
	DrawBox(0, 0, 800, 200, nadotyabluecolor, true);
	DrawBox(0, 500, 800, 600, nadotyabluecolor, true);
	/*-----------------------------*/
	DrawBox(200,200,600,500,moegigreencolor,false);
	/*-----------------------------*/
	/*DrawBox(0,0,800,600,ashbluecolor,true);*/  //色を試す用

	soro.Drawstatus();


	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			if (lmidcount != 10 &&
				lupcount != 3 &&
				lmidcount != 20 &&
				lmidcount != 30 &&
				lmidcount != 40&&
				ldowncount!=1
				) {
				int selectcolor_2 = 0;
				bool enflug = false;
				if (selectnox == i && selectnoy == j) {
					selectcolor = 255; selectcolor_2 = 0; enflug = true;
				}
				else {
					selectcolor = 00; selectcolor_2 = 210; enflug = false;
				}
				if (selecttext[i * 3 + j].size() / 2 >= 1) {
					DrawBox(45-5 + i * 600, 250 - 5+ j * 90 , 45 + (selecttext[i * 3 + j].size() / 2 * 24 + 10) + i * 600, 250 + 32 + j * 90, GetColor(selectcolor_2, selectcolor_2, selectcolor_2), enflug);
				}
				DrawFormatString(45 + i * 600, 250 + j * 90, GetColor(selectcolor, selectcolor, selectcolor), selecttext[i * 3 + j].c_str());
			}
			if (page == select_page) {
				//DrawFormatString(280 + i * 20, 300 + j * 20, GetColor(255, 255, 255), "ここですねー");
			}

		}
	}
	if (lmidcount!=40&&
		lmidcount == 10||
		lupcount==3||
		lmidcount==20||
		lmidcount==30||
		ldowncount==1
		) {
		for (int i = 0; i < 5; i++) {
				bool enflug = false;
			for (int j = 0; j < 2; j++) {
				
				if (selectnoy == i&&selectnox!=1) {
					selectcolor = 255; enflug = true;
				}
				else {
					selectcolor = 0;enflug = false;
				}
			}int rinzicolor = (selectnox==1&&selectnoy==0)?255:0;
			if (enflug==false) {
				DrawCircle(40,250+i*56+12,2, GetColor(0,0,0),true);
			}
			DrawFormatString(50, 250 + i * 56, GetColor(selectcolor, selectcolor, selectcolor), selecttext[i].c_str());
			
			DrawFormatString(50+600, 250, GetColor(rinzicolor, rinzicolor, rinzicolor), selecttext[5].c_str());

		}
	}
	if (lmidcount == 40) {
		for (int i = 0; i < 2; i++) {
			int selectcolor_2 = 0;
			bool enflug = false;
			if (selectnox == i) {
				selectcolor = 255; selectcolor_2 = 0; enflug = true;
			}
			else {
				selectcolor = 0; selectcolor_2 = 210; enflug = false;
			}
			if (selecttext[i].size() / 2 >= 1) {
				DrawBox(50 - 5 + i * 600, 300-5, 50 + (selecttext[i].size() / 2 * 24 + 10) + i * 600, 300 + 32 , GetColor(selectcolor_2, selectcolor_2, selectcolor_2), enflug);
			}
			DrawFormatString(50+i*600, 300, GetColor(selectcolor, selectcolor, selectcolor), selecttext[i].c_str());
		}
	}
	int rinzicolor =(
		lmidcount==10||lmidcount==12||
		lmidcount==20||lmidcount==22||
		lmidcount==30||lmidcount==32
		)?0 : 200;
	DrawFormatString(250, 500+5, GetColor(rinzicolor, rinzicolor, 0), undertext.c_str());

	if(lmidcount>=44!=lmidcount<=50)
	DrawFormatString(350, 200-28*2, GetColor(255, 255, 255), messegetext.c_str());

	if (uptext.size() != 0) {
		int upsize=uptext.size();
		int text = upsize / 2+1;
		DrawBox(550, 40, 550+42+text*48, 40 + 20 + 32 * 1, GetColor(255, 255, 255), true);
		DrawBox(550 + 1, 40 + 1 , 550+42 - 1+ text * 48, 92 - 1, GetColor(50, 50, 50), false);
		SetFontSize(48);
		DrawFormatString(592, 42, GetColor(0, 0, 0), uptext.c_str());
		SetFontSize(24);
	}
	if (choicetext.size() != 0) {
		SetFontSize(16);
		DrawFormatString(575, 32 + 4 + 20 + 40, GetColor(255, 255, 255), choicetext.c_str());
		SetFontSize(24);
	}

	//DrawFormatString(249, 299, GetColor(255, 255, 255), middletext.c_str());
	//DrawFormatString(251, 301, GetColor(255, 255, 255), middletext.c_str());
	//DrawFormatString(249, 301, GetColor(255, 255, 255), middletext.c_str());
	//DrawFormatString(251, 299, GetColor(255, 255, 255), middletext.c_str());


	mozicount++;
	if (page == start_page) {
		SetFontSize(48);
	}
	//メッセージウィンドウにテキストを表示する
	std::wstring message_a = StringToWString(middletext);
	std::string disp_message_a = WStringToString(message_a.substr(0, mozicount / 3));
	DrawFormatString(230-1, 300-1, GetColor(255, 255, 255), disp_message_a.c_str());
	//メッセージウィンドウにテキストを表示する
	std::wstring message_b = StringToWString(middletext);
	std::string disp_message_b = WStringToString(message_b.substr(0, mozicount / 3));
	DrawFormatString(230+1, 300+1, GetColor(255, 255, 255), disp_message_b.c_str());
	//メッセージウィンドウにテキストを表示する
	std::wstring message_c = StringToWString(middletext);
	std::string disp_message_c = WStringToString(message_c.substr(0, mozicount / 3));
	DrawFormatString(230+1, 300, GetColor(255, 255, 255), disp_message_c.c_str());
	//メッセージウィンドウにテキストを表示する
	std::wstring message_d = StringToWString(middletext);
	std::string disp_message_d = WStringToString(message_d.substr(0, mozicount / 3));
	DrawFormatString(230-1, 300, GetColor(255, 255, 255), disp_message_d.c_str());
	//メッセージウィンドウにテキストを表示する
	std::wstring message_e = StringToWString(middletext);
	std::string disp_message_e = WStringToString(message_e.substr(0, mozicount / 3));
	DrawFormatString(230, 300, GetColor(0, 0, 0), disp_message_e.c_str());

	if (page == start_page)SetFontSize(24);

	



}
void gameDelete() {

}