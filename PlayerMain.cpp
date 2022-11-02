#include "PlayerMain.h"


void PlayerMain::Move()
{
	
	
	if (Key::IsPressed(DIK_O) != 0) {
		JUMPPOWER += 0.01;
	}
	if (Key::IsPressed(DIK_L) != 0) {
		JUMPPOWER -= 0.01;
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
		Speed.y = JUMPPOWER;
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

	Pos.y = Clamp::clamp(Pos.y, FLOOR,9999);

	if (Pos.y <= FLOOR ) {
		Speed.y = 0;
		OtherSpeed.y = 0;
		JumpTime = 0;
		CanJump = true;
	}
	else {
		CanJump = false;
	}

	PlayerQuad = { Pos,int(PlayerHitBoxSize.x),int(PlayerHitBoxSize.y)};
	
	PreJumpKey = Controller::IsPressedButton(0, Controller::bA)||Key::IsPressed(DIK_SPACE);

	
}

void PlayerMain::NormalAttack()
{
	
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

	/*screen.DrawQuad(Pos.x - PlayerHitBoxSize.x / 2, Pos.y - PlayerHitBoxSize.y / 2,
		Pos.x + PlayerHitBoxSize.x / 2, Pos.y - PlayerHitBoxSize.y / 2,
		Pos.x - PlayerHitBoxSize.x / 2, Pos.y + PlayerHitBoxSize.y / 2,
		Pos.x + PlayerHitBoxSize.x / 2, Pos.y + PlayerHitBoxSize.y / 2,
		0, 0, 1, 1, texture, WHITE);*/

	screen.DrawQuad2Renban(PlayerQuad, SrcX,0,1, 1,0,60,AnimeFlame,texture,WHITE,0);

	screen.DrawLine(0, FLOOR, SCREEN_WIDTH, FLOOR, RED);

	Novice::ScreenPrintf(0, 0, "[O][L]keys JumpPower : %0.2f", JUMPPOWER);
	Novice::ScreenPrintf(0, 20, "%f");
}
