#include "DxLib.h"
#include <string>
#include"maneger.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(false);
	ChangeWindowMode(TRUE);	//ウィンドウモードにする
	SetGraphMode(800, 600, 32);	//ウィンドウサイズを設定する

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);	//裏画面を描画対象へ
	//初期化
	Init();
	//メイン処理
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_DECIMAL) == 0)
	{
		clsDx();
		
		Debug();
		Updete();
		Draw();
		
		ScreenFlip();		//裏画面と表画面の入替
		ClearDrawScreen();	//裏画面の描画を全て消去

	}
	//メモリ解放
	Delete();

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

