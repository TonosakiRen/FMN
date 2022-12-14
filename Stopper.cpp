#include "Stopper.h"
#include "Screen.h"

bool Stopper::Pause()
{
	if (canselect == true) {
		if (Key::IsTrigger(DIK_P) || Controller::IsTriggerButton(0, Controller::bSTART)) {
			sound.SoundEffect(sound.Pozu, 0.3f, "./Resources/sounds/pozu.wav", false);

			if (isPause == true) {
				isPause = false;
			}
			else {
				isPause = true;
				Selected = 0;

				switch (scene)
				{
				case title:
					BackGame.LINE = 0;
					BackGame.Pos = { 1920 / 2,690 };
					Quit.LINE = 1;
					Quit.Pos = { 1920 / 2,810 };
					break;
				case stage:
					BackGame.LINE = 0;
					BackGame.Pos = { 1920 / 2,570 };
					Restart.LINE = 1;
					Restart.Pos = { 1920 / 2,690 };
					Quit.LINE = 3;
					Quit.Pos = { 1920 / 2,930 };
					Title.LINE = 2;
					Title.Pos = { 1920 / 2,810 };
					break;
				}
			}
		}

		stickup = Controller::IsStickDirection(0, Controller::lsdUP);
		stickdown = Controller::IsStickDirection(0, Controller::lsdDOWN);

		if (isPause == true) {
			
			if (Key::IsTrigger(DIK_S) || (stickdown == true && prestickdown == false)) {
					sound.SoundEffect(sound.Pick, 0.3f, "./Resources/sounds/sentaku.wav", false);
					Selected++;
					if (Selected > MAXLINE) {
						Selected = 0;
					}
				}
			if (Key::IsTrigger(DIK_W) || (stickup == true && prestickup == false)) {
				Selected--;
				sound.SoundEffect(sound.Pick, 0.3f, "./Resources/sounds/sentaku.wav", false);

				if (Selected < 0) {
					Selected = MAXLINE;
				}
			}

			switch (scene)
			{
			case title:

				if (BackGame.LINE == Selected) {
					BackGame.Color = 0x20d6c7FF;
					if (Key::IsTrigger(DIK_K) || Controller::IsTriggerButton(0, Controller::bA)) {
						sound.SoundEffect(sound.PickUp, 0.3f, "./Resources/sounds/kettei.wav", false);

						isPause = false;
					}
				}
				else {
					BackGame.Color = WHITE;
				}

				if (Quit.LINE == Selected) {
					Quit.Color = 0x20d6c7FF;
					if (Key::IsTrigger(DIK_K) || Controller::IsTriggerButton(0, Controller::bA)) {
						sound.SoundEffect(sound.PickUp, 0.3f, "./Resources/sounds/kettei.wav", false);
						QuitFlag = true;
					}
				}
				else {
					Quit.Color = WHITE;
				}
				break;

			case stage:
				if (BackGame.LINE == Selected) {
					BackGame.Color = 0x20d6c7FF;
					if (Key::IsTrigger(DIK_K) || Controller::IsTriggerButton(0, Controller::bA)) {
						sound.SoundEffect(sound.PickUp, 0.3f, "./Resources/sounds/kettei.wav", false);

						isPause = false;
					}
				}
				else {
					BackGame.Color = WHITE;
				}

				if (Restart.LINE == Selected) {
					Restart.Color = 0x20d6c7FF;
					if (Key::IsTrigger(DIK_K) || Controller::IsTriggerButton(0, Controller::bA)) {
						sound.SoundEffect(sound.PickUp, 0.3f, "./Resources/sounds/kettei.wav", false);

						RestartFlag = true;
						canselect = false;
						isPause = false;
					}
				}
				else {
					Restart.Color = WHITE;
				}

				/*if (BGM.LINE == Selected) {
					BGM.Color = 0x20d6c7FF;
				}
				else {
					BGM.Color = WHITE;
				}

				if (SE.LINE == Selected) {
					SE.Color = 0x20d6c7FF;
				}
				else {
					SE.Color = WHITE;
				}*/

				if (Title.LINE == Selected) {
					Title.Color = 0x20d6c7FF;
					if (Key::IsTrigger(DIK_K) || Controller::IsTriggerButton(0, Controller::bA)) {
						sound.SoundEffect(sound.PickUp, 0.3f, "./Resources/sounds/kettei.wav", false);
						TitileBackFlag = true;
						canselect = false;
						isPause = false;
					}
				}
				else {
					Title.Color = WHITE;
				}

				if (Quit.LINE == Selected) {
					Quit.Color = 0x20d6c7FF;
					if (Key::IsTrigger(DIK_K) || Controller::IsTriggerButton(0, Controller::bA)) {
						sound.SoundEffect(sound.PickUp, 0.3f, "./Resources/sounds/kettei.wav", false);
						QuitFlag = true;
					}
				}
				else {
					Quit.Color = WHITE;
				}
				break;
			}
		}

		prestickup = stickup;
		prestickdown = stickdown;
	}

	return isPause;
}

void Stopper::SetScene(int mainscene)
{
	scene = mainscene;
}



void Stopper::HitStopMake(int StopFlame)
{	
	if (StopFlame > 0) {
		isHitStop = true;
		HitStopTime = StopFlame;
	}
}

bool Stopper::HitStopUpdate()
{
	
	if (HitStopTime > 0) {
		HitStopTime--;
	}
	else {
		isHitStop = false;
	}

	return isHitStop;

}

void Stopper::PauseDraw(int inPause_Gra, int PauseSelect_Gra)
{
	if (isPause == true) {
		Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0x2200007F, kFillModeSolid);

		PauseQuadDraw(InPause, inPause_Gra);

		switch (scene)
		{
		case title:
			PauseQuadDraw(BackGame, PauseSelect_Gra);
			PauseQuadDraw(Quit, PauseSelect_Gra);
			break;
		case stage:
			PauseQuadDraw(BackGame, PauseSelect_Gra);

			PauseQuadDraw(Restart, PauseSelect_Gra);

			/*	PauseQuadDraw(BGM, PauseSelect_Gra);

				PauseQuadDraw(SE, PauseSelect_Gra);*/

			PauseQuadDraw(Title, PauseSelect_Gra);

			PauseQuadDraw(Quit, PauseSelect_Gra);
			break;
		}

	}
}

void Stopper::PauseQuadDraw(PauseStruct select,int tex) {
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