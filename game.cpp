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

//wstring��string�֕ϊ�
std::string WStringToString(std::wstring oWString)
{
	// wstring �� SJIS
	int iBufferSize = WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str()
		, -1, (char*)NULL, 0, NULL, NULL);
	// �o�b�t�@�̎擾
	CHAR* cpMultiByte = new CHAR[iBufferSize];
	// wstring �� SJIS
	WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str(), -1, cpMultiByte
		, iBufferSize, NULL, NULL);
	// string�̐���
	std::string oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);
	// �o�b�t�@�̔j��
	delete[] cpMultiByte;
	// �ϊ����ʂ�Ԃ�
	return(oRet);
}
std::wstring StringToWString(std::string oString)
{
	//  SJIS��wstring
	std::wstring ws;
	int iBufferSize = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, oString.c_str()
		, -1, (wchar_t*)NULL, 0);

	// �o�b�t�@�̎擾
	wchar_t* cpMultiByte = new wchar_t[iBufferSize];
	// wstring �� SJIS
	MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, cpMultiByte
		, iBufferSize);
	// wstring�̐���
	std::wstring oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);
	// �o�b�t�@�̔j��
	delete[] cpMultiByte;
	// �ϊ����ʂ�Ԃ�
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
		middletext = "�����͍L��";
		page++;
	}
	if (page == select_pagestart) {
		choicetext = "";
		middletext = "";
		uptext = "�L��";
		undertext = "�\���L�[�őI�����悤";
		/*�������牺__��- - - - - - - - - - - - - - -*/
		selecttext[0] = "����";
		selecttext[1] = "���^��";
		selecttext[2] = "����";
		selecttext[3] = "�E��";
		selecttext[4] = "�E�^��";
		selecttext[5] = "�E��";
		/*- - - - - - - - - - - - - - - - - - - - - -*/
		page++;
	}
	if (page == select_page) {

		if (selectnox == 0 && selectnoy == 0) {
			selecttext[0] = "����";
			messegetext = "�����͕񍐂��邽�ߍs��";
		}
		if (selectnox == 0 && selectnoy == 1) {
			selecttext[1] = "���^��";
			messegetext = "�����ɂ͓���n��";
		}
		if (selectnox == 0 && selectnoy == 2) {
			selecttext[2] = "����";
			messegetext = "�����̗͉͑񕜂�";
		}
		if (selectnox == 1 && selectnoy == 0) {
			selecttext[3] = "�E��";
			messegetext = "�����͂������҂�";
		}
		if (selectnox == 1 && selectnoy == 1) {
			selecttext[4] = "�E�^��";
			messegetext = "�����͂��̑��֘A��";
		}
		if (selectnox == 1 && selectnoy == 2) {
			selecttext[5] = "�E��";
			messegetext = "�T�����邽�߂�";
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
		uptext = "�񍐊�";

		if (lupcount == -1) {
			moziflug = false;
			lupcount++;
		}
		if (lupcount == 0)middletext = "�G���^�[�L�[��\n���̕���ǂނ��Ƃ��ł��邼��";
		if (lupcount == 1)middletext = "�����ł͍��x�̐��ʂ�\n�N�ɕ񍐂��Ă��炤";
		if (lupcount == 2)middletext = "���A . . . .";
		if (lupcount == 3) {
			choicetext = "";
			middletext = "";
			undertext = "�\���L�[�őI�����悤";
			messegetext = "����܂łɉ������ʂ������H";
			selecttext[0] = "�^�������ɂ����ɂ���";
			selecttext[1] = "�G��|�����B";
			selecttext[2] = "�������������B";
			selecttext[3] = "���ꂩ�炷��̂�";
			selecttext[4] = "�ق��Ă���B";
			selecttext[5] = "�L�Ԃɖ߂�";
		}
		if (lupcount == 4) {
			if (selectnox == 0 && selectnoy == 0) {
				lupcount = 10;
				choicetext = "�^�������ɂ����ɂ���";
			}
			if (selectnox == 0 && selectnoy == 1) {
				lupcount = 20;
				choicetext = "�G��|�����B";
			}
			if (selectnox == 0 && selectnoy == 2) {
				lupcount = 30;
				choicetext = "�������������B";
			}
			if (selectnox == 0 && selectnoy == 3) {
				lupcount = 40;
				choicetext = "���ꂩ�炷��̂�";
			}
			if (selectnox == 0 && selectnoy == 4) {
				lupcount = 50;
				choicetext = "�ق��Ă���B";
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
		if (lupcount == 10)middletext = "�ӂށA�^����������Ƃ́A\n �f���Ȑ��i�����Ă����";
		if (lupcount == 11)middletext = "���̌���������@�����";
		if (lupcount == 12)middletext = "�����ɗ���̂�\n ���߂ĂȂ̂��낤�ȁA";
		if (lupcount == 13)middletext = "�����ł͙N��";
		if (lupcount == 14)middletext = "�񍐂����Ă��炤��ł���";
		if (lupcount == 15)middletext = "�퓬�A�������A";
		if (lupcount == 16)middletext = "���͉���������";
		if (lupcount == 17)middletext = "�����񍐂��Ă��炢����";
		if (lupcount == 18)middletext = "�ȏゾ";
		if (lupcount == 19) lupcount = 3;

		if (lupcount == 20)middletext = "�������A";
		if (lupcount == 21)middletext = "�������ݓG�΂��Ă�҂ɂ���\n ��������K�v�͂Ȃ����������";
		if (lupcount == 22)middletext = "�|�����G����\n �h���b�v����A�C�e����";
		if (lupcount == 23)middletext = "����Ȃǂ̂��X�ɔ���͂炢";
		if (lupcount == 24)middletext = "���g�̑����𐮂��邪�悢";
		if (lupcount == 25)middletext = "�ꉞ�A�퓬�̃R�c��`�����悤";
		if (lupcount == 26)middletext = "�����݁A�퓬������܂���";
		if (lupcount == 27)middletext = "���ǉ����邩���s���ł�";
		if (lupcount == 28)middletext = "���C�܂܂ɍ쐬���ł������܂��B";
		if (lupcount == 29)lupcount = 3;

		if (lupcount == 30)middletext = "�������Ƃ�\n �}�C�y�[�X�ɕ���ł����";
		if (lupcount == 31)middletext = "�ǂ�ȕ����������̂��̂�";
		if (lupcount == 32)middletext = "�����h��A";
		if (lupcount == 33)middletext = "���Օi�Ȃǂ𔃂���";
		if (lupcount == 34)middletext = "���̌�̖`���ɖ𗧂ł��낤";
		if (lupcount == 35)middletext = "���͏��Ղ��Ⴉ��A";
		if (lupcount == 36)middletext = "�K�v�Ȃ�����������";
		if (lupcount == 37)middletext = "���̂����A\n �ǉ�����镨�����邩�������";
		if (lupcount == 38)middletext = "���傭���傭���Ƃ悢��";
		if (lupcount == 39)lupcount = 3;

		if (lupcount == 40)middletext = "���ށA���̈ӋC��ǂ�";
		if (lupcount == 41)middletext = "���ꂩ��͐F�X�T����";
		if (lupcount == 42)middletext = "�l�X�ȂƂ����\n �`������ł��낤";
		if (lupcount == 43)middletext = "���̖`��������";
		if (lupcount == 44)middletext = "�y����ł��邪�悢";
		if (lupcount == 45)middletext = "���Ⴊ�A\n �s���l�܂�Ƃ��A";
		if (lupcount == 46)middletext = "�@��������ǂ���\n ������Ȃ�����";
		if (lupcount == 47)middletext = "�����������";
		if (lupcount == 48)middletext = "���̎��́A\n �܂������֗���Ƃ悢��";
		if (lupcount == 49)lupcount = 3;

		if (lupcount == 50)middletext = "�ǖقȂ̂���";
		if (lupcount == 51)middletext = "����......";
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
		uptext = "���X";
		if (lmidcount == -1) {
			moziflug = false;
			selectnox = 0;
			selectnoy = 0;
			lmidcount++;
		}
		if (lmidcount == 0) {
			choicetext = "";
			middletext = "";
			undertext = "�\���L�[�őI�����悤";
			messegetext = "�ǂ��ɍs�������ȁH";
			selecttext[0] = "���";
			selecttext[1] = "���퉮";
			selecttext[2] = "�h�";
			selecttext[3] = "�肢��";
			selecttext[4] = "�ӂ������";
			selecttext[5] = "�L�Ԃɖ߂�";
		}
		if (lmidcount == 1) {
			moziflug = false;
			if (selectnox == 0 && selectnoy == 0) {
				lmidcount = 10;
				choicetext = "���";
			}
			if (selectnox == 0 && selectnoy == 1) {
				lmidcount = 20;
				choicetext = "���퉮";
			}
			if (selectnox == 0 && selectnoy == 2) {
				lmidcount = 30;
				choicetext = "�h�";
			}
			if (selectnox == 1 && selectnoy == 0) {
				lmidcount = 40;
				choicetext = "�肢��";
			}
			if (selectnox == 1 && selectnoy == 1) {
				lmidcount = 50;
				choicetext = "�ӂ������i�����j";
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
			
			undertext = "�u�����͓������I�v";
			middletext = "";
			selecttext[0] = "�񕜖�(����)";
			selecttext[1] = "�}�i��";
			selecttext[2] = "�񕜖�(����)";
			selecttext[3] = "������";
			selecttext[4] = "�������߂́H";
			selecttext[5] = "���X���o��";
			if (selectnox == 0 && selectnoy == 0)messegetext = "�̗͂��񕜂����\n�@�h���܂������Ă���";
			if (selectnox == 0 && selectnoy == 1)messegetext = "�C�����̐؂�ւ����ł����\n�@�������킵��..."; 
			if (selectnox == 0 && selectnoy == 2)messegetext = "�̗͂�傫���񕜂����\n�@�O��������I"; 
			if (selectnox == 0 && selectnoy == 3)messegetext = "��Ԃ��グ�镲\n�@�y����..�����!������nk...."; 
			if (selectnox == 0 && selectnoy == 4)messegetext = "�ڈڂ肵�Ă��܂���\n�@�������߂𕷂��Ă݂�"; 
			if (selectnox == 1 && selectnoy == 0)messegetext = "���X�𗣂��"; 
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
				middletext = "�񕜖�˖��x����I";
				undertext = "�񕜖����ɓ��ꂽ";
			}
			if (selectnox == 0 && selectnoy == 1) {
				middletext = "������I���^�����̃}�i�ۂ���I";
				undertext = "�}�i�ۂ���ɓ��ꂽ";
			}
			if (selectnox == 0 && selectnoy == 2) {
				middletext = "����𔃂��Ƃ�\n ���q���񂨖ڂ������ˁI";
				undertext = "�񕜖�i��j����ɓ��ꂽ";
			}
			if (selectnox == 0 && selectnoy == 3) {
				middletext = "���񂽁A\n ����𔃂��̂́A��̈�������";
				undertext = "����������ɓ��ꂽ";
			}
			if (selectnox == 0 && selectnoy == 4) {
				middletext = "�����A�񕜖��\n�@�����Ă������U���\n�@�@���C����";
				undertext = "�񕜖򂪂������߂�������";
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
			undertext = "�u���킾�A�؂ꕨ�Ȃ炱���ɗ��ȁv";
			middletext = "";
			selecttext[0] = "�i�C�t";
			selecttext[1] = "�";
			selecttext[2] = "����";
			selecttext[3] = "��";
			selecttext[4] = "�������߂́H";
			selecttext[5] = "���X���o��";
			if (selectnox == 0 && selectnoy == 0)messegetext = "�育��ȃi�C�t\n�@���͉ʕ��i�C�t";
			if (selectnox == 0 && selectnoy == 1)messegetext = "�؂ꖡ���Q�ȕ\n�@�o�n���";
			if (selectnox == 0 && selectnoy == 2)messegetext = "�����Ȍ�\n�@�@���؂�^�C�v�̂��";
			if (selectnox == 0 && selectnoy == 3)messegetext = "�Y��Ȕg��̓�\n�@�������J�b�R����";
			if (selectnox == 0 && selectnoy == 4)messegetext = "����͉��������̂��A\n�@�������߂𕷂��Ă݂�";
			if (selectnox == 1 && selectnoy == 0)messegetext = "���X�𗣂��";
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
				middletext = "�i�C�t��,�K�тɋC������";
				undertext = "�i�C�t����ɓ��ꂽ";
			}
			if (selectnox == 0 && selectnoy == 1) {
				middletext = "���,�����Ǝ���ꂵ��";
				undertext = "�����ɓ��ꂽ";
			}
			if (selectnox == 0 && selectnoy == 2) {
				middletext = "������,�]�藐�\�Ɉ����Ȃ�";
				undertext = "��������ɓ��ꂽ";
			}
			if (selectnox == 0 && selectnoy == 3) {
				middletext = "����,���J�Ɉ�����";
				undertext = "������ɓ��ꂽ";
			}
			if (selectnox == 0 && selectnoy == 4) {
				middletext = "������������";
				undertext = "����ȊO���g���炵��";
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
			undertext = "�u�h���[�@���͒����ˁ[�H�v";
			middletext = "";
			selecttext[0] = "���̕�";
			selecttext[1] = "�z�̕�";
			selecttext[2] = "�Z";
			selecttext[3] = "����q";
			selecttext[4] = "�������߂́H";
			selecttext[5] = "���X���o��";
			if (selectnox == 0 && selectnoy == 0)messegetext = "���łł�����\n�@���킲�킵�Ă���";
			if (selectnox == 0 && selectnoy == 1)messegetext = "��G�肪������\n�@���S�n���悳������";
			if (selectnox == 0 && selectnoy == 2)messegetext = "�������肵���Z\n�@�P�����Ă���̂͏d������";
			if (selectnox == 0 && selectnoy == 3)messegetext = "�����肩���т炾\n�@�ȒP�ɂ͐؂�Ȃ����낤";
			if (selectnox == 0 && selectnoy == 4)messegetext = "�ǂ̕��𔃂����H\n�@�������߂𕷂��Ă݂�";
			if (selectnox == 1 && selectnoy == 0)messegetext = "���X�𗣂��";
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
				middletext = "���̕��͂�������[";
				undertext = "���̕�����ɓ��ꂽ";
			}
			if (selectnox == 0 && selectnoy == 1) {
				middletext = "�͂�T�V���c�ˁ[";
				undertext = "�z�̕�����ɓ��ꂽ";
			}
			if (selectnox == 0 && selectnoy == 2) {
				middletext = "��낢���Ē��Â炢��ˁ[";
				undertext = "�Z����ɓ��ꂽ";
			}
			if (selectnox == 0 && selectnoy == 3) {
				middletext = "�����肩���т炾��[\n �키�񂾂ˁ[";
				undertext = "����q����ɓ��ꂽ";
			}
			if (selectnox == 0 && selectnoy == 4) {
				middletext = "�z�̕��͂������߂���[";
				undertext = "���̕���蒅�₷���炵��";
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
			messegetext = "���񂽁A�肤�����H";
			selecttext[0] = "�͂�";
			selecttext[1] = "������";
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
			middletext = "�Ȃ�A�邱�Ƃ���";
		}
		if (lmidcount == 43) {
			lmidcount = 0;
		}
		if (lmidcount == 44) lmidcount = 49;
		if (lmidcount == 45) middletext = "���[�[�[�[�[�[��";
		if (lmidcount == 46) middletext = "���̂܂܂ł�\n ���܂�����Ă���������\n�@�@���̏�������Ă���ˁA";
		if (lmidcount == 47) middletext = "����Ȋق��Đ肢������ق�\n�@�����󋵂���Ȃ��݂�����";
		if (lmidcount == 48) middletext = "�V�������Ƃɒ��킷��̂�\n�@�Y�ꂸ�ɂ�";
		if (lmidcount == 49) lmidcount = 0;

		if (lmidcount == 50)middletext = "������\n �����̂��X���������ԘH�n";
		if (lmidcount == 51)middletext = "���퉮�A�h��A\n ����A�肢��������B";
		if (lmidcount == 52)middletext = "���ꂼ��̂��X�̓X���";
		if (lmidcount == 53)middletext = "���I�Ȑl�������݂���";
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
		uptext = "�h";
		if (ldowncount == -1) {
			moziflug = false;
			selectnox = 1;
			selectnoy = 0;
			ldowncount++;
		}
		if (ldowncount == 0)middletext = "�����͏h������I\n �~�܂��Ă��������H";
		if (ldowncount == 1) {
			undertext = "�ǂ�����H";
			middletext = "";
			selecttext[0] = "�����Ă�";
			selecttext[1] = "��ѐH�ׂĂ�";
			selecttext[2] = "�����x��ł�";
			selecttext[3] = "�ӂ�����Ă݂�";
			selecttext[4] = "�֎q�ɍ���";
			selecttext[5] = "�h���o��";
			if (selectnox == 0 && selectnoy == 0)messegetext = "�̗͂��S�񕜂���";
			if(selectnox==0&&selectnoy==1)messegetext = "�̗͂�������";
			if(selectnox==0&&selectnoy==2)messegetext = "�̗͂�������";
			if(selectnox==0&&selectnoy==3)messegetext = "���̏h���������čs����";
			if(selectnox==0&&selectnoy==4)messegetext = "�����߂��̈֎q�ɍ��낤";
			if(selectnox==1&&selectnoy==0)messegetext ="�h������o�Ă���";
		}
		if (ldowncount == 2) {
			moziflug = false;
			if (selectnox == 0 && selectnoy == 0) {
				choicetext = "�����Ă�";
				ldowncount = 10; 
			}
			if (selectnox == 0 && selectnoy == 1) {
				choicetext = "��ѐH�ׂĂ�";
				ldowncount = 20;
			}
			if (selectnox == 0 && selectnoy == 2) {
				choicetext = "�����x��ł�";
				ldowncount = 30;
			}
			if (selectnox == 0 && selectnoy == 3) {
				choicetext = "�ӂ�����Ă݂�";
				ldowncount = 40;
			}
			if (selectnox == 0 && selectnoy == 4) {
				choicetext = "�֎q�ɍ���";
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
		if (ldowncount == 10)middletext = "�̗͂��S�񕜂����I";
		if(ldowncount==11)ldowncount = 19;
		if(ldowncount==19)ldowncount = 60;
		if (ldowncount == 20)middletext = "�̗͂����񕜂����I";
		if(ldowncount==21)ldowncount = 29;
		if(ldowncount==29)ldowncount = 60;
		if (ldowncount == 30)middletext = "�̗͂������񕜂����B";
		if(ldowncount==31)ldowncount = 39;
		if(ldowncount==39)ldowncount = 60;
		if(ldowncount==40)middletext = "������������n���Ă݂����A";
		if(ldowncount==41)middletext = "���܂���₩�ȏh��\n�@�ł͖����݂������B";
		if(ldowncount==42)ldowncount = 49;
		if(ldowncount==49)ldowncount = 60;
		if(ldowncount==50)middletext = "�߂��ɂ���\n�@�育��Ȉ֎q�ɍ������낵��";
		if(ldowncount==51)middletext = "�����x�e������A�܂��������B";
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
	/*DrawBox(0,0,800,600,ashbluecolor,true);*/  //�F�������p

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
				//DrawFormatString(280 + i * 20, 300 + j * 20, GetColor(255, 255, 255), "�����ł��ˁ[");
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
	//���b�Z�[�W�E�B���h�E�Ƀe�L�X�g��\������
	std::wstring message_a = StringToWString(middletext);
	std::string disp_message_a = WStringToString(message_a.substr(0, mozicount / 3));
	DrawFormatString(230-1, 300-1, GetColor(255, 255, 255), disp_message_a.c_str());
	//���b�Z�[�W�E�B���h�E�Ƀe�L�X�g��\������
	std::wstring message_b = StringToWString(middletext);
	std::string disp_message_b = WStringToString(message_b.substr(0, mozicount / 3));
	DrawFormatString(230+1, 300+1, GetColor(255, 255, 255), disp_message_b.c_str());
	//���b�Z�[�W�E�B���h�E�Ƀe�L�X�g��\������
	std::wstring message_c = StringToWString(middletext);
	std::string disp_message_c = WStringToString(message_c.substr(0, mozicount / 3));
	DrawFormatString(230+1, 300, GetColor(255, 255, 255), disp_message_c.c_str());
	//���b�Z�[�W�E�B���h�E�Ƀe�L�X�g��\������
	std::wstring message_d = StringToWString(middletext);
	std::string disp_message_d = WStringToString(message_d.substr(0, mozicount / 3));
	DrawFormatString(230-1, 300, GetColor(255, 255, 255), disp_message_d.c_str());
	//���b�Z�[�W�E�B���h�E�Ƀe�L�X�g��\������
	std::wstring message_e = StringToWString(middletext);
	std::string disp_message_e = WStringToString(message_e.substr(0, mozicount / 3));
	DrawFormatString(230, 300, GetColor(0, 0, 0), disp_message_e.c_str());

	if (page == start_page)SetFontSize(24);

	



}
void gameDelete() {

}