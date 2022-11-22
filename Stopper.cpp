#include "Stopper.h"
#include "Screen.h"

bool Stopper::Pause()
{
	if (canselect == true) {
		if (Key::IsTrigger(DIK_P) || Controller::IsTriggerButton(0, Controller::bSTART)) {
			if (isPause == true) {
				isPause = false;
			}
			else {
				isPause = true;
			}
		}

		if (isPause == true) {
			if (Key::IsTrigger(DIK_S) || Controller::IsStickDirection(0, Controller::lsdDOWN)) {
				Selected++;
				if (Selected > 3) {
					Selected = 0;
				}
			}
			if (Key::IsTrigger(DIK_W) || Controller::IsStickDirection(0, Controller::lsdUP)) {
				Selected--;
				if (Selected < 0) {
					Selected = 3;
				}
			}

			if (BackGame.LINE == Selected) {
				BackGame.Color = 0x20d6c7FF;
				if (Key::IsTrigger(DIK_K) || Controller::IsTriggerButton(0, Controller::bA)) {
					isPause = false;
				}
			}
			else {
				BackGame.Color = WHITE;
			}

			if (Restart.LINE == Selected) {
				Restart.Color = 0x20d6c7FF;
				if (Key::IsTrigger(DIK_K) || Controller::IsTriggerButton(0, Controller::bA)) {
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
					QuitFlag = true;
				}
			}
			else {
				Quit.Color = WHITE;
			}
		}
	}

	return isPause;
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

		PauseQuadDraw(BackGame, PauseSelect_Gra);

		PauseQuadDraw(Restart, PauseSelect_Gra);

	/*	PauseQuadDraw(BGM, PauseSelect_Gra);

		PauseQuadDraw(SE, PauseSelect_Gra);*/

		PauseQuadDraw(Title, PauseSelect_Gra);

		PauseQuadDraw(Quit, PauseSelect_Gra);

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