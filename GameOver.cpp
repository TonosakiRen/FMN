#include "GameOver.h"
#include "Key.h"
#include "ControllerInput.h"

void GameOver::Update()
{
	if (canselect == true) {

		stickup = Controller::IsStickDirection(0, Controller::lsdUP);
		stickdown = Controller::IsStickDirection(0, Controller::lsdDOWN);

		if (Key::IsTrigger(DIK_S) || (stickdown == true && prestickdown == false)) {
			Selected++;
			if (Selected > 1) {
				Selected = 0;
				sound.SoundEffect(sound.Pick, 1.0f, "./Resources/sounds/sentaku.wav");
			}
		}
		if (Key::IsTrigger(DIK_W) || (stickup == true && prestickup == false)) {
			Selected--;
			if (Selected < 0) {
				Selected = 1;
				sound.SoundEffect(sound.Pick, 1.0f, "./Resources/sounds/sentaku.wav");

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

		prestickup = stickup;
		prestickdown = stickdown;
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