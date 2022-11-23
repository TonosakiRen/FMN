#include "GameClear.h"
#include "Key.h"
#include "ControllerInput.h"

void GameClear::Update()
{

	if (Time > 180) {
		TitleDrawFlag = true;
	}

	Time++;

	if (TitleDrawFlag == true) {
		if (Key::IsTrigger(DIK_K) || Controller::IsTriggerButton(0, Controller::bA)) {
			TitleDrawFlag = false;
			TitleFlag = true;
			Time = 0;
		}
	}
}

void GameClear::Draw(Screen& screen, int Ending_Gra, int gamecleargra)
{
	if (TitleDrawFlag == true) {
		GameClearQuadDraw(TitleBack, Ending_Gra);
	}
	GameClearQuadDraw(GameClearText, gamecleargra);
}

void GameClear::GameClearQuadDraw(GameClearStruct select, int tex) {
	if (select.IMAGELINE != -1) {
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
}