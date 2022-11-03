#include "PlayerMain.h"


void PlayerMain::Move()
{
	
	
	{


		if (Key::IsPressed(DIK_O) != 0) {
			JUMPPOWER += 0.01;
		}
		if (Key::IsPressed(DIK_L) != 0) {
			JUMPPOWER -= 0.01;
		}


		Sword.Pos =
		{ 9999,9999 };
		Sword.Quad = { {Sword.Pos.x - Sword.HitBoxSize.x / 2, Sword.Pos.y - Sword.HitBoxSize.y / 2},
		int(Sword.HitBoxSize.x),int(Sword.HitBoxSize.y) };

		Speed.x = 0;
		//Speed.y = 0;

		if (Controller::IsStickDirection(0, Controller::lsdRIGHT) || Key::IsPressed(DIK_D)) {
			Speed.x = 8;
			FaceRight = true;
		}

		if (Controller::IsStickDirection(0, Controller::lsdLEFT) || Key::IsPressed(DIK_A)) {
			Speed.x = -8;
			FaceRight = false;
		}

		if (Controller::IsStickDirection(0, Controller::lsdUP) || Key::IsPressed(DIK_W)) {
			FaceUp = true;
		}
		else {
			FaceUp = false;
		}

		if (Controller::IsStickDirection(0, Controller::lsdDOWN) || Key::IsPressed(DIK_S)) {
			//Speed.y = -1;
			FaceDown = true;
		}
		else {
			FaceDown = false;
		}

		if (Controller::IsPressedButton(0, Controller::bA) == 1 || Key::IsPressed(DIK_SPACE)) {
			if (CanJump == true && PreJumpKey == 1) {
				JumpFlag = true;
			}
		}

		if (Controller::IsReleaseButton(0, Controller::bA) == 1 || Key::IsRelease(DIK_SPACE)) {
			JumpFlag = false;
		}

		if ((Controller::IsTriggerButton(0, Controller::lSHOULDER) == 1 || Key::IsTrigger(DIK_J)) && DashCoolTime <= 0) {
			DashFlag = true;
			JumpFlag = false;
			DashFaseRight = FaceRight;
		}

		if (DashFlag == true) {
			OtherSpeed.y = 0;
			Speed.y = 0;
			if (DashFaseRight == true) {
				Speed.x = 25;
			}
			else {
				Speed.x = -25;
			}
			DashTime++;
			if (DashTime > 7) {
				DashFlag = false;
				DashTime = 0;
				OtherSpeed.y = 0.2;
				DashCoolTime = 20;
			}
		}

		DashCoolTime--;

		if (JumpFlag == true) {
			Speed.y = JUMPPOWER;
			JumpTime++;
			if (JumpTime >= 10) {
				JumpFlag = false;
				JumpTime = 0;
			}
		}
		else {
			if (DashFlag == false) {
				OtherSpeed.y -= 0.2;
			}
		}

		Player.Pos.x += Speed.x;
		Player.Pos.y += (Speed.y + OtherSpeed.y) * G;

		Player.Pos.y = Clamp::clamp(Player.Pos.y, FLOOR + Player.HitBoxSize.y / 2, 9999);

		if (Player.Pos.y <= FLOOR + Player.HitBoxSize.y / 2) {
			Speed.y = 0;
			OtherSpeed.y = 0;
			JumpTime = 0;
			CanJump = true;
		}
		else {
			CanJump = false;
		}

		Player.Quad = { { Player.Pos.x - Player.HitBoxSize.x / 2, Player.Pos.y + Player.HitBoxSize.y / 2 },
			int(Player.HitBoxSize.x),int(Player.HitBoxSize.y) };

		PreJumpKey = Controller::IsPressedButton(0, Controller::bA) || Key::IsPressed(DIK_SPACE);

		if (Controller::IsTriggerButton(0, Controller::bX) == 1 || Key::IsTrigger(DIK_K)) {
			NormalAttack();
		}



	}
	
	
	
}

