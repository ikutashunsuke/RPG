//#include<math>
#include "DxLib.h"

#define GAME_WIDTH 800
#define GAME_HEIGHT 600
#define GAME_COLOR 32

#define GAME_BACKGROUND "..\画像\\背景.jpg"
#define GAME_CHARA "..\\画像\\char.jpg"

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

//########## 構造体 ##########
struct GAZOU {
	int Handle;
	char FilePath[128];
	int X;
	int Y;
	int Width;
	int Height;
	int C_Width;
	int C_Height;
	int MoveSpeed;
	BOOL IsView;
};

GAZOU chara;

//fps関連
int CountFps;
int StartTimeFps;
int SampleNumFps = GAME_FPS_SPEED;
float CalcFps;

int GameSceneNow = (int)GAME_SCENE_TITLE;//最初の画面

char AllKeyState[256];

VOID MY_ALL_KEYDOWN_UPDATE(VOID);

VOID MY_FPS_UPDATE(VOID);
VOID MY_FPS_WAIT(VOID);
VOID MY_FPS_DRAW(VOID);

//VOID MY_DRAW_PLAY_INFO(VOID);//プレイ画面

VOID MY_GAME_TITLE(VOID);//タイトル画面
VOID MY_GAME_END(VOID);//エンド画面

VOID MY_GAZOU_LOAD(VOID);

int Handle_title;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);
	ChangeWindowMode(TRUE);
	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);

	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	if (MY_GAZOU_LOAD(&chara, 0, 0, GAME_WIDTH / 2, GAME_HEIGHT / 2, GAME_CHARA) == FALSE) { return -1; }

	int Handle;
	Handle = LoadGraph("..\\画像\\char.jpg");

	Handle_title = LoadGraph("..\\画像\\背景.jpg");

	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }
		if (ClearDrawScreen() != 0) { break; }

		MY_ALL_KEYDOWN_UPDATE();
		MY_FPS_UPDATE();

		switch (GameSceneNow)
		{
		case(int)GAME_SCENE_TITLE:
			MY_GAME_TITLE();


			break;
		case(int)GAME_SCENE_PLAY:

			DrawGraph(50, 100, Handle, TRUE);

			if (AllKeyState[KEY_INPUT_UP] != 0)
			{
				/*if (GAME_CHARA.Y - GAME_CHARA.MoveSpeed > 0)
				{
					.Y -= GAME_CHARA.MoveSpeed;
				}*/
			}

			break;


		case(int)GAME_SCENE_END:
			MY_GAME_END();
			break;


		default:
			break;
		}


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

	DrawGraph(0,0,Handle_title,TRUE);

	char title1[64] = "タイトル画面";//表示する画面
	SetFontSize(64);//フォントサイズ変更
	DrawString(100, 100, &title1[0],GetColor(255,255,255));
	SetFontSize(24);

}

VOID MY_GAME_END(VOID)
{
	char EndWin[64] = "GAME CLEAR";
	char EndLose[64] = "GAME OVER";

	SetFontSize(100);
}

VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	char TempKey[256];

	GetHitKeyStateAll(TempKey);

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)
		{
			AllKeyState[i]++;
		}
		else
		{
			AllKeyState[i] = 0;
		}
	}
	return;
}

VOID MY_GAZOU_LOAD(GAZOU*g,int x,int y,const char*path)
{
	wsprintf(g->FilePath, path);
	g->Handle = LoadGraph(g -> FilePath);

	if (g->Handle == -1) { return FALSE; }

	GetGraphSize(g->Handle, &g->Width, &g->Height);
	g->X = x;
	g->Y = y;
	g->C_Width = g->Width / 2;
	g->C_Height = g->Height / 2;

	g->MoveSpeed = 4;
	g->IsView = TRUE;

	return TRUE;
}