#include "PlayerMain.h"
#include "Easing.h"


void PlayerMain::Init()
{
	Player.Pos = { 300,0 };
	DashFlag = false;
	DashTime = 0;
	attackstarttime = -1;
	HitCoolDown = 0;
	AttackCoolDown = 0;
	PreJumpKey = false;
	JumpFlag = false;
	Speed = { 0,0 };
	OtherSpeed = { 0,0 };
	HitBack = { 0,0 };
	Gravity = 0;
	FaceRight = true;
	HitStop = 0;
	CanMove = true;
	HP = MaxHp;
	GameOverTX = 0;
	GameOverTY = 0;
}

void PlayerMain::Move()
{
	isSwordHit = false;
	isSwordAppear = false;

	if (Key::IsTrigger(DIK_Y)) {

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

	PlayerAnimeMode = stand;



	if (CanMove == true) {
		if (Controller::IsStickDirection(0, Controller::lsdRIGHT) || Key::IsPressed(DIK_D)) {
			Speed.x = 8;
			if (attackstarttime == -1) {
				FaceRight = true;
			}
			PlayerAnimeMode = walk;
		}

		if (Controller::IsStickDirection(0, Controller::lsdLEFT) || Key::IsPressed(DIK_A)) {
			Speed.x = -8;
			if (attackstarttime == -1) {
				FaceRight = false;
			}
			PlayerAnimeMode = walk;
		}

		if (Controller::IsStickDirection(0, Controller::lsdUP) || Key::IsPressed(DIK_W)) {
			if (attackstarttime == -1) {
				FaceUp = true;
			}
			//Speed.y = 1;
		}
		else {
			if (attackstarttime == -1) {
				FaceUp = false;
			}
		}


		if (Controller::IsStickDirection(0, Controller::lsdDOWN) || Key::IsPressed(DIK_S)) {
			//Speed.y = -1;
			if (attackstarttime == -1) {
				FaceDown = true;
			}
		}
		else {
			if (attackstarttime == -1) {
				FaceDown = false;
			}
		}

		if (Controller::IsPressedButton(0, Controller::bA) == 1 || Key::IsPressed(DIK_SPACE)) {
			if (CanJump == true && PreJumpKey == 1 && DashFlag == false) {
				JumpFlag = true;
				sound.SoundEffect(1.5f, "./Resources/sounds/Jump.mp3");
			}
		}

		if (Controller::IsReleaseButton(0, Controller::bA) == 1 || Key::IsRelease(DIK_SPACE)) {
			JumpFlag = false;
		}

		if ((Controller::IsTriggerButton(0, Controller::lSHOULDER) == 1 || Key::IsTrigger(DIK_J)) && DashCoolTime <= 0) {
			DashFlag = true;
			JumpFlag = false;
			DashFaseRight = FaceRight;
			if (FaceDown == true || FaceUp == true) {
				DashAvoid = true;
			}
		}
	}

	if (DashFlag == true) {
		Gravity = 0;
		Speed.y = 0;
		if (DashAvoid == true) {
			Gravity = 0;
		}
		else {
			if (DashFaseRight == true) {
				Speed.x = DASHSPEED;
			}
			else {
				Speed.x = -DASHSPEED;
			}
		}
		DashTime++;
		if (DashTime > 6) {
			DashFlag = false;
			DashAvoid = false;
			DashTime = 0;
			Gravity = 0.14;
			DashCoolTime = 20;
		}
	}

	if (OtherSpeed.x < 0) {
		OtherSpeed.x+= 10;
	}

	DashCoolTime--;

	if (JumpFlag == true) {
		Speed.y = JUMPPOWER;
		JumpTime++;
		if (JumpTime >= 11) {
			JumpFlag = false;
			JumpTime = 0;
		}
	}
	else {
		if (DashFlag == false) {
			Gravity -= 0.14;
		}
	}
	
	if (HP <= 0) {
		Gravity = 0;
		Speed = { 0,0 };
		OtherSpeed = { 0,0 };
		HitBack = { 0,0 };
		HitCoolDown = 0;
	}
	

	Player.Pos.x += Speed.x + OtherSpeed.x + HitBack.x + MovieSpeed.x;
	Player.Pos.y += (Speed.y + OtherSpeed.y + HitBack.y + Gravity + MovieSpeed.y) * G;

	Player.Pos.y = Clamp::clamp(Player.Pos.y, FLOOR + Player.HitBoxSize.y / 2, 9999);
	Player.Pos.x = Clamp::clamp(Player.Pos.x, Player.HitBoxSize.x / 2, (1920*1.25) - Player.HitBoxSize.x / 2);

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
	
	/*if (OtherSpeed.x > 1) {
		OtherSpeed.x -= 1;
	}
	else if (OtherSpeed.x < -1) {
		OtherSpeed.x += 1;
	}
	else {
		OtherSpeed.x = 0;
	}

	if (OtherSpeed.y > 0) {
		OtherSpeed.y -= 1;
	}*/

	if (Player.Pos.y <= FLOOR + Player.HitBoxSize.y / 2) {
		Speed.y = 0;
		Gravity = 0;
		OtherSpeed.y = 0;
		HitBack.y = 0;
		JumpTime = 0;
		CanJump = true;
	}
	else {
		CanJump = false;
	}

	if (MovieSpeed.x > 0) {
		PlayerAnimeMode = walk;
	}

	if ((Speed.y + Gravity) * G > 0) {
		PlayerAnimeMode = jump;
	}

	if ((Speed.y + Gravity) * G < 0) {
		PlayerAnimeMode = fall;
	}

	if (DashFlag == true) {
		PlayerAnimeMode = dash;
	}

	if (HP <= 0) {
		PlayerAnimeMode = death;
	}



	Player.Quad = { { Player.Pos.x - Player.HitBoxSize.x / 2, Player.Pos.y + Player.HitBoxSize.y / 2 },
		int(Player.HitBoxSize.x),int(Player.HitBoxSize.y) };



	PreJumpKey = Controller::IsPressedButton(0, Controller::bA) || Key::IsPressed(DIK_SPACE);


	if (CanMove == true) {
		if (Controller::IsTriggerButton(0, Controller::bX) == 1 || Key::IsTrigger(DIK_K)) {
			isAttack = 4;
			
		}
	}

	if (isAttack > 0) {
		if (AttackCoolDown <= 0 && attackstarttime == -1) {
			attackstarttime = 3;
			
		}
		isAttack--;
	}

	if (attackstarttime == 0) {
		attackstarttime = -1;
		sound.SoundEffect(1.0f,"./Resources/sounds/sword.mp3");
		NormalAttack();
		AttackCoolDown = ATTACKCOOLDOWNMAX;
		isSwordAppear = true;
		PlayerAnimeMode = attack;
	}

	

	if (attackstarttime > 0) {
		attackstarttime--;
		PlayerAnimeMode = attack;
	}

	if (AttackCoolDown > 0) {
		AttackCoolDown--;
	}

	if (HitCoolDown > 0) {
		HitCoolDown--;
	}

}

void PlayerMain::NormalAttack()
{
	
	if (FaceUp == true) {
		Sword.HitBoxSize = { 128, 228 };
		Sword.Pos =
		{ Player.Pos.x,
		 Player.Pos.y + Player.HitBoxSize.y / 2 + Sword.HitBoxSize.y / 2 };
		Sword.Quad = { {Sword.Pos.x - Sword.HitBoxSize.x / 2, Sword.Pos.y + Sword.HitBoxSize.y / 2},
		int(Sword.HitBoxSize.x),int(Sword.HitBoxSize.y) };
		
	}
	else if (FaceDown == true) {
		Sword.HitBoxSize = { 128, 228 };
		Sword.Pos =
		{ Player.Pos.x,
		 Player.Pos.y - Player.HitBoxSize.y / 2 - Sword.HitBoxSize.y / 2 };
		Sword.Quad = { {Sword.Pos.x - Sword.HitBoxSize.x / 2, Sword.Pos.y + Sword.HitBoxSize.y / 2},
		int(Sword.HitBoxSize.x),int(Sword.HitBoxSize.y) };
		
	}
	else if (FaceRight == true) {
		Sword.HitBoxSize = { 228, 128 };
		Sword.Pos =
		{ Player.Pos.x + Player.HitBoxSize.x / 2 + Sword.HitBoxSize.x / 2,
		 Player.Pos.y };
		Sword.Quad = { {Sword.Pos.x - Sword.HitBoxSize.x / 2, Sword.Pos.y + Sword.HitBoxSize.y / 2},
		int(Sword.HitBoxSize.x),int(Sword.HitBoxSize.y) };
		
	}
	else if (FaceRight == false) {
		Sword.HitBoxSize = { 228, 128 };
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
		isSwordHit = true;

		 if(FaceDown == true){
			 HitBack.y =3;
			 Gravity = 0;
		 }
		 else if (FaceUp == true) {
			 HitBack.y = -3;
		 }
		 else {
			 if (FaceRight == true) {
				 HitBack.x = -12;
			 }
			 else {
				 HitBack.x =  12;
			 }
		 }

		 hitAttackPos = Collision::GetCollisionQuad(Sword.Quad, Target);

		 HitStop = 3;
	}

	
	
}

void PlayerMain::PlayerHit(Quad Target)
{
	if (HP > 0) {
		if (HitCoolDown == 0) {
			if (Collision::DiagonalQuadToQuad(Player.Quad, Target)) {
				//Novice::ScreenPrintf(0, 300, "chinchin");


				Vec2 TargetPos = { Target.LeftTop.x + (Target.RightBottom.x - Target.LeftTop.x) / 2,
								Target.LeftTop.y + (Target.RightBottom.y - Target.LeftTop.y) / 2 };


				HitStop = 5;
				HitCoolDown = HITCOOLDOWNMAX;
				if (HP > 0) {
					HP--;
				}
				if (HP <= 0) {
					HitStop = 30;
					CanMove = false;
					gameoverflag = true;
				}
			}
		}
	}
}


void PlayerMain::PlayerHit(Circle Target)
{
	if (HP > 0) {
		if (Target.radius != 0) {
			if (HitCoolDown == 0) {
				if (Collision::CircleToQuad(Target, Player.Quad)) {
					//Novice::ScreenPrintf(0, 300, "chinchin");



					HitStop = 5;
					HitCoolDown = HITCOOLDOWNMAX;
					if (HP > 0) {
						HP--;
					}
					if (HP <= 0) {
						HitStop = 30;
						CanMove = false;
						gameoverflag = true;
					}
				}
			}
		}
	}
}

void PlayerMain::PlayerHitKnockBack(Quad Target)
{
	if (HitCoolDown == 0) {
		if (Collision::DiagonalQuadToQuad(Player.Quad, Target)) {

			HitStop = 5;
			OtherSpeed.x = -100;
		}
	}
}



void PlayerMain::Draw(Screen& screen, int stand, int walk, int dash,int jump, int fall, int attack,int death)
{
	int player_gra = stand;
	int flame = 1;
	int sheets = 1;
	int isloop = false;

	if (Load == 0) {
		Load = 1;
		PlayerHpBar_gra= Novice::LoadTexture("./Resources/images/PlayerHpBar.png");
	}
	switch (PlayerAnimeMode)
	{
	case 1:
		player_gra = walk;
		flame = 5;
		sheets = 4;
		isloop = true;
		break;
	case 2:
		player_gra = dash;
		break;
	case 3:
		player_gra = jump;
		break;
	case 4:
		player_gra = fall;
		break;
	case 5:
		player_gra = attack;
		break;
	case 6:
		player_gra = death;
		flame = 60;
		sheets = 3;
		break;
	}


	//Novice::ScreenPrintf(0, 100, "%f", HitBack.y);

	Quad ImageQuad = { {Player.Pos.x - Player.ImageSize.x / 2, Player.Pos.y + Player.ImageSize.y / 2 - Player.ImageMisal},
		int(Player.ImageSize.x),int(Player.ImageSize.y) };

	if (HitCoolDown % 2 == 0 || HitCoolDown == 0) {
			screen.DrawQuad2Renban(ImageQuad, Player.SrcX, 0, Player.ImageSize.x, Player.ImageSize.y, sheets, flame, Player.AnimeFlame, player_gra, Player.Color, FaceRight, isloop);
			//screen.DrawQuad2Renban(Player.Quad, Player.SrcX, 0, Player.HitBoxSize.x, Player.HitBoxSize.y, 1, 60, Player.AnimeFlame, 0, Player.Color, FaceRight);
	}

	//screen.DrawBox(Sword.Quad.LeftTop.x, Sword.Quad.LeftTop.y, Sword.HitBoxSize.x, Sword.HitBoxSize.y, 0, 0x0000FF7F, kFillModeSolid);

	//screen.DrawLine(0, FLOOR, SCREEN_WIDTH * 1.25, FLOOR, RED);

	
	/*Novice::ScreenPrintf(0, 0, "[O][L]keys JumpPower : %0.2f", JUMPPOWER);
	Novice::ScreenPrintf(0, 20, "%d", HP);*/

	Clamp::clamp(HP, 0, 200);

	if (HP > 0) {
		Novice::DrawBox(113, 915, 210 * HP / MaxHp, 33, 0, GREEN, kFillModeSolid);
		Novice::DrawSprite(50, 900, PlayerHpBar_gra, 1, 1, 0, WHITE);
	}

}

void PlayerMain::BladeDraw(Screen& screen, int mainbladeImg, int upmainbladeImg, int downmainbladeImg, int upsubbladeImg, int downsubbladeImg, int* subbladeImg, int color, BlendMode mode) {
	if (isSwordAppear == true) {
		
			swordDrawFrame = 3;

			if (FaceUp == true) {
				isSwordHitFace = 0;
			}
			else if (FaceDown == true) {
				isSwordHitFace = 1;
			}
			else if (FaceRight == true) {
				isSwordHitFace = 2;
			}
			else {
				isSwordHitFace = 3;
			}

			if (isSwordHit == true) {
				isSaveSwordHit = true;
				for (int i = 0; i < 3; i++) {
					subSwordDrawNum[i] = CurrentSubSwordDrawNum;
					CurrentSubSwordDrawNum++;
				}
				if (CurrentSubSwordDrawNum >= 7) {
					CurrentSubSwordDrawNum = 0;
				}
			}
		
		if (swordDrawFrame > 0 && isSaveSwordHit == true) {
			Novice::SetBlendMode(mode);
			if (isSwordHitFace == 0) {
				screen.DrawQuad2({ { Player.Quad.LeftTop.x - 66,Player.Quad.LeftTop.y + 360 }, 192, 456 }, 0.0f, 0.0f, 192.0f, 456.0f, upmainbladeImg, color, true);
			}
			else if (isSwordHitFace == 1) {
				screen.DrawQuad2({ { Player.Quad.LeftTop.x - 66 ,Player.Quad.LeftBottom.y + 100  }, 192, 456 }, 0.0f, 0.0f, 192.0f, 456.0f, downmainbladeImg, color, true);
			}
			else if (isSwordHitFace == 2) {
				screen.DrawQuad2({ { Player.Quad.RightTop.x - 100,Player.Quad.LeftBottom.y + 152.0f }, 456, 192 }, 0.0f, 0.0f, 456.0f, 192.0f, mainbladeImg, color, true);
			}
			else {
				screen.DrawQuad2({ { Player.Quad.LeftTop.x + 100 - 456,Player.Quad.LeftBottom.y + 152.0f }, 456, 192 }, 0.0f, 0.0f, 456.0f, 192.0f, mainbladeImg, color, false);
			}

			Novice::SetBlendMode(kBlendModeNormal);
		}
		

		if (swordDrawFrame > 0 && isSaveSwordHit == false) {
			Novice::SetBlendMode(mode);
			if (isSwordHitFace == 0) {
				screen.DrawQuad2({ { Player.Quad.LeftTop.x - 66 ,Player.Quad.LeftTop.y + 360  }, 192, 456 }, 0.0f, 0.0f, 192.0f, 456.0f, upsubbladeImg, color, true);
			}
			else if (isSwordHitFace == 1) {
				screen.DrawQuad2({ { Player.Quad.LeftTop.x - 66 ,Player.Quad.LeftBottom.y + 100 }, 192, 456 }, 0.0f, 0.0f, 192.0f, 456.0f, downsubbladeImg, color, true);
			}
			else if (isSwordHitFace == 2) {
				screen.DrawQuad2({ { Player.Quad.RightTop.x - 100,Player.Quad.LeftBottom.y + 152.0f }, 456, 192 }, 0.0f, 0.0f, 456.0f, 192.0f, subbladeImg[3], color, true);
			}
			else {
				screen.DrawQuad2({ { Player.Quad.LeftTop.x + 100 - 456,Player.Quad.LeftBottom.y + 152.0f }, 456, 192 }, 0.0f, 0.0f, 456.0f, 192.0f, subbladeImg[3], color, false);
			}

			Novice::SetBlendMode(kBlendModeNormal);
		}
		
	}

	if (swordDrawFrame <= 0) {
		isSaveSwordHit = false;
	}
	--swordDrawFrame;
}

Vec2 PlayerMain::Translation()
{
	return Vec2(Player.Pos);
}

void PlayerMain::Movie()
{
	if (MovieTime == 0) {
		Player.Pos = { 0,0 };
		CanMove = false;
		MovieSpeed.x = 8;
	}else if (MovieTime == 135) {
		MovieSpeed.x = 0;
	}
	else if (MovieTime > 180 && MovieTime <= 360) {
		float t = (float(MovieTime - 180)) / 180;
		PulsScroll = 400 * t;
	}
	else if (MovieTime > 810 && MovieTime <= 939) {
		float t = (float(MovieTime - 810)) / 120;
		PulsScroll = 400 - 400 * t;
	}
	else if (MovieTime == 940) {
		CanMove = true;
		PulsScroll = 0;
	}

	MovieTime++;
}

bool PlayerMain::Returngameoverflag()
{
	if (gameoverflag == true) {
		gameoverflag = false;
		return true;
	}
	return false;
}

void PlayerMain::PauseLag()
{
	AttackCoolDown = 4;
}

void PlayerMain::GameOver(Screen& screen)
{
	if (HP <= 0) {
		Gravity = 0;
		Speed = { 0,0 };
		OtherSpeed = { 0,0 };
		HitBack = { 0,0 };
		HitCoolDown = 0;

		Player.Pos.x = Easing::easing(GameOverTX, Player.Pos.x , 960 + screen.Scroll.x, 1.0f / 240, Easing::easeOutSine);
		Player.Pos.y = Easing::easing(GameOverTY, Player.Pos.y, 200.0f, 1.0f / 240, Easing::easeOutSine);
	}
}