void PlayerMain::NormalAttack()
{
	
	if (FaceUp == true) {
		Sword.HitBoxSize = { 128, 196 };
		Sword.Pos =
		{ Player.Pos.x,
		 Player.Pos.y + Player.HitBoxSize.y / 2 + Sword.HitBoxSize.y / 2 };
		Sword.Quad = { {Sword.Pos.x - Sword.HitBoxSize.x / 2, Sword.Pos.y + Sword.HitBoxSize.y / 2},
		int(Sword.HitBoxSize.x),int(Sword.HitBoxSize.y) };
		
	}
	else if (FaceDown == true) {
		Sword.HitBoxSize = { 128, 196 };
		Sword.Pos =
		{ Player.Pos.x,
		 Player.Pos.y - Player.HitBoxSize.y / 2 - Sword.HitBoxSize.y / 2 };
		Sword.Quad = { {Sword.Pos.x - Sword.HitBoxSize.x / 2, Sword.Pos.y + Sword.HitBoxSize.y / 2},
		int(Sword.HitBoxSize.x),int(Sword.HitBoxSize.y) };
		
	}
	else if (FaceRight == true) {
		Sword.HitBoxSize = { 196, 128 };
		Sword.Pos =
		{ Player.Pos.x + Player.HitBoxSize.x / 2 + Sword.HitBoxSize.x / 2,
		 Player.Pos.y };
		Sword.Quad = { {Sword.Pos.x - Sword.HitBoxSize.x / 2, Sword.Pos.y + Sword.HitBoxSize.y / 2},
		int(Sword.HitBoxSize.x),int(Sword.HitBoxSize.y) };
		
	}
	else if (FaceRight == false) {
		Sword.HitBoxSize = { 196, 128 };
		Sword.Pos =
		{ Player.Pos.x - Player.HitBoxSize.x / 2 - Sword.HitBoxSize.x / 2,
		 Player.Pos.y };
		Sword.Quad = { {Sword.Pos.x - Sword.HitBoxSize.x / 2, Sword.Pos.y + Sword.HitBoxSize.y / 2},
		int(Sword.HitBoxSize.x),int(Sword.HitBoxSize.y) };
		
	}



	

}

void PlayerMain::SwordHit(Quad Target)
{
	if (Collision::QuadToQuad(Sword.Quad , Target))
	{
		Novice::ScreenPrintf(0, 20, "a");
	}
}

void PlayerMain::Draw(Screen& screen,int texture)
{

	/*Novice::DrawQuad(
		PlayerPos.x - HitBoxWide.x / 2, PlayerPos.y - HitBoxWide.y / 2,
		PlayerPos.x + HitBoxWide.x / 2, PlayerPos.y - HitBoxWide.y / 2,
		PlayerPos.x - HitBoxWide.x / 2, PlayerPos.y + HitBoxWide.y / 2,
		PlayerPos.x + HitBoxWide.x / 2, PlayerPos.y + HitBoxWide.y / 2,
		0, 0, 1, 1, texture, WHITE);*/

	//Novice::DrawLine(0,FLOOR,1280,FLOOR,RED);

	/*screen.DrawQuad(PlayerPos.x - PlayerHitBoxSize.x / 2, PlayerPos.y - PlayerHitBoxSize.y / 2,
		PlayerPos.x + PlayerHitBoxSize.x / 2, PlayerPos.y - PlayerHitBoxSize.y / 2,
		PlayerPos.x - PlayerHitBoxSize.x / 2, PlayerPos.y + PlayerHitBoxSize.y / 2,
		PlayerPos.x + PlayerHitBoxSize.x / 2, PlayerPos.y + PlayerHitBoxSize.y / 2,
		0, 0, 1, 1, texture, WHITE);*/

	screen.DrawQuad2Renban(Player.Quad, Player.SrcX,0,1, 1,0,60, Player.AnimeFlame,texture,WHITE,0);

	screen.DrawQuad2Renban(Sword.Quad, Sword.SrcX, 0, 1, 1, 0, 60, Sword.AnimeFlame, texture, 0x0000FF7F, 0);

	screen.DrawEllipse(Player.Pos.x, Player.Pos.y,10,10,0,BLUE,kFillModeSolid);

	if (FaceUp == true) {
		screen.DrawLine(Player.Pos.x, Player.Pos.y, Player.Pos.x, Player.Pos.y + 100, 0xFFFF00FF);
	}
	else if (FaceDown == true) {
		screen.DrawLine(Player.Pos.x, Player.Pos.y, Player.Pos.x, Player.Pos.y - 100, 0xFFFF00FF);
	}
	else if (FaceRight == true) {
		screen.DrawLine(Player.Pos.x, Player.Pos.y , Player.Pos.x + 100, Player.Pos.y, 0xFFFF00FF);
	}
	else if (FaceRight == false) {
		screen.DrawLine(Player.Pos.x , Player.Pos.y, Player.Pos.x - 100, Player.Pos.y , 0xFFFF00FF);
	}
	

	screen.DrawLine(0, FLOOR, SCREEN_WIDTH, FLOOR, RED);

	Novice::ScreenPrintf(0, 0, "[O][L]keys JumpPower : %0.2f", JUMPPOWER);
	//Novice::ScreenPrintf(0, 20, "%f", boss.testget());

}

Vec2 PlayerMain::Translation()
{
	return Vec2(Player.Pos);
}
