//#include<math>
#include "DxLib.h"

#define GAME_WIDTH 800
#define GAME_HEIGHT 600
#define GAME_COLOR 32

#define GAME_FPS_SPEED 60

#define SET_WINDOW_ST_MODE_DEFAULT			0
#define SET_WINDOW_ST_MODE_TITLE_NONE		1
#define SET_WINDOW_ST_MODE_TITLE_FLAME_NONE	2
#define SET_WINDOW_ST_MODE_FLAME_NONE		3

enum GAME_SCENE {
	GAME_SCENE_TITLE,	//タイトル画面
	GAME_SCENE_PLAY,	//プレイ画面
	GAME_SCENE_END		//エンド画面
};

//fps関連
int CountFps;
int StartTimeFps;
int SampleNumFps = GAME_FPS_SPEED;
float CalcFps;

int GameSceneNow = (int)GAME_SCENE_TITLE;//最初の画面

char AllKeyState[256];

VOID MY_FPS_UPDATE(VOID);
VOID MY_FPS_WAIT(VOID);
VOID MY_FPS_DRAW(VOID);

VOID MY_GAME_TITLE(VOID);


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);
	ChangeWindowMode(TRUE);
	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);


	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	int Handle;
	//Handle = LoadGraph("..\\画像\\char.jpg");
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }
		if (ClearDrawScreen() != 0) { break; }



		//MY_ALL_KEYDOWN_UPDATE();
		MY_FPS_UPDATE();

		switch (GameSceneNow)
		{
		case(int)GAME_SCENE_TITLE:
			MY_GAME_TITLE();
			break;
		}

		//DrawGraph(50, 100, Handle, TRUE);

		MY_FPS_DRAW();

		ScreenFlip();

		MY_FPS_WAIT();

	}



	WaitKey();
	DxLib_End();
	return 0;
}

VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0)
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == GAME_FPS_SPEED)
	{
		int now = GetNowCount();
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)GAME_FPS_SPEED);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}

VOID MY_FPS_DRAW(VOID)
{

	DrawFormatString(0, 0, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);

	return;
}

VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;
	int waitTime = CountFps * 1000 / GAME_FPS_SPEED - resultTime;

	if (waitTime > 0)
	{
		Sleep(waitTime);
	}
	return;
}

VOID MY_GAME_TITLE(VOID)
{
	if (AllKeyState[KEY_INPUT_RETURN] != 0)
	{
		GameSceneNow = (int)GAME_SCENE_PLAY;
	}
	DrawGraph(BackGround.X, BackGround.Y, BackGround.Handle, TRUE);
	char title1[64] = "タイトル画面";//表示する画面
	SetFontSize(64);//フォントサイズ変更

}