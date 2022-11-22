#include "GameOver.h"
#include "Key.h"

void GameOver::Update()
{
	if (canselect == true) {
		if (Key::IsTrigger(DIK_S) || Controller::IsStickDirection(0, Controller::lsdDOWN)) {
			Selected++;
			if (Selected > 1) {
				Selected = 0;
			}
		}
		if (Key::IsTrigger(DIK_W) || Controller::IsStickDirection(0, Controller::lsdUP)) {
			Selected--;
			if (Selected < 0) {
				Selected = 1;
			}
		}

		if (Restart.LINE == Selected) {
			Restart.Color = 0x20d6c7FF;
			if (Key::IsTrigger(DIK_K) || Controller::IsTriggerButton(0, Controller::bA)) {
				RestartFlag = true;
				canselect = false;
			}
		}
		else {
			Restart.Color = WHITE;
		}

		if (Quit.LINE == Selected) {
			Quit.Color = 0x20d6c7FF;
			if (Key::IsTrigger(DIK_K) || Controller::IsTriggerButton(0, Controller::bA)) {
				QuitFlag = true;
				canselect = false;
			}
		}
		else {
			Quit.Color = WHITE;
		}
	}
}

void GameOver::Draw(Screen& screen, int PauseSelect_Gra)
{
	

	GameOverQuadDraw(Restart, PauseSelect_Gra);
	GameOverQuadDraw(Quit, PauseSelect_Gra);
}

void GameOver::GameOverQuadDraw(GameOverStruct select, int tex) {
	if (select.LINE != -1) {
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