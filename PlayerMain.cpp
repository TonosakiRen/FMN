#include "PlayerMain.h"
#include <Novice.h>
#include "Clamp.h"
#include "ControllerInput.h"
//#include "Key.h"

void PlayerMain::Move()
{
	

	Speed.x = 0;

	if (Controller::IsStickDirection(0,Controller::lsdRIGHT)) {
		Speed.x = 8;
	}
	if (Controller::IsStickDirection(0, Controller::lsdLEFT)) {
		Speed.x = -8;
	}

	if (Controller::IsTriggerButton(0,Controller::bA)) {
		if (CanJump == true) {
			JumpFlag = true;
		}
	}
	else {
		JumpFlag = false;
	}

	if (JumpFlag == true) {
		Speed.y -= 3;
	}

	if (Speed.y <= -6) {
		JumpFlag = false;
	}

	Speed.y += 0.5;

	Speed.y = Clamp::clamp(Speed.y, -6,100);

	Pos.x += Speed.x ;
	Pos.y += Speed.y * G;

	Pos.y = Clamp::clamp(Pos.y, 0,FLOOR - HitBoxWide.y / 2);

	if (Pos.y >= FLOOR - HitBoxWide.y / 2) {
		Speed.y = 0;
		CanJump = true;
	}
	else {
		CanJump = false;
	}
	
}

void PlayerMain::Draw(int texture)
{
	Novice::DrawQuad(
		Pos.x - HitBoxWide.x / 2, Pos.y - HitBoxWide.y / 2,
		Pos.x + HitBoxWide.x / 2, Pos.y - HitBoxWide.y / 2,
		Pos.x - HitBoxWide.x / 2, Pos.y + HitBoxWide.y / 2,
		Pos.x + HitBoxWide.x / 2, Pos.y + HitBoxWide.y / 2,
		0, 0, 1, 1, texture, WHITE);

	Novice::DrawLine(0,FLOOR,1280,FLOOR,RED);

	//Novice::ScreenPrintf(0, 0, "%d", preKeys[DIK_W]);
}
