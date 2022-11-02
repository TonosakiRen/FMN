#include "PlayerMain.h"


void PlayerMain::Move()
{
	
	
	if (Key::IsPressed(DIK_O) != 0) {
		JumpPower += 0.01;
	}
	if (Key::IsPressed(DIK_L) != 0) {
		JumpPower -= 0.01;
	}



	Speed.x = 0;

	if (Controller::IsStickDirection(0,Controller::lsdRIGHT)||Key::IsPressed(DIK_D)) {
		Speed.x = 8;
	}
	if (Controller::IsStickDirection(0, Controller::lsdLEFT) || Key::IsPressed(DIK_A)) {
		Speed.x = -8;
	}

	if (Controller::IsPressedButton(0,Controller::bA) == 1||Key::IsPressed(DIK_SPACE)) {
		if (CanJump == true && PreJumpKey == 1) {
			JumpFlag = true;
		}
	}

	if(Controller::IsReleaseButton(0, Controller::bA) == 1 || Key::IsRelease(DIK_SPACE)) {
		JumpFlag = false;
	}

	if (JumpFlag == true) {
		Speed.y = JumpPower;
		JumpTime++;
		if (JumpTime >= 10) {
			JumpFlag = false;
			JumpTime = 0;
		}
	}
	else {
		OtherSpeed.y -= 0.2;
	}


	
	

	Pos.x += Speed.x ;
	Pos.y += (Speed.y + OtherSpeed.y )* G;

	Pos.y = Clamp::clamp(Pos.y, FLOOR + HitBoxWide.y / 2,9999);

	if (Pos.y <= FLOOR + HitBoxWide.y / 2) {
		Speed.y = 0;
		OtherSpeed.y = 0;
		JumpTime = 0;
		CanJump = true;
	}
	else {
		CanJump = false;
	}
	
	PreJumpKey = Controller::IsPressedButton(0, Controller::bA)||Key::IsPressed(DIK_SPACE);

}

void PlayerMain::Draw(Screen& screen,int texture)
{
	/*Novice::DrawQuad(
		Pos.x - HitBoxWide.x / 2, Pos.y - HitBoxWide.y / 2,
		Pos.x + HitBoxWide.x / 2, Pos.y - HitBoxWide.y / 2,
		Pos.x - HitBoxWide.x / 2, Pos.y + HitBoxWide.y / 2,
		Pos.x + HitBoxWide.x / 2, Pos.y + HitBoxWide.y / 2,
		0, 0, 1, 1, texture, WHITE);*/

	//Novice::DrawLine(0,FLOOR,1280,FLOOR,RED);

	screen.DrawQuad(Pos.x - HitBoxWide.x / 2, Pos.y - HitBoxWide.y / 2,
		Pos.x + HitBoxWide.x / 2, Pos.y - HitBoxWide.y / 2,
		Pos.x - HitBoxWide.x / 2, Pos.y + HitBoxWide.y / 2,
		Pos.x + HitBoxWide.x / 2, Pos.y + HitBoxWide.y / 2,
		0, 0, 1, 1, texture, WHITE);

	screen.DrawLine(0, FLOOR, SCREEN_WIDTH, FLOOR, RED);

	Novice::ScreenPrintf(0, 0, "[O][L]keys JumpPower : %0.2f", JumpPower);
	
}

Vec2 PlayerMain::Translation()
{
	return Vec2(Pos);
}
