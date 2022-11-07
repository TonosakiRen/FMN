#include "PlayerMain.h"


void PlayerMain::Move()
{
	{
		
		if (Key::IsTrigger(DIK_Y)) {
			HitStop = 30;
		}

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
			if (CanJump == true && PreJumpKey == 1 && DashFlag == false) {
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

		Player.Pos.x += Speed.x + OtherSpeed.x + HitBack.x;
		Player.Pos.y += (Speed.y + OtherSpeed.y + HitBack.y) * G;

		Player.Pos.y = Clamp::clamp(Player.Pos.y, FLOOR + Player.HitBoxSize.y / 2, 9999);

		if (HitBack.x > 1) {
			HitBack.x -= 1;
		}
		else if (HitBack.x < -1) {
			HitBack.x += 1;
		}
		else {
			HitBack.x = 0;
		}

		if (HitBack.y > 0) {
			HitBack.y -= 1;
		}

		if (Player.Pos.y <= FLOOR + Player.HitBoxSize.y / 2) {
			Speed.y = 0;
			OtherSpeed.y = 0;
			HitBack.y = 0;
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
		 HitRatio.x = 
			 ((Target.LeftTop.x + Target.GetWidth() / 2)
		    - (Player.Quad.LeftTop.x + Player.Quad.GetWidth() / 2))
			/
			 (Sword.HitBoxSize.x
				 + Player.Quad.GetWidth() / 2
				 + Target.GetWidth() / 2);

		 HitRatio.y =
			 (((Target.LeftTop.y * -1 + FLOOR) + Target.GetHeight() / 2)
				 - ((Player.Quad.LeftTop.y * -1 + FLOOR) + Player.Quad.GetHeight() / 2))
			 /
			 (Sword.HitBoxSize.y
				 + Player.Quad.GetHeight() / 2
				 + Target.GetHeight() / 2);

		 if(FaceDown == true){
			 HitBack.y = (1 - HitRatio.y) * 8;
			 OtherSpeed.y = 0;
		 }
		 else if (FaceUp == true) {
			 HitBack.y = (-1 + -HitRatio.y) * 8;
		 }
		 else {
			 if (FaceRight == true) {
				 HitBack.x = (-1 + HitRatio.x) * 30;
			 }
			 else {
				 HitBack.x = (1 + HitRatio.x) * 30;
			 }
		 }
	}

	
	
}

void PlayerMain::PlayerHit(Quad Target, Screen& screen)
{

//	//Vec2 TargetPos = Target.LeftTop
//	
//	Vec2 TargetWide = { Target.RightTop.x - Target.LeftTop.x , Target.LeftTop.y - Target.LeftBottom.y};
//	
//	Vec2 TargetPos = { Target.LeftTop.x + (Target.RightBottom.x - Target.LeftTop.x) / 2,
//						 Target.LeftTop.y + (Target.RightBottom.y - Target.LeftTop.y) / 2 };
//
//#pragma region a
//
//	Vec2 MostLeft = Target.LeftTop;
//	Vec2 MostRight = Target.RightTop;
//	Vec2 MostTop = Target.LeftBottom;
//	Vec2 MostBottom = Target.RightBottom;
//
//	if(MostLeft.x > Target.RightTop.x){
//		MostLeft = Target.RightTop;
//	}
//	if (MostLeft.x > Target.LeftBottom.x) {
//		MostLeft = Target.LeftBottom;
//	}
//	if (MostLeft.x > Target.RightBottom.x) {
//		MostLeft = Target.RightBottom;
//	}
//
//	if (MostRight.x < Target.RightTop.x) {
//		MostRight = Target.RightTop;
//	}
//	if (MostRight.x < Target.LeftBottom.x) {
//		MostRight = Target.LeftBottom;
//	}
//	if (MostRight.x < Target.RightBottom.x) {
//		MostRight = Target.RightBottom;
//	}
//
//	if (MostTop.y < Target.RightTop.y) {
//		MostTop = Target.RightTop;
//	}
//	if (MostTop.y < Target.LeftBottom.y) {
//		MostTop = Target.LeftBottom;
//	}
//	if (MostTop.y < Target.RightBottom.y) {
//		MostTop = Target.RightBottom;
//	}
//
//	if (MostBottom.y > Target.RightTop.y) {
//		MostBottom = Target.RightTop;
//	}
//	if (MostBottom.y > Target.LeftBottom.y) {
//		MostBottom = Target.LeftBottom;
//	}
//	if (MostBottom.y > Target.RightBottom.y) {
//		MostBottom = Target.RightBottom;
//	}
//
//
//#pragma endregion
//
//	float Dot1[4] = { 
//		(Player.Quad.LeftTop.x - MostLeft.x) * (MostTop.y - MostLeft.y + FLOOR)
//		- (Player.Quad.LeftTop.y - MostLeft.y + FLOOR) * (MostTop.x - MostLeft.x) ,
//		(Player.Quad.RightTop.x - MostLeft.x)* (MostTop.y - MostLeft.y + FLOOR)
//		- (Player.Quad.RightTop.y - MostLeft.y + FLOOR) * (MostTop.x - MostLeft.x) ,
//		(Player.Quad.LeftBottom.x - MostLeft.x)* (MostTop.y - MostLeft.y + FLOOR)
//		- (Player.Quad.LeftBottom.y - MostLeft.y + FLOOR) * (MostTop.x - MostLeft.x) ,
//		(Player.Quad.RightBottom.x - MostLeft.x)* (MostTop.y - MostLeft.y + FLOOR)
//		- (Player.Quad.RightBottom.y - MostLeft.y + FLOOR) * (MostTop.x - MostLeft.x) ,
//	};
//
//	float Dot2[4] = {
//		(Player.Quad.LeftTop.x - MostTop.x) * (MostRight.y - MostTop.y + FLOOR)
//		- (Player.Quad.LeftTop.y - MostTop.y + FLOOR) * (MostRight.x - MostTop.x) ,
//		(Player.Quad.RightTop.x - MostTop.x) * (MostRight.y - MostTop.y + FLOOR)
//		- (Player.Quad.RightTop.y - MostTop.y + FLOOR) * (MostRight.x - MostTop.x) ,
//		(Player.Quad.LeftBottom.x - MostTop.x) * (MostRight.y - MostTop.y + FLOOR)
//		- (Player.Quad.LeftBottom.y - MostTop.y + FLOOR) * (MostRight.x - MostTop.x) ,
//		(Player.Quad.RightBottom.x - MostTop.x) * (MostRight.y - MostTop.y + FLOOR)
//		- (Player.Quad.RightBottom.y - MostTop.y + FLOOR) * (MostRight.x - MostTop.x) ,
//	};
//
//	float Dot3[4] = {
//		(Player.Quad.LeftTop.x - MostRight.x) * (MostBottom.y - MostRight.y + FLOOR)
//		- (Player.Quad.LeftTop.y - MostRight.y + FLOOR) * (MostBottom.x - MostRight.x) ,
//		(Player.Quad.RightTop.x - MostRight.x) * (MostBottom.y - MostRight.y + FLOOR)
//		- (Player.Quad.RightTop.y - MostRight.y + FLOOR) * (MostBottom.x - MostRight.x) ,
//		(Player.Quad.LeftBottom.x - MostRight.x) * (MostBottom.y - MostRight.y + FLOOR)
//		- (Player.Quad.LeftBottom.y - MostRight.y + FLOOR) * (MostBottom.x - MostRight.x) ,
//		(Player.Quad.RightBottom.x - MostRight.x) * (MostBottom.y - MostRight.y + FLOOR)
//		- (Player.Quad.RightBottom.y - MostRight.y + FLOOR) * (MostBottom.x - MostRight.x) ,
//	};
//
//	float Dot4[4] = {
//		(Player.Quad.LeftTop.x - MostBottom.x) * (MostLeft.y - MostBottom.y + FLOOR)
//		- (Player.Quad.LeftTop.y - MostBottom.y + FLOOR) * (MostLeft.x - MostBottom.x) ,
//		(Player.Quad.RightTop.x - MostBottom.x) * (MostLeft.y - MostBottom.y + FLOOR)
//		- (Player.Quad.RightTop.y - MostBottom.y + FLOOR) * (MostLeft.x - MostBottom.x) ,
//		(Player.Quad.LeftBottom.x - MostBottom.x) * (MostLeft.y - MostBottom.y + FLOOR)
//		- (Player.Quad.LeftBottom.y - MostBottom.y + FLOOR) * (MostLeft.x - MostBottom.x) ,
//		(Player.Quad.RightBottom.x - MostBottom.x) * (MostLeft.y - MostBottom.y + FLOOR)
//		- (Player.Quad.RightBottom.y - MostBottom.y + FLOOR) * (MostLeft.x - MostBottom.x) ,
//	};
//
//	Player.Color = WHITE;
//	for (int i = 0; i < 4; i++) {
//		if (Dot1[i] > 0) {
//			Novice::DrawEllipse(100, 100, 30, 30, 0, RED, kFillModeSolid);
//		}
//
//		if (Dot2[i] > 0) {
//			Novice::DrawEllipse(200, 100, 30, 30, 0, RED, kFillModeSolid);
//		}
//
//		if (Dot3[i] > 0) {
//			Novice::DrawEllipse(300, 100, 30, 30, 0, RED, kFillModeSolid);
//		}
//
//		if (Dot4[i] > 0) {
//			Novice::DrawEllipse(400, 100, 30, 30, 0, RED, kFillModeSolid);
//		}
//
//		
//
//		if (Dot1[i] > 0 && Dot2[i] > 0 && Dot3[i] > 0 && Dot4[i] > 0 ) {
//			//Player.Pos.y += 500;
//			Player.Color = RED;
//		}
//	}
//
//
//	Novice::ScreenPrintf(100, 40, "%f %f", TargetWide.x, TargetWide.y);
//
//	screen.DrawEllipse(Target.LeftTop.x, Target.LeftTop.y, 10, 10, 0, RED, kFillModeSolid);
//
//	screen.DrawEllipse(MostLeft.x, MostLeft.y, 10, 10, 0, BLUE, kFillModeSolid);
//
//	screen.DrawEllipse(MostRight.x, MostRight.y, 10, 10, 0, BLUE, kFillModeSolid);
//	
//	screen.DrawEllipse(MostTop.x, MostTop.y, 10, 10, 0, BLUE, kFillModeSolid);
//
//	screen.DrawEllipse(MostBottom.x, MostBottom.y, 10, 10, 0, BLUE, kFillModeSolid);
//
//	screen.DrawLine(MostLeft.x, MostLeft.y, MostTop.x, MostTop.y, RED);
//
//	screen.DrawLine(MostLeft.x, MostLeft.y, MostBottom.x, MostBottom.y, RED);
//	
//	screen.DrawLine(MostRight.x, MostRight.y, MostTop.x, MostTop.y, RED);
//
//	screen.DrawLine(MostRight.x, MostRight.y, MostBottom.x, MostBottom.y, RED);


	if (Collision::DiagonalQuadToQuad(Player.Quad, Target)) {
		Novice::ScreenPrintf(0, 300, "chinchin");
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

	Novice::ScreenPrintf(0, 100, "%f", HitBack.y);

	screen.DrawQuad2Renban(Player.Quad, Player.SrcX,0,1, 1,0,60, Player.AnimeFlame,texture, Player.Color,0);

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
	Novice::ScreenPrintf(0, 20, "%f", HitBack.x);

}

Vec2 PlayerMain::Translation()
{
	return Vec2(Player.Pos);
}
