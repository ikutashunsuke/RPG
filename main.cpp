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

//fpsŠÖ˜A
int CountFps;
int StartTimeFps;
int SampleNumFps = GAME_FPS_SPEED;
int CalcFps;

VOID MY_FPS_UPDATE(VOID);
VOID MY_FPS_WAIT(VOID);
VOID MY_FPS_DRAW(VOID);

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);
	ChangeWindowMode(TRUE);
	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);


	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	int Handle;
	Handle = LoadGraph("..\\‰æ‘œ\\char.jpg");
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }
		if (ClearDrawScreen() != 0) { break; }



		//MY_ALL_KEYDOWN_UPDATE();
		MY_FPS_UPDATE();

		DrawGraph(50, 100, Handle, TRUE);

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