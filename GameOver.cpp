#include "GameOver.h"
#include "Key.h"
#include "ControllerInput.h"

void GameOver::Update(bool type)
{

	typee = type;

	if (canselect == true) {

		stickup = Controller::IsStickDirection(0, Controller::lsdUP);
		stickdown = Controller::IsStickDirection(0, Controller::lsdDOWN);

		if (Key::IsTrigger(DIK_S) || (stickdown == true && prestickdown == false)) {
			Selected++;
			sound.SoundEffect(sound.Pick, 0.3f, "./Resources/sounds/sentaku.wav", false);

		
			if (type == true) {
				if (Selected > 2) {
					Selected = 1;
				}
			}
			else {
				if (Selected > 2) {
					Selected = 0;
				}
			}
		}
		if (Key::IsTrigger(DIK_W) || (stickup == true && prestickup == false)) {
			Selected--;
			if (type == true) {
				if (Selected < 1) {
					Selected = 2;
				}
			}
			else {
				if (Selected < 0) {
					Selected = 2;
				}
			}
			sound.SoundEffect(sound.Pick, 0.3f, "./Resources/sounds/sentaku.wav", false);

		}

		if (Restart.LINE == Selected) {
			Restart.Color = 0x20d6c7FF;
			if (Key::IsTrigger(DIK_K) || Controller::IsTriggerButton(0, Controller::bA)) {
				RestartFlag = true;
				canselect = false;
				sound.SoundEffect(sound.PickUp, 0.3f, "./Resources/sounds/kettei.wav", false);

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
				sound.SoundEffect(sound.PickUp, 0.3f, "./Resources/sounds/kettei.wav", false);

			}
		}
		else {
			Quit.Color = WHITE;
		}

		if (Restart2.LINE == Selected) {
			Restart2.Color = 0x20d6c7FF;
			if (Key::IsTrigger(DIK_K) || Controller::IsTriggerButton(0, Controller::bA)) {

				canselect = false;
			}
		}
		else {
			Restart2.Color = WHITE;
		}

		prestickup = stickup;
		prestickdown = stickdown;
	}
}



void GameOver::Draw(Screen& screen, int PauseSelect_Gra)
{
	if (typee == false) {
		GameOverQuadDraw(Restart2, PauseSelect_Gra);
	}
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