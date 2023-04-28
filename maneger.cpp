#include<DxLib.h>
#include"string"
#include"maneger.h"
#include"game.h"
#include"keyboard.h"

namespace {
	
}
void Debug() {
	if (gamescene == title_scene) {
		DrawFormatString(400, 5, GetColor(255, 255, 255), "何もなかったら\nエンターキー押してー\nあと、\n作ってないところ多すぎて\n復帰不可な所あるから\n気を付けて\n");
		DrawFormatString(400, 5 + 24 * 7, GetColor(255, 255, 255), "・復帰用コマンド；\nスペースキー＋①\n");
	}
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		DrawBox(0,0,200,200,GetColor(0,0,0),true);
		gameDebug();

		if (gamescene == 0) {
			printfDx("\n\n\n\t\ttitlescene\n");
		}
		else if (gamescene == 1) {
			printfDx("\n\n\n\t\tgamescene\n");
		}
		else if (gamescene == 2) {
			printfDx("\n\n\n\t\tendscene\n");
		}
		else {
			printfDx("\n\tscenes:%d\n", gamescene);
		}
	}
	else {
		printfDx("\n\n\t\t\t\t\t\tSpace_Debug\n");
	}
}
void Init() {
	gamescene = title_scene;
	keystop = false;

	gameInit();
}
void Updete() {
	
	switch (gamescene) {
	case title_scene:
		break;
	case game_scene:
		gameUpdete();
		break;
	case end_scene:
		break;
	default:
		break;
	}
	if (CheckHitKey(KEY_INPUT_NUMPAD0))gamescene = title_scene;
	if (CheckHitKey(KEY_INPUT_NUMPAD1))gamescene = end_scene;
	if (CheckHitKey(KEY_INPUT_NUMPAD2))gamescene = 50;
	if (CheckHitKey(KEY_INPUT_RETURN)&&keystop==false) {
		if (gamescene == title_scene) {
			gamescene = game_scene;
		}
		keystop = true;
	}
	if (CheckHitKey(KEY_INPUT_RETURN) == 0
		)keystop = false;
}
void Draw() {
	switch (gamescene) {
	case title_scene:
		DrawFormatString(400, 5, GetColor(255, 255, 255), "エンターで始まり、");
		
		break;
	case game_scene:
		gameDraw();
		break;
	case end_scene:
		break;
	default:
		DrawBox(0,0,800,600,GetColor(7,135,60),true);
		break;
	}

}
void Delete() {

	gameDelete();
}