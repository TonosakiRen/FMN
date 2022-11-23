#include "GameClear.h"
#include "Key.h"
#include "ControllerInput.h"

void GameClear::Init()
{
	Time = 0;

	TitleDrawFlag = false;
	RestartTimeFlag = false;
	pargectflag = false;

	RestartCountNum = 0;
	DrawNum = 0;

	Ealpha = 0;

	GameClearText.Pos.y = 400;
	Num.Color = 0xFFFFFFFF;
	Num10.Color = 0xFFFFFFFF;
	RestartCount.Color = 0xFFFFFFFF;
}

void GameClear::Update(int restartcount)
{
	RestartCountNum = restartcount;
	if (Time > 150) {
		RestartTimeFlag = true;
		pargectflag = true;
		if (Ealpha < 255) {
			Ealpha++;
		}
	}

	if (Time > 270) {
		TitleDrawFlag = true;
	}

	Time++;

	TitleBack.Color = 0x20d6c7FF;

	if (RestartCountNum <= 0) {
		GameClearText.Pos.y = 120;
		Num.Color = 0xFFEE00FF;
		Num10.Color = 0xFFEE00FF;
		RestartCount.Color = 0xFFEE00FF;
	}
	else {
		GameClearText.Pos.y = 400;
		Num.Color = 0xFFFFFFFF;
		Num10.Color = 0xFFFFFFFF;
		RestartCount.Color = 0xFFFFFFFF;
	}

	if (TitleDrawFlag == true) {
		if (Key::IsTrigger(DIK_K) || Controller::IsTriggerButton(0, Controller::bA)) {
			TitleFlag = true;
		}
	}
}

void GameClear::Draw(Screen& screen, int numgra,int Ending_Gra, int gamecleargra,int e)
{
	if (TitleDrawFlag == true) {
		GameClearQuadDraw(TitleBack, Ending_Gra);
	}
	if (RestartTimeFlag == true) {
		GameClearQuadDraw(RestartCount, Ending_Gra);

		DrawNum = RestartCountNum % 10;
		GameClearQuadDraw(Num, numgra);
		
		if (RestartCountNum / 10 != 0) {
			DrawNum = RestartCountNum / 10;
			GameClearQuadDraw(Num10, numgra);
		}

		if (RestartCountNum <= 0) {
			GameClearQuadDraw(E, gamecleargra);
			if (pargectflag) {
				GameClearQuadDraw(Parfect, Ending_Gra);
			}
		}
	}

	GameClearQuadDraw(GameClearText, gamecleargra);

	
}

void GameClear::GameClearQuadDraw(GameClearStruct select, int tex) {
	if (select.IMAGELINE == 99) {
		Novice::DrawQuad(
			select.Pos.x - select.Size.x / 2, select.Pos.y - select.Size.y / 2,
			select.Pos.x + select.Size.x / 2, select.Pos.y - select.Size.y / 2,
			select.Pos.x - select.Size.x / 2, select.Pos.y + select.Size.y / 2,
			select.Pos.x + select.Size.x / 2, select.Pos.y + select.Size.y / 2,
			DrawNum * select.Size.x, 0,
			select.Size.x, select.Size.y,
			tex, select.Color);
	}
	else if (select.IMAGELINE == 999) {
		Novice::DrawQuad(
			select.Pos.x - select.Size.x / 2, select.Pos.y - select.Size.y / 2,
			select.Pos.x + select.Size.x / 2, select.Pos.y - select.Size.y / 2,
			select.Pos.x - select.Size.x / 2, select.Pos.y + select.Size.y / 2,
			select.Pos.x + select.Size.x / 2, select.Pos.y + select.Size.y / 2,
			0, 0,
			select.Size.x, select.Size.y,
			0, 0xFFFFFF00 + Ealpha);
	}
	else if (select.IMAGELINE != -1) {
		Novice::DrawQuad(
			select.Pos.x - select.Size.x / 2, select.Pos.y - select.Size.y / 2,
			select.Pos.x + select.Size.x / 2, select.Pos.y - select.Size.y / 2,
			select.Pos.x - select.Size.x / 2, select.Pos.y + select.Size.y / 2,
			select.Pos.x + select.Size.x / 2, select.Pos.y + select.Size.y / 2,
			0, select.IMAGELINE * 80,
			select.Size.x, select.Size.y,
			tex, select.Color);
	}
	else {
		Novice::DrawQuad(
			select.Pos.x - select.Size.x / 2, select.Pos.y - select.Size.y / 2,
			select.Pos.x + select.Size.x / 2, select.Pos.y - select.Size.y / 2,
			select.Pos.x - select.Size.x / 2, select.Pos.y + select.Size.y / 2,
			select.Pos.x + select.Size.x / 2, select.Pos.y + select.Size.y / 2,
			0, 0,
			select.Size.x, select.Size.y,
			tex, select.Color);
	}

	Novice::ScreenPrintf(0, 0, "%d", DrawNum);
}


