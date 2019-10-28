//#include<math>
#include "DxLib.h"

#define GAME_WIDTH 800
#define GAME_HEIGHT 600
#define GAME_COLOR 32

#define GAME_FPS_SPEED 60

//fpsŠÖ˜A
int CountFps;
int StartTimeFps;
int SampleNumFps;
int CalcFps;

VOID MY_FPS_UPDATE(VOID);
VOID MY_FPS_WAIT(VOID);
VOID MY_FPS_DRAW(VOID);

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE);
	DxLib_Init();
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);

	int Handle;
	Handle = LoadGraph("‰æ‘œ/char.jpg");
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }
		if (ClearDrawScreen() != 0) { break; }

		//MY_ALL_KEYDOWN_UPDATE();
		MY_FPS_UPDATE();

		DrawGraph(50,100,Handle,TRUE);

		MY_FPS_DRAW();
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

	if (CountFps == SampleNumFps)
	{
		int now = GetNowCount();
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
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