#include "Boss.h"
#include "Degree.h"
#include "Clamp.h"
#include "Key.h"
#include "Easing.h"
#include "Randam.h"


Boss::Boss()
{
	Size = { 150,300 };

	Pos = { 1000,Size.y/2};
	LeftTop = { Pos.x - (Size.x / 2),Pos.y + (Size.y / 2)};
	LeftBottom = Vec2(Pos - (Size/2));
	RightTop= Vec2(Pos + (Size/2));
	RightBottom = { Pos.x + (Size.x / 2),Pos.y - (Size.y / 2) };
	Quad_Pos = { LeftTop,RightTop,LeftBottom,RightBottom};
	CoolTime = 200;
	Randam::SRAND();

	
}
void Boss::UpDate() {
	LeftTop = { Pos.x - (Size.x / 2),Pos.y + (Size.y / 2) };
	LeftBottom = Vec2(Pos - (Size / 2));
	RightTop = Vec2(Pos + (Size / 2));
	RightBottom = { Pos.x + (Size.x / 2),Pos.y - (Size.y / 2) };
	Quad_Pos = { LeftTop,RightTop,LeftBottom,RightBottom };

	Pos.y = Clamp::clamp(Pos.y, Size.y / 2, 10000);
	Pos.x = Clamp::clamp(Pos.x, Size.x / 2+100, (1920 * 1.25) - Size.x / 2-100);


	//攻撃を当てられた時の処理
	if (isBossHit == true) {
		HP -= 25;
	};
	if (HP <= 0) {
		IsLife = false;
	}

#pragma region Parts


	if (Head.PulsPos.y >= 0) {
		Head.PulsPosSpeed *= -1;
	}
	else if (Head.PulsPos.y <= -16) {
		Head.PulsPosSpeed *= -1;
	}

	if (Body.PulsPos.y >= 0) {
		Body.PulsPosSpeed *= -1;
	}
	else if (Body.PulsPos.y <= -16) {
		Body.PulsPosSpeed *= -1;
	}

	if (Leg.PulsPos.y >= 0) {
		Leg.PulsPosSpeed *= -1;
	}
	else if (Leg.PulsPos.y <= -16) {
		Leg.PulsPosSpeed *= -1;
	}

	if (RightArm.PulsPos.y >= 0) {
		RightArm.PulsPosSpeed *= -1;
	}
	else if (RightArm.PulsPos.y <= -16) {
		RightArm.PulsPosSpeed *= -1;
	}

	if (LeftArm.PulsPos.y >= 0) {
		LeftArm.PulsPosSpeed *= -1;
	}
	else if (LeftArm.PulsPos.y <= -16) {
		LeftArm.PulsPosSpeed *= -1;
	}

	if (ArmPosAngle >= 90) {
		ArmPosAngleSpeed *= -1;
	}
	else if (ArmPosAngle <= 0) {
		ArmPosAngleSpeed *= -1;
	}

	ArmPosAngle += ArmPosAngleSpeed;

	RightArm.PulsPos.x = -10 * cosf(Degree(ArmPosAngle) * Direction) * Direction;
	LeftArm.PulsPos.x = 10 * cosf(Degree(ArmPosAngle) * Direction) * Direction;
	RightArm.PulsPos.y = -10 * sinf(Degree(ArmPosAngle) * Direction) * Direction;
	LeftArm.PulsPos.y = -10 * sinf(Degree(ArmPosAngle) * Direction) * Direction;

	Head.PulsPos.y += Head.PulsPosSpeed.y;
	Body.PulsPos.y += Body.PulsPosSpeed.y;

	if (Direction == 1) {
		RightArm.PosMisal.x = -94;
		LeftArm.PosMisal.x = 94;
	}
	else {
		RightArm.PosMisal.x = -94;
		LeftArm.PosMisal.x = 94;
	}


	Body.ImagePos = { Pos .x + Body.PosMisal.x * Direction + Body.PulsPos.x * Body.StandMotionFlag + Body.HitReaction.x + Body.MotionPos.x,
		Pos.y + Body.PosMisal.y + Body.PulsPos.y * Body.StandMotionFlag + Body.HitReaction.y + Body.MotionPos.y};
	Body.ImageQuad = { {Body.ImagePos.x - Body.ImageSize.x / 2, Body.ImagePos.y + Body.ImageSize.y / 2},
		int(Body.ImageSize.x),int(Body.ImageSize.y) };
	Body.ColQuad = { { Body.ImagePos.x - Body.ColMisal.x * Direction - Body.ColSize.x / 2, Body.ImagePos.y + Body.ColMisal.y + Body.ColSize.y / 2},
		int(Body.ColSize.x),int(Body.ColSize.y) };

	Head.ImagePos = { Pos.x + Head.PosMisal.x * Direction + Head.PulsPos.x * Head.StandMotionFlag + Head.HitReaction.x + Head.MotionPos.x,
		Pos.y + Head.PosMisal.y + Head.PulsPos.y * Head.StandMotionFlag + Head.HitReaction.y + Head.MotionPos.y };
	Head.ImageQuad = { {Head.ImagePos.x - Head.ImageSize.x / 2, Head.ImagePos.y + Head.ImageSize.y / 2},
		int(Head.ImageSize.x),int(Head.ImageSize.y) };
	Head.ColQuad = { { Head.ImagePos.x - Head.ColMisal.x * Direction - Head.ColSize.x / 2, Head.ImagePos.y + Head.ColMisal.y + Head.ColSize.y / 2},
		int(Head.ColSize.x),int(Head.ColSize.y) };

	Leg.ImagePos = { Pos.x + Leg.PosMisal.x * Direction + Leg.PulsPos.x * Leg.StandMotionFlag + Leg.HitReaction.x + Leg.MotionPos.x,
		Pos.y + Leg.PosMisal.y + Leg.PulsPos.y * Leg.StandMotionFlag + Leg.HitReaction.y + Leg.MotionPos.y };
	Leg.ImageQuad = { {Leg.ImagePos.x - Leg.ImageSize.x / 2, Leg.ImagePos.y + Leg.ImageSize.y / 2},
		int(Leg.ImageSize.x),int(Leg.ImageSize.y) };
	Leg.ColQuad = { { Leg.ImagePos.x - Leg.ColMisal.x * Direction - Leg.ColSize.x / 2, Leg.ImagePos.y + Leg.ColMisal.y + Leg.ColSize.y / 2},
		int(Leg.ColSize.x),int(Leg.ColSize.y) };

	RightArm.ImagePos = { Pos.x + RightArm.PosMisal.x + RightArm.PulsPos.x * RightArm.StandMotionFlag * Direction + RightArm.HitReaction.x + RightArm.MotionPos.x,
		Pos.y + RightArm.PosMisal.y + RightArm.PulsPos.y * RightArm.StandMotionFlag + RightArm.HitReaction.y + RightArm.MotionPos.y };
	RightArm.ImageQuad = { {RightArm.ImagePos.x - RightArm.ImageSize.x / 2 * Direction, RightArm.ImagePos.y + RightArm.ImageSize.y / 2},
		int(RightArm.ImageSize.x * Direction),int(RightArm.ImageSize.y) };
	RightArm.ColQuad = { { RightArm.ImagePos.x - RightArm.ColMisal.x - RightArm.ColSize.x / 2, RightArm.ImagePos.y + RightArm.ColMisal.y + RightArm.ColSize.y / 2},
		int(RightArm.ColSize.x),int(RightArm.ColSize.y) };

	LeftArm.ImagePos = { Pos.x + LeftArm.PosMisal.x + LeftArm.PulsPos.x * LeftArm.StandMotionFlag * Direction + LeftArm.HitReaction.x + LeftArm.MotionPos.x,
		Pos.y + LeftArm.PosMisal.y + LeftArm.PulsPos.y * LeftArm.StandMotionFlag + LeftArm.HitReaction.y + LeftArm.MotionPos.y };
	LeftArm.ImageQuad = { {LeftArm.ImagePos.x - LeftArm.ImageSize.x / 2 * Direction , LeftArm.ImagePos.y + LeftArm.ImageSize.y / 2},
		int(LeftArm.ImageSize.x * Direction),int(LeftArm.ImageSize.y) };
	LeftArm.ColQuad = { { LeftArm.ImagePos.x - LeftArm.ColMisal.x - LeftArm.ColSize.x / 2 , LeftArm.ImagePos.y + LeftArm.ColMisal.y + LeftArm.ColSize.y / 2},
		int(LeftArm.ColSize.x),int(LeftArm.ColSize.y) };

#pragma endregion

	

}
void Boss::Set()
{
	Size = { 150,400 };

	Pos = { 1000,Size.y / 2 };
	LeftTop = { Pos.x - (Size.x / 2),Pos.y + (Size.y / 2) };
	LeftBottom = Vec2(Pos - (Size / 2));
	RightTop = Vec2(Pos + (Size / 2));
	RightBottom = { Pos.x + (Size.x / 2),Pos.y - (Size.y / 2) };
	Quad_Pos = { LeftTop,RightTop,LeftBottom,RightBottom };

}



void Boss::Draw(Screen& screen, int texsture,int headtex,int bodytex,int legtex, int rightarm,int leftarm)
{
	if (load == 0) {
		load = 1;
		Rainsword_gra = Novice::LoadTexture("./Resources/images/RainSword.png");
		Mahoujin_gra = Novice::LoadTexture("./Resources/images/mahoujin.png");
		Blade_gra = Novice::LoadTexture("./Resources/images/Boss/Blade.png");
		HoldBlade_gra = Novice::LoadTexture("./Resources/images/Boss/HoldBlade.png");
	}
	bool BossisFlip = false;

	if (Direction == 1) {
		BossisFlip = true;
	}
	else {
		BossisFlip = false;
	}
	
	
	for (int i = 0; i < kMAX_WAVE; i++) {

		screen.DrawQuad2(Wave[i].QuadPos, 0, 0, 0, 0, 0, 0x00FF0011);
		screen.DrawQuad2(Wave[i].Quad2Pos, 0, 0, 0, 0, 0, 0x00FF0011);
	}
	screen.DrawQuad2Renban(Leg.ImageQuad, SrcX, 0, Leg.ImageSize.x, Leg.ImageSize.y, 0, 60, AnimeFlame, legtex, WHITE, BossisFlip);
	screen.DrawQuad2Renban(Body.ImageQuad, SrcX, 0, Body.ImageSize.x, Body.ImageSize.y, 0, 60, AnimeFlame, bodytex, WHITE, BossisFlip);
	screen.DrawQuad2Renban(Head.ImageQuad, SrcX, 0, Head.ImageSize.x, Head.ImageSize.y, 0, 60, AnimeFlame, headtex, WHITE, BossisFlip);
	screen.DrawQuad2Renban(RightArm.ImageQuad, SrcX, 0, RightArm.ImageSize.x, RightArm.ImageSize.y, 0, 60, AnimeFlame, rightarm, WHITE, BossisFlip);
	screen.DrawQuad2Renban(LeftArm.ImageQuad, SrcX, 0, LeftArm.ImageSize.x, LeftArm.ImageSize.y, 0, 60, AnimeFlame, leftarm, WHITE, BossisFlip);

	screen.DrawQuad2(Head.ColQuad, 0, 0, 0, 0, 0, 0xFF000044);
	screen.DrawQuad2(Body.ColQuad, 0, 0, 0, 0, 0, 0xFF000044);
	screen.DrawQuad2(Leg.ColQuad, 0, 0, 0, 0, 0, 0xFF000044);
	screen.DrawQuad2(RightArm.ColQuad, 0, 0, 0, 0, 0, 0xFF000044);
	screen.DrawQuad2(LeftArm.ColQuad, 0, 0, 0, 0, 0, 0xFF000044);

	screen.DrawQuad2(BladeImageQuad, 0, 0, BladeImageSize.x, BladeImageSize.y + HoldPlusY, UseBladeGra, WHITE);
	screen.DrawQuad2(blade.Quad_Pos, 0, 0, 0, 0, 0, 0xFFFFFF11);

	screen.DrawEllipse(RightArm.ImageQuad.GetCenter(), 3, 3, 0, WHITE, kFillModeSolid);


	for (int i = 0; i < kMAX_CIR; i++) {
		screen.DrawEllipse(Circleofdeath[i].circle.pos.x, Circleofdeath[i].circle.pos.y, Circleofdeath[i].circle.radius, Circleofdeath[i].circle.radius, 0, 0xFF000066, kFillModeSolid);
		screen.DrawEllipse(Circleofdeath[i].circle.pos.x, Circleofdeath[i].circle.pos.y, Circleofdeath[i].fRad, Circleofdeath[i].fRad, 0, 0xFFFFFFFF, kFillModeWireFrame);
		screen.DrawQuad2(Circleofdeath[i].Quad_Pos, 0, 0, 600, 600, Mahoujin_gra, WHITE);
	}
	Novice::DrawBox(20, 20, HP, 80, 0, GREEN, kFillModeSolid);
	for (int i = 0; i < kMAX_RAINSWORD; i++) {
		screen.DrawQuad2(Rainofsword[i].QuadPos, 0, 0, 100, 200, Rainsword_gra, RED);
		screen.DrawQuad2(Rainofsword[i].ColQuadPos, 0, 0, 0, 0, 0, 0x00FF0022);
	}
	Novice::ScreenPrintf(0, 70, "Boss HitCount %d", HP);
	Clamp::clamp(HP, 0, 10000);
}

void Boss::State(PlayerMain& player)
{
	Vec2 Distance = Pos - player.Translation();
	if (Action == false) {
		if (Distance.Length() < 500) {
			pattarn = NEAR_1;
		}
		else
			if (Distance.Length() < 900) {
				pattarn = MIDDLE;
			}
			else {
				pattarn = FAR_1;
			}
		if (HP < ThreeQuarterHP) {
			hppattarn = THREEQUARTERS;
			if (HP < HalfHP) {
				hppattarn = HALF;
			}
		}else {
				hppattarn = NORMAL;
			}
	}
}
void Boss::KeepUP(PlayerMain& player) {
	//プレイヤーについていく関数使わないかもしれない
	Vec2 vel = (player.Translation() - Pos).Normalized();
	Pos.x += vel.x*20;

}
void Boss::KeepUpWaitBack(PlayerMain&player)
{
	
	keep.Time++;
	if (keep.Time == 20) {
		keep.Time = 0;
		keep.rand = Randam::RAND(0, 100);
	}
	if (0 <= keep.rand && keep.rand <= 30) {
		Vec2 vel = (player.Translation() - Pos).Normalized();
		Pos.x += vel.x * 5;
	}
	if (31 <= keep.rand && keep.rand <= 85) {
		Vec2 vel = (player.Translation() - Pos).Normalized();
		Pos.x -= vel.x * 5;
	}
	if (86 <= keep.rand && keep.rand <= 100) {
		
	}
}
void Boss::BackStep(PlayerMain& player)
{	
	Vec2 Distance = Pos - player.Translation();
	if (StepT==0) {
		
		StepFPos = Pos.x;
	}
	
	if (Distance.Length()< 400) {
		if (Pos.x < 200 || Pos.x>2200) {
			ShockWaveAttackCenter(player);
		}
		else {
			bStep = true;
		}
	}
	else if (bStep == false) {
		Action = false;
	}

	if (bStep == true) {
		Pos.x = Easing::easing(StepT, StepFPos, StepFPos + 600 * -Direction, 0.02f, Easing::easeInQuart);
		if (StepT == 1) {
			StepT = 0;
			Action = false;
			bStep = false;
		}
	}
	

}
void Boss::DirectionGet(PlayerMain& player) {
	//プレイヤーの位置によってマイナスかプラスかわかる関羽数うすうす進巣
	if (player.Translation().x <= Pos.x) {
		Direction = -1;
	}
	else Direction = 1;
}
void Boss::RandMoveSet() {
	
	
		for (int i = 0; i < MAX_PATTERN; i++) {
			if (0 <= i && i <= 9) {
				MovePattern[i] = array.AttackFunction01;

			}
			else
				if (9 <= i && i <=19) {
					MovePattern[i] = array.AttackFunction02;

				}
				else
					if (19 <= i && i <= 29) {
						MovePattern[i] = array.AttackFunction03;

					}
					else
						if (29 <= i && i <= 39) {
							MovePattern[i] = array.AttackFunction04;

						}
						else
							if (39 <= i && i <=49) {
								MovePattern[i] = array.AttackFunction05;

							}
							else
								if (MovePattern[i] == 0) {
									MovePattern[i] = array.NormalAttack;

								}
		}
	
	
}

int Boss::ReloadMove(int Movearray)
{
	int rand = Randam::RAND(0, 5);
	if (rand == 0) {
		if (MoveArray == array.NormalAttack) {
			rand = Randam::RAND(0, 5);
		}
		else { return array.NormalAttack; }
	}
	if (rand == 1) {
		if (MoveArray == array.AttackFunction01) {
			rand = Randam::RAND(0, 5);
		}
		else { return array.AttackFunction01; }
	}
	if (rand == 2) {
		if (MoveArray == array.AttackFunction02) {
			rand = Randam::RAND(0, 5);
		}
		else { return array.AttackFunction02; }
	}
	if (rand == 3) {
		if (MoveArray == array.AttackFunction03) {
			rand = Randam::RAND(0, 5);
		}
		else { return array.AttackFunction03; }
	}
	if (rand == 4) {
		if (MoveArray == array.AttackFunction04) {
			rand = Randam::RAND(0, 5);
		}
		else {	return array.AttackFunction04;	}
	}
	if (rand == 5) {
		if (MoveArray == array.AttackFunction05) {
			rand = Randam::RAND(0, 5);
		}
		else { return array.AttackFunction05; }
	}
	
}

void Boss::RandamMoveSelect(int rand,PlayerMain& player,Screen& screen)
{
	Novice::ScreenPrintf(1000, 0, "Cooltime::%d", CoolTime);
	Novice::ScreenPrintf(1000, 20, "Action_Boss::%d", Action);
	Novice::ScreenPrintf(1000, 40, "Movearray::%d", MoveArray);
	Novice::ScreenPrintf(1000, 60, "MovePattarn::%d", MovePattern[MoveArray]);
	Novice::ScreenPrintf(1000, 80, "boss:state:%d", pattarn);
	Novice::ScreenPrintf(1000, 200, "boss:hpstate:%d", hppattarn);

	Novice::ScreenPrintf(Pos.x, Pos.y - 200+SCREEN_HEIGHT, "HP:%d", HP);


	if (CoolTime == 0&&Action==false) {
		MoveArray =rand;

		if (MovePattern[MoveArray] == FMoveArray) {
			Novice::ScreenPrintf(1000, 100, "Reload:%d", reload);

			if (reload == 0) {
				Action = true;

			}
			if (reload == 1) {
				MovePattern[MoveArray] = ReloadMove(FMoveArray);
			}
		}
		else {
			Action = true;

		}
		DirectionGet(player);
	}
	else if (CoolTime != 0&&Action==false) {
		CoolTime--;
		State(player);
		reload = Randam::RAND(0, 1);
		KeepUpWaitBack(player); 
		
		RandMoveSet();
		DirectionGet(player);

	}

		KeepWaveAttack();

		if (Action == true) {
			
			switch (hppattarn)
			{
				
			case NORMAL:
				CoolTime = 10;

				switch (pattarn) {
				case NEAR_1:
				{
					if (MovePattern[MoveArray] == array.NormalAttack) {
						//通常攻撃のコードはここ
						BackStep(player);

						//NomalSwordAttack(player);
						//RainOfSwordAttack();
						//CircleOfDeathAttack(player);
						//ShockWaveAttack(player, screen);
						//ShockWaveAttack2(player, screen);
						FMoveArray = array.NormalAttack;
					}
					if (MovePattern[MoveArray] == array.AttackFunction01) {
						//5%の攻撃
						NomalRotedSwordAttack(player);
						/*NomalSwordAttack(player);
						array.bAttackFunction01 = true;
						array.InitNotThis(array.bAttackFunction01);*/
						/*CoolTime = 40;*/
						FMoveArray = array.AttackFunction01;

						
						//Action = false;
					}
					if (MovePattern[MoveArray] == array.AttackFunction02 ) {
						//5%の攻撃
						//NomalRotedSwordAttack(player);
						//NomalSwordAttack(player);

						NomalSwordAttack(player);

						
						FMoveArray = array.AttackFunction02;
						/*CoolTime = 0;
						Action = false;*/
					}
					if (MovePattern[MoveArray] == array.AttackFunction03 ) {
						//5%の攻撃
						//NomalSwordAttack(player);
						ShockWaveAttack(player, screen);

						//NomalRotedSwordAttack(player);
						/*Action = false;
						CoolTime = 0;*/
						FMoveArray = array.AttackFunction03;


					}
					if (MovePattern[MoveArray] == array.AttackFunction04 ) {
						//5%の攻撃
						//JumpAttack(player);
						//NomalRotedSwordAttack(player);
						//NomalSwordAttack(player);
						ShockWaveAttack(player, screen);						
						FMoveArray = array.AttackFunction04;
						/*CoolTime = 0;
						Action = false;*/

					}
					if (MovePattern[MoveArray] == array.AttackFunction05 ) {
						//5%の攻撃
						//JumpAttack(player);
						//NomalRotedSwordAttack(player);
						//NomalSwordAttack(player);
						//ShockWaveAttack(player, screen);

						
						//FMoveArray = array.AttackFunction05;

						Action = false;
						CoolTime = 0;

					}
					if (MovePattern[MoveArray] == 0) {
						
						Action = false;
					}
					//関数の終わりにAction=falseと関数内で使った変数の初期化をしろおおおおおおお
					//関数ないとこにはAction=falseを入れること。
					break;
				}
				case MIDDLE:
				{
					if (MovePattern[MoveArray] == array.NormalAttack) {
						//通常攻撃のコードはここ
						//NomalSwordAttack(player);
						NomalRotedSwordAttack(player);
						FMoveArray = array.NormalAttack;
					}
					if (MovePattern[MoveArray] == array.AttackFunction01) {
						//5%の攻撃
						//NomalRotedSwordAttack(player);
						NomalSwordAttack(player);
						/*Action = false;*/
						FMoveArray = array.AttackFunction01;

					}
					if (MovePattern[MoveArray] == array.AttackFunction02) {
						//5%の攻撃
						//NomalRotedSwordAttack(player);
						//NomalSwordAttack(player);

						//FMoveArray = array.AttackFunction02;
						Action = false;
						CoolTime = 0;

					}
					if (MovePattern[MoveArray] == array.AttackFunction03) {
						//5%の攻撃
						NomalSwordAttack(player);

						//NomalRotedSwordAttack(player);
						/*Action = false;*/
						FMoveArray = array.AttackFunction03;
					}
					if (MovePattern[MoveArray] == array.AttackFunction04) {
						//5%の攻撃
						//JumpAttack(player);
						//NomalRotedSwordAttack(player);
						ShockWaveAttack(player, screen);
						/*Action = false;*/
						FMoveArray = array.AttackFunction04;
					}
					if (MovePattern[MoveArray] == array.AttackFunction05) {
						//5%の攻撃
						//JumpAttack(player);
						//NomalRotedSwordAttack(player);
						//ShockWaveAttack(player, screen);
						CoolTime = 0;
						Action = false;
						//FMoveArray = array.AttackFunction05;
					}
					if (MovePattern[MoveArray] == 0) {
						Action = false;
					}
					//関数の終わりにAction=falseと関数内で使った変数の初期化をしろおおおおおおお
					//関数ないとこにはAction=falseを入れること。
					break;
				}
				case FAR_1:
				{
					if (MovePattern[MoveArray] == array.NormalAttack) {
						//通常攻撃のコードはここ
						//NomalSwordAttack(player);
						//JumpAttack(player, screen);
						ShockWaveAttack(player, screen);
						FMoveArray = array.NormalAttack;

					}
					if (MovePattern[MoveArray] == array.AttackFunction01) {
						//5%の攻撃
						//NomalRotedSwordAttack(player);
						//JumpAttack(player, screen);
						NomalSwordAttack(player);
						//ShockWaveAttack(player, screen);
						//CircleOfDeathAttack(player);
						/*Action = false;*/
						FMoveArray = array.AttackFunction01;
					}
					if (MovePattern[MoveArray] == array.AttackFunction02) {
						//5%の攻撃
						NomalRotedSwordAttack(player);
						//NomalRotedSwordAttack(player);
						//CircleOfDeathAttack(player);
						//NomalSwordAttack(player);
						//ShockWaveAttack(player, screen);
						//JumpAttack(player, screen);
						/*Action = false;*/
						FMoveArray = array.AttackFunction02;
					}
					if (MovePattern[MoveArray] == array.AttackFunction03) {
						//5%の攻撃
						//NomalRotedSwordAttack(player);
						JumpAttack(player, screen);
						//ShockWaveAttack(player, screen);
						//CircleOfDeathAttack(player);
						FMoveArray = array.AttackFunction03;
						CoolTime = 45;
						/*Action = false;*/
					}
					if (MovePattern[MoveArray] == array.AttackFunction04) {
						//5%の攻撃
						//JumpAttack(player, screen);
						//ShockWaveAttack(player, screen);
						//CircleOfDeathAttack(player);
						//FMoveArray = array.AttackFunction04;
						Action = false;
						CoolTime = 0;
					}
					if (MovePattern[MoveArray] == array.AttackFunction05) {
						//5%の攻撃
						//JumpAttack(player, screen);
						//ShockWaveAttack(player, screen);
						//CircleOfDeathAttack(player);
						//FMoveArray = array.AttackFunction05;
						Action = false; 
						CoolTime = 0;
					}
					if (MovePattern[MoveArray] == 0) {
						Action = false;
					}
					//関数の終わりにAction=falseと関数内で使った変数の初期化をしろおおおおおおお
					//関数ないとこにはAction=falseを入れること。
					break;
				}
				}
				break;

				case THREEQUARTERS:
					CoolTime = 0;

					switch (pattarn) {
					case NEAR_1:
					{
						

						if (MovePattern[MoveArray] == array.NormalAttack) {
							//通常攻撃のコードはここ
							//NomalSwordAttack2(player);
							//CircleOfDeathAttack();
							//ShockWaveAttack(player, screen);
							BackStep(player);
							FMoveArray = array.NormalAttack;
						}
						if (MovePattern[MoveArray] == array.AttackFunction01) {
							//5%の攻撃
							NomalRotedSwordAttack(player);
							/*NomalSwordAttack(player);
							array.bAttackFunction01 = true;
							array.InitNotThis(array.bAttackFunction01);*/
							/*CoolTime = 40;*/
							FMoveArray = array.AttackFunction01;


							//Action = false;
						}
						if (MovePattern[MoveArray] == array.AttackFunction02) {
							//5%の攻撃
							//NomalRotedSwordAttack(player);
							//NomalSwordAttack2(player);
							RainOfSwordAttack();


							FMoveArray = array.AttackFunction02;
							//CoolTime = 30;
							//Action = false;
						}
						if (MovePattern[MoveArray] == array.AttackFunction03) {
							//5%の攻撃
							//NomalSwordAttack(player);
							ShockWaveAttack(player, screen);

							//NomalRotedSwordAttack(player);
							/*Action = false;
							CoolTime = 0;*/
							FMoveArray = array.AttackFunction03;


						}
						if (MovePattern[MoveArray] == array.AttackFunction04) {
							//5%の攻撃
							//JumpAttack(player);
							//NomalRotedSwordAttack(player);
							NomalSwordAttack(player);
							//ShockWaveAttack(player, screen);
							//ShockWaveAttack(player, screen);

							FMoveArray = array.AttackFunction04;
							//BackStep(player);

							/*CoolTime = 0;
							Action = false;*/

						}
						if (MovePattern[MoveArray] == array.AttackFunction05) {
							//5%の攻撃
							//JumpAttack(player);
							//NomalRotedSwordAttack2(player);
							//NomalSwordAttack(player);
							//ShockWaveAttack(player, screen);
							/*RainOfSwordAttack();

							FMoveArray = array.AttackFunction05;*/

							Action = false;
							CoolTime = 0;

						}
						if (MovePattern[MoveArray] == 0) {

							Action = false;
						}
						//関数の終わりにAction=falseと関数内で使った変数の初期化をしろおおおおおおお
						//関数ないとこにはAction=falseを入れること。
						break;
					}
					case MIDDLE:
					{
						if (MovePattern[MoveArray] == array.NormalAttack) {
							//通常攻撃のコードはここ
							//NomalSwordAttack(player);
							NomalRotedSwordAttack(player);
							FMoveArray = array.NormalAttack;
						}
						if (MovePattern[MoveArray] == array.AttackFunction01) {
							//5%の攻撃
							//NomalRotedSwordAttack(player);
							NomalSwordAttack2(player);
							/*Action = false;*/
							FMoveArray = array.AttackFunction01;

						}
						if (MovePattern[MoveArray] == array.AttackFunction02) {
							//5%の攻撃
							//NomalRotedSwordAttack(player);
							//NomalSwordAttack2(player);
							RainOfSwordAttack();
							//FMoveArray = array.AttackFunction02;
							/*Action = false;
							CoolTime = 0;*/

						}
						if (MovePattern[MoveArray] == array.AttackFunction03) {
							//5%の攻撃
							NomalSwordAttack2(player);

							//NomalRotedSwordAttack(player);
							/*Action = false;*/
							FMoveArray = array.AttackFunction03;
						}
						if (MovePattern[MoveArray] == array.AttackFunction04) {
							//5%の攻撃
							//JumpAttack(player);
							//NomalRotedSwordAttack(player);
							ShockWaveAttack(player, screen);
							/*Action = false;*/
							FMoveArray = array.AttackFunction04;
						}
						if (MovePattern[MoveArray] == array.AttackFunction05) {
							//5%の攻撃
							//JumpAttack(player);
							//NomalRotedSwordAttack(player);
							//ShockWaveAttack(player, screen);
							//ShockWaveAttack2(player, screen);
							BackStep(player);

							/*CoolTime = 0;
							Action = false;*/
							//FMoveArray = array.AttackFunction05;
						}
						if (MovePattern[MoveArray] == 0) {
							Action = false;
						}
						//関数の終わりにAction=falseと関数内で使った変数の初期化をしろおおおおおおお
						//関数ないとこにはAction=falseを入れること。
						break;
					}
					case FAR_1:
					{
						if (MovePattern[MoveArray] == array.NormalAttack) {
							//通常攻撃のコードはここ
							//NomalSwordAttack(player);
							//JumpAttack(player, screen);
							//ShockWaveAttack(player, screen);
							ShockWaveAttack(player, screen);
							FMoveArray = array.NormalAttack;

						}
						if (MovePattern[MoveArray] == array.AttackFunction01) {
							//5%の攻撃
							//NomalRotedSwordAttack(player);
							//JumpAttack(player, screen);
							//ShockWaveAttack(player, screen);
							//CircleOfDeathAttack(player);
							Action = false;
							CoolTime = 0;
							//FMoveArray = array.AttackFunction01;
						}
						if (MovePattern[MoveArray] == array.AttackFunction02) {
							//5%の攻撃
							//NomalRotedSwordAttack(player);
							//NomalRotedSwordAttack(player);
							//CircleOfDeathAttack(player);

							//ShockWaveAttack(player, screen);
							JumpAttack(player, screen);
							/*Action = false;*/
							FMoveArray = array.AttackFunction02;
							CoolTime = 20;
						}
						if (MovePattern[MoveArray] == array.AttackFunction03) {
							//5%の攻撃
							//NomalRotedSwordAttack(player);
							//JumpAttack(player, screen);
							/*Action = false;*/
							//ShockWaveAttack(player, screen);
							CircleOfDeathAttack(player);
							FMoveArray = array.AttackFunction03;
						}
						if (MovePattern[MoveArray] == array.AttackFunction04) {
							//5%の攻撃
							//JumpAttack(player, screen);
							//ShockWaveAttack(player, screen);
							CircleOfDeathAttack(player);

							/*Action = false;*/
							FMoveArray = array.AttackFunction04;
						}
						if (MovePattern[MoveArray] == array.AttackFunction05) {
							//5%の攻撃
							//JumpAttack(player, screen);
							//ShockWaveAttack(player, screen);
							//CircleOfDeathAttack(player);

							Action = false;
							CoolTime = 0;
							//FMoveArray = array.AttackFunction05;
						}
						if (MovePattern[MoveArray] == 0) {
							Action = false;
						}
						//関数の終わりにAction=falseと関数内で使った変数の初期化をしろおおおおおおお
						//関数ないとこにはAction=falseを入れること。
						break;
					}
					}
					break;

			case HALF:
				CoolTime = 0;
				switch (pattarn) {
				case NEAR_1:
				{
					

					if (MovePattern[MoveArray] == array.NormalAttack) {
						//通常攻撃のコードはここ
						NomalSwordAttack3(player);
						//CircleOfDeathAttack();
						//ShockWaveAttack(player, screen);
						/*CoolTime = 50;*/
						FMoveArray = array.NormalAttack;
					}
					if (MovePattern[MoveArray] == array.AttackFunction01) {
						//5%の攻撃
						//NomalRotedSwordAttack(player);
						NomalSwordAttack2(player);
						FMoveArray = array.AttackFunction01;
						/*Action = false;*/
						CoolTime = 20;
					}
					if (MovePattern[MoveArray] == array.AttackFunction02) {
						//5%の攻撃
						//NomalRotedSwordAttack(player);
						//NomalSwordAttack3(player);
						CircleOfDeathAttack(player);
						FMoveArray = array.AttackFunction02;
						/*Action = false;*/

					}
					if (MovePattern[MoveArray] == array.AttackFunction03) {
						//5%の攻撃
						//NomalSwordAttack(player);
						ShockWaveAttack2(player, screen);

						//NomalRotedSwordAttack(player);
						/*Action = false;*/
						FMoveArray = array.AttackFunction03;
					}
					if (MovePattern[MoveArray] == array.AttackFunction04) {
						//5%の攻撃
						//JumpAttack(player);
						//NomalRotedSwordAttack(player);
						//NomalSwordAttack(player);
						BackStep(player);


						/*Action = false;*/
						FMoveArray = array.AttackFunction04;
						//CoolTime = 20;
					}
					if (MovePattern[MoveArray] == array.AttackFunction05) {
						//5%の攻撃
						//JumpAttack(player);
						//NomalRotedSwordAttack(player);
						//NomalSwordAttack(player);
						//ShockWaveAttack(player, screen);
						RainOfSwordAttack();
						/*Action = false;
						CoolTime = 0;*/
						FMoveArray = array.AttackFunction05;
					}
					if (MovePattern[MoveArray] == 0) {
						Action = false;
					}
					//関数の終わりにAction=falseと関数内で使った変数の初期化をしろおおおおおおお
					//関数ないとこにはAction=falseを入れること。
					break;
				}
				case MIDDLE:
				{
					if (MovePattern[MoveArray] == array.NormalAttack) {
						//通常攻撃のコードはここ
						//NomalSwordAttack(player);
						NomalRotedSwordAttack2(player);
						FMoveArray = array.NormalAttack;
					}
					if (MovePattern[MoveArray] == array.AttackFunction01) {
						//5%の攻撃
						//NomalRotedSwordAttack(player);
						CircleOfDeathAttack(player);

						//NomalSwordAttack(player);
						/*Action = false;*/
						FMoveArray = array.AttackFunction01;
					}
					if (MovePattern[MoveArray] == array.AttackFunction02) {
						//5%の攻撃
						NomalRotedSwordAttack(player);
						//NomalSwordAttack(player);
						//CircleOfDeathAttack(player);

						/*Action = false;*/
						FMoveArray = array.AttackFunction02;
					}
					if (MovePattern[MoveArray] == array.AttackFunction03) {
						//5%の攻撃
						//NomalSwordAttack(player);
						//CircleOfDeathAttack(player);
						RainOfSwordAttack();
						//NomalRotedSwordAttack(player);
						/*Action = false;*/
						FMoveArray = array.AttackFunction03;
					}
					if (MovePattern[MoveArray] == array.AttackFunction04) {
						//5%の攻撃
						//JumpAttack(player);
						//NomalRotedSwordAttack(player);
						ShockWaveAttack2(player, screen);
						/*Action = false;*/
						FMoveArray = array.AttackFunction04;
					}
					if (MovePattern[MoveArray] == array.AttackFunction05) {
						//5%の攻撃
						//JumpAttack(player);
						//NomalRotedSwordAttack(player);
						ShockWaveAttack(player, screen);

						/*Action = false;*/
						CoolTime = 20;
						FMoveArray = array.AttackFunction05;
					}
					if (MovePattern[MoveArray] == 0) {
						Action = false;
					}
					//関数の終わりにAction=falseと関数内で使った変数の初期化をしろおおおおおおお
					//関数ないとこにはAction=falseを入れること。
					break;
				}
				case FAR_1:
				{
					if (MovePattern[MoveArray] == array.NormalAttack) {
						//通常攻撃のコードはここ
						//NomalSwordAttack(player);
						//JumpAttack(player, screen);
						ShockWaveAttack2(player, screen);

						FMoveArray = array.NormalAttack;

					}
					if (MovePattern[MoveArray] == array.AttackFunction01) {
						//5%の攻撃
						//NomalRotedSwordAttack(player);
						//JumpAttack(player, screen);
						//ShockWaveAttack(player, screen);
						CircleOfDeathAttack(player);
						/*Action = false;*/
						FMoveArray = array.AttackFunction01;
						CoolTime = 20;
					}
					if (MovePattern[MoveArray] == array.AttackFunction02) {
						//5%の攻撃
						//NomalRotedSwordAttack(player);
						//NomalRotedSwordAttack(player);
						//CircleOfDeathAttack(player);

						//ShockWaveAttack(player, screen);
						JumpAttack(player, screen);
						/*Action = false;*/
						FMoveArray = array.AttackFunction02;
						CoolTime = 10;
					}
					if (MovePattern[MoveArray] == array.AttackFunction03) {
						//5%の攻撃
						//NomalRotedSwordAttack(player);
						//JumpAttack(player, screen);
						//ShockWaveAttack(player, screen);
						//CircleOfDeathAttack(player);
						RainOfSwordAttack();
						FMoveArray = array.AttackFunction03;
						/*Action = false;
						CoolTime = 0;*/

					}
					if (MovePattern[MoveArray] == array.AttackFunction04) {
						//5%の攻撃
						//JumpAttack(player, screen);
						//ShockWaveAttack(player, screen);
						//CircleOfDeathAttack(player);
						NomalRotedSwordAttack2(player);
						/*Action = false;*/
						FMoveArray = array.AttackFunction04;
					}
					if (MovePattern[MoveArray] == array.AttackFunction05) {
						//5%の攻撃
						//JumpAttack(player, screen);
						//ShockWaveAttack(player, screen);
						//CircleOfDeathAttack(player);
						NomalSwordAttack3(player);
						/*Action = false;*/
						FMoveArray = array.AttackFunction05;
					}
					if (MovePattern[MoveArray] == 0) {
						Action = false;
					}
					//関数の終わりにAction=falseと関数内で使った変数の初期化をしろおおおおおおお
					//関数ないとこにはAction=falseを入れること。
					break;
				}
				}
				break;


			}
		}
}


///スキル関数
void Boss::AttackFunction01(Screen&screen)
{
	for (int i = 0; i < 6; i++) {
		ArkSword.quad[i].LeftTop = { Pos.x + i * 100 * Direction, 400 };
		ArkSword.quad[i].RightTop = {LeftTop.x-100, 400 };
		ArkSword.quad[i].LeftBottom = { LeftTop.x,0  };
		ArkSword.quad[i].RightBottom = { RightTop.x, 0 };

		screen.DrawQuad2(ArkSword.quad[i], 0, 0, 0, 0, 0, GREEN );
	}
}

void Boss::NomalSwordAttack(PlayerMain& player)
{
	int MOTIONEND = 25;
	UseBladeGra = HoldBlade_gra;
	SwordAttack = true;
	float Distance = Pos.x - player.Translation().x;
	if ((Distance < 300 && Distance > -300) || Attack == true) {
		if (Attack == false) {
			AttackStartTime = 0;
		}
		Attack = true;
	}
	else { 
		KeepUP(player); 
		
	}
	//DirectionGet(player);

	if (BossMotionTime == 0) {
		RightArm.StandMotionFlag = 0;
	}
	else {
		if (BossMotionTime <= MOTIONEND) {
			float t = 1 - (BossMotionTime / MOTIONEND);
			RightArm.MotionPos.x = 94 * (1.0f - t * t * t * t);
			RightArm.MotionPos.y = 140 * (1.0f - t * t * t * t);

			float angle = 180 - 180 * (1.0f - t * t * t * t);

			float theta = angle / 180.0f * M_PI;

			Matrix2x2 mat = MakeRotateMatrix(theta);

			Vec2 LeftTop = { -RightArm.ImageSize.x / 2 , -RightArm.ImageSize.y / 2 };
			Vec2 RightTop = { RightArm.ImageSize.x / 2 , -RightArm.ImageSize.y / 2 };
			Vec2 LeftBottom = { -RightArm.ImageSize.x / 2 , RightArm.ImageSize.y / 2 };
			Vec2 RightBottom = { RightArm.ImageSize.x / 2 , RightArm.ImageSize.y / 2 };

			RightArm.ImageQuad.LeftTop = Multiply(LeftTop, mat);
			RightArm.ImageQuad.RightTop = Multiply(RightTop, mat);
			RightArm.ImageQuad.LeftBottom = Multiply(LeftBottom, mat);
			RightArm.ImageQuad.RightBottom = Multiply(RightBottom, mat);

			RightArm.ImageQuad.LeftTop += RightArm.ImagePos;
			RightArm.ImageQuad.RightTop += RightArm.ImagePos;
			RightArm.ImageQuad.LeftBottom += RightArm.ImagePos;
			RightArm.ImageQuad.RightBottom += RightArm.ImagePos;
		}
	}

	if (BossMotionTime >= MOTIONEND) {
		RightArm.MotionPos.x = 9999;
		RightArm.MotionPos.y = 9999;
		if (Attack == true) {
			if (AttackStartTime <= 0) {
				blade.angle = Easing::easing(blade.t, 0, 150, 0.03f, Easing::easeInOutBack) * -Direction;

				blade.theta = blade.angle / 180.0f * M_PI;

				Matrix2x2 mat = MakeRotateMatrix(blade.theta);
				//剣の座標最初の
				Vec2 LeftTop = { -30 , 400 };
				Vec2 RightTop = { 30  , 400 };
				Vec2 LeftBottom = { -30 , 50 };
				Vec2 RightBottom = { 30 , 50 };
				blade.Quad_Pos = { blade.LeftTop,blade.RightTop,blade.LeftBottom,blade.RightBottom };

				blade.LeftTop = Multiply(LeftTop, mat);
				blade.RightTop = Multiply(RightTop, mat);
				blade.LeftBottom = Multiply(LeftBottom, mat);
				blade.RightBottom = Multiply(RightBottom, mat);

				blade.LeftTop += Pos;
				blade.RightTop += Pos;
				blade.LeftBottom += Pos;
				blade.RightBottom += Pos;

				blade.Quad_Pos = { blade.LeftTop,blade.RightTop,blade.LeftBottom,blade.RightBottom };

				if (blade.t == 1 && BossMotionTime >= 64) {
					blade.Init();
					Action = false;
					Attack = false;
					SwordAttack = false;
					bNomalSwordAttack = true;
					BossMotionTime = 0;
					RightArm.StandMotionFlag = 1;
					RightArm.MotionPos = {0,0};
				}

				BladeImageLink(mat);

			}
			else {
				AttackStartTime--;
			}
		}
	}
	BossMotionTime++;
}
void Boss::NomalSwordAttack2(PlayerMain& player)
{
	int MOTIONEND = 20;
	UseBladeGra = HoldBlade_gra;
	SwordAttack = true;
	
	//int Fpos = Pos.x;
	float Distance = Pos.x - player.Translation().x;
	if ((Distance < 300 && Distance > -300) || Attack == true) {
		if (Attack == false) {
			AttackStartTime = 4;
			blade.FPosBoss.x = Pos.x;

		}
		Attack = true;
	}
	else {
		KeepUP(player);
		blade.FPosBoss.x = Pos.x;

	}
	//DirectionGet(player);
	if (BossMotionTime == 0) {
		RightArm.StandMotionFlag = 0;
	}
	else {
		if (BossMotionTime <= MOTIONEND) {
			float t = 1 - (BossMotionTime / MOTIONEND);
			RightArm.MotionPos.x = 94 * (1.0f - t * t * t * t);
			RightArm.MotionPos.y = 140 * (1.0f - t * t * t * t);

			float angle = 180 - 180 * (1.0f - t * t * t * t);

			float theta = angle / 180.0f * M_PI;

			Matrix2x2 mat = MakeRotateMatrix(theta);

			Vec2 LeftTop = { -RightArm.ImageSize.x / 2 , -RightArm.ImageSize.y / 2 };
			Vec2 RightTop = { RightArm.ImageSize.x / 2 , -RightArm.ImageSize.y / 2 };
			Vec2 LeftBottom = { -RightArm.ImageSize.x / 2 , RightArm.ImageSize.y / 2 };
			Vec2 RightBottom = { RightArm.ImageSize.x / 2 , RightArm.ImageSize.y / 2 };

			RightArm.ImageQuad.LeftTop = Multiply(LeftTop, mat);
			RightArm.ImageQuad.RightTop = Multiply(RightTop, mat);
			RightArm.ImageQuad.LeftBottom = Multiply(LeftBottom, mat);
			RightArm.ImageQuad.RightBottom = Multiply(RightBottom, mat);

			RightArm.ImageQuad.LeftTop += RightArm.ImagePos;
			RightArm.ImageQuad.RightTop += RightArm.ImagePos;
			RightArm.ImageQuad.LeftBottom += RightArm.ImagePos;
			RightArm.ImageQuad.RightBottom += RightArm.ImagePos;
		}
	}

	if (BossMotionTime >= MOTIONEND) {
		RightArm.MotionPos.x = 9999;
		RightArm.MotionPos.y = 9999;
		if (Attack == false) {
			blade.FPosBoss.x = Pos.x;

		}
		if (Attack == true) {
			if (AttackStartTime <= 0) {
				blade.angle = Easing::easing(blade.t, 0, 200, 0.035f, Easing::easeInBack) * -Direction;

				blade.theta = blade.angle / 180.0f * M_PI;
				if (blade.t == 1) {
					if (blade.t == 1 && blade.t_back == 0) {
						DirectionGet(player);
					}
					blade.angle = Easing::easing(blade.t_back, 200, 0, 0.025f, Easing::easeInOutBack) * -Direction;

					blade.theta = blade.angle / 180.0f * M_PI;
					Pos.x = Easing::easing(blade.Boss_t, blade.FPosBoss.x, blade.FPosBoss.x + (150 * Direction), 0.05, Easing::easeInQuart);
				}
				else {
				}
				Matrix2x2 mat = MakeRotateMatrix(blade.theta);
				//剣の座標最初の
				Vec2 LeftTop = { -30 , 400 };
				Vec2 RightTop = { 30  , 400 };
				Vec2 LeftBottom = { -30 , 50 };
				Vec2 RightBottom = { 30 , 50 };
				blade.Quad_Pos = { blade.LeftTop,blade.RightTop,blade.LeftBottom,blade.RightBottom };


				blade.LeftTop = Multiply(LeftTop, mat);
				blade.RightTop = Multiply(RightTop, mat);
				blade.LeftBottom = Multiply(LeftBottom, mat);
				blade.RightBottom = Multiply(RightBottom, mat);

				blade.LeftTop += Pos;
				blade.RightTop += Pos;
				blade.LeftBottom += Pos;
				blade.RightBottom += Pos;

				blade.Quad_Pos = { blade.LeftTop,blade.RightTop,blade.LeftBottom,blade.RightBottom };



				if (blade.t_back == 1) {
					blade.Init();
					Action = false;
					Attack = false;
					SwordAttack = false;
					bNomalSwordAttack = true;
					BossMotionTime = 0;
					RightArm.StandMotionFlag = 1;
					RightArm.MotionPos = { 0,0 };
				}

				BladeImageLink(mat);
			}
			else {
				AttackStartTime--;
			}
		}
	}
	BossMotionTime++;
}
void Boss::NomalSwordAttack3(PlayerMain& player)
{
	int MOTIONEND = 20;
	UseBladeGra = HoldBlade_gra;
	SwordAttack = true;

	//int Fpos = Pos.x;
	float Distance = Pos.x - player.Translation().x;
	if ((Distance < 300 && Distance > -300) || Attack == true) {
		if (Attack == false) {
			AttackStartTime = 4;
			blade.FPosBoss.x = Pos.x;

		}
		Attack = true;
	}
	else {
		KeepUP(player);
		blade.FPosBoss.x = Pos.x;

	}
	//DirectionGet(player);

	if (BossMotionTime == 0) {
		RightArm.StandMotionFlag = 0;
	}
	else {
		if (BossMotionTime <= MOTIONEND) {
			float t = 1 - (BossMotionTime / MOTIONEND);
			RightArm.MotionPos.x = 94 * (1.0f - t * t * t * t);
			RightArm.MotionPos.y = 140 * (1.0f - t * t * t * t);

			float angle = 180 - 180 * (1.0f - t * t * t * t);

			float theta = angle / 180.0f * M_PI;

			Matrix2x2 mat = MakeRotateMatrix(theta);

			Vec2 LeftTop = { -RightArm.ImageSize.x / 2 , -RightArm.ImageSize.y / 2 };
			Vec2 RightTop = { RightArm.ImageSize.x / 2 , -RightArm.ImageSize.y / 2 };
			Vec2 LeftBottom = { -RightArm.ImageSize.x / 2 , RightArm.ImageSize.y / 2 };
			Vec2 RightBottom = { RightArm.ImageSize.x / 2 , RightArm.ImageSize.y / 2 };

			RightArm.ImageQuad.LeftTop = Multiply(LeftTop, mat);
			RightArm.ImageQuad.RightTop = Multiply(RightTop, mat);
			RightArm.ImageQuad.LeftBottom = Multiply(LeftBottom, mat);
			RightArm.ImageQuad.RightBottom = Multiply(RightBottom, mat);

			RightArm.ImageQuad.LeftTop += RightArm.ImagePos;
			RightArm.ImageQuad.RightTop += RightArm.ImagePos;
			RightArm.ImageQuad.LeftBottom += RightArm.ImagePos;
			RightArm.ImageQuad.RightBottom += RightArm.ImagePos;
		}
	}

	if (BossMotionTime >= MOTIONEND) {
		RightArm.MotionPos.x = 9999;
		RightArm.MotionPos.y = 9999;
		if (Attack == false) {
			blade.FPosBoss.x = Pos.x;

		}
		if (Attack == true) {
			if (AttackStartTime <= 0) {
				blade.angle = Easing::easing(blade.t, 0, 200, 0.035f, Easing::easeInBack) * -Direction;

				blade.theta = blade.angle / 180.0f * M_PI;
				if (blade.t == 1) {
					if (blade.t == 1 && blade.t_back == 0) {
						DirectionGet(player);
					}
					blade.angle = Easing::easing(blade.t_back, 200, 0, 0.025f, Easing::easeInOutBack) * -Direction;

					blade.theta = blade.angle / 180.0f * M_PI;
					Pos.x = Easing::easing(blade.Boss_t, blade.FPosBoss.x, blade.FPosBoss.x + (150 * Direction), 0.05, Easing::easeInQuart);
					
					if (blade.t_back == 1) {
						if (BossMotionTime < MOTIONEND + 30) {
							Pos.y = 5000;

						}
						else {
							if (blade.t_back == 1 && blade.t_back2 == 0) {
								DirectionGet(player);
								blade.FPosBoss.x = player.Translation().x + (350 * Direction);
							}

							blade.angle = Easing::easing(blade.t_back2, -20, 200, 0.015f, Easing::easeInOutBack) * -Direction;
							blade.theta = blade.angle / 180.0f * M_PI;
							Pos.x = Easing::easing(blade.Boss_t2, blade.FPosBoss.x, blade.FPosBoss.x + (150 * Direction), 0.05, Easing::easeInQuart);
							if (blade.t_back2 < 0.2) {
								DirectionGet(player);
								Pos.y = Size.y / 2;
							}


						}
						BossMotionTime++;
					}
					
				}
				else {
				}
				Matrix2x2 mat = MakeRotateMatrix(blade.theta);
				//剣の座標最初の
				Vec2 LeftTop = { -30 , 400 };
				Vec2 RightTop = { 30  , 400 };
				Vec2 LeftBottom = { -30 , 50 };
				Vec2 RightBottom = { 30 , 50 };
				blade.Quad_Pos = { blade.LeftTop,blade.RightTop,blade.LeftBottom,blade.RightBottom };


				blade.LeftTop = Multiply(LeftTop, mat);
				blade.RightTop = Multiply(RightTop, mat);
				blade.LeftBottom = Multiply(LeftBottom, mat);
				blade.RightBottom = Multiply(RightBottom, mat);

				blade.LeftTop += Pos;
				blade.RightTop += Pos;
				blade.LeftBottom += Pos;
				blade.RightBottom += Pos;

				blade.Quad_Pos = { blade.LeftTop,blade.RightTop,blade.LeftBottom,blade.RightBottom };



				if (blade.t_back2 == 1) {
					blade.Init();
					Action = false;
					Attack = false;
					SwordAttack = false;
					bNomalSwordAttack = true;
					BossMotionTime = 0;
					RightArm.StandMotionFlag = 1;
					RightArm.MotionPos = { 0,0 };
				}

				BladeImageLink(mat);
			}
			else {
				AttackStartTime--;
			}
		}
	}
	if (BossMotionTime < MOTIONEND) {
		BossMotionTime++;
	}
}
void Boss::NomalRotedSwordAttack(PlayerMain& player) {
	//DirectionGet(player);
	int MOTIONEND1 = 50;
	int MOTIONEND2 = 10;
	int MOTIONEND3 = 30;
	int MOTIONEND4 = 40;
	UseBladeGra = Blade_gra;
	RightArm.StandMotionFlag = 0;
	
	float t = BossMotionTime / MOTIONEND1;
	RightArm.MotionPos.x = 0 * (1.0f - t * t * t * t);


	
	Vec2 LeftTop = { RightArm.ImageSize.x / 2 , -RightArm.ImageSize.y / 2 + 78 };
	Vec2 RightTop = { -RightArm.ImageSize.x / 2 , -RightArm.ImageSize.y / 2 + 78 };
	Vec2 LeftBottom = { RightArm.ImageSize.x / 2 , RightArm.ImageSize.y / 2 + 78 };
	Vec2 RightBottom = { -RightArm.ImageSize.x / 2 , RightArm.ImageSize.y / 2 + 78 };

	float angle = 0;

	if (BossMotionTime <= MOTIONEND1) {
		t = 1 - (BossMotionTime / MOTIONEND1);
		angle = 180 - 100 * (1 - t * t * t) * Direction;
		RightArm.MotionPos.y = 40;
	}
	else if (BossMotionTime <= MOTIONEND1 + MOTIONEND2) {
		t = (BossMotionTime - MOTIONEND1) / MOTIONEND2;
		angle = 80 * Direction + 120 * t * Direction;
		RightArm.MotionPos.y = 40;
	}
	else if (BossMotionTime <= MOTIONEND1 + MOTIONEND2 + MOTIONEND3) {
		t = (BossMotionTime - MOTIONEND1 - MOTIONEND2) / MOTIONEND3;
		angle = 80 * Direction + 120 * Direction + 10 * t;
		//RightArm.StandMotionFlag = 1;
	}
	else if (BossMotionTime <= MOTIONEND1 + MOTIONEND2 + MOTIONEND3 + MOTIONEND4) {
		t = 1 - ((BossMotionTime - MOTIONEND1 - MOTIONEND2 - MOTIONEND3) / MOTIONEND4);
		angle = 180 - 180 * ( 1 - t * t * t) * Direction;

		LeftTop.x *= -1;
		RightTop.x *= -1;
		LeftBottom.x *= -1;
		RightBottom.x *= -1;
	}
	else {
		LeftTop.x *= -1;
		RightTop.x *= -1;
		LeftBottom.x *= -1;
		RightBottom.x *= -1;
	}


	float theta = angle / 180.0f * M_PI;

	Matrix2x2 mat = MakeRotateMatrix(theta);

	

	RightArm.ImageQuad.LeftTop = Multiply(LeftTop, mat);
	RightArm.ImageQuad.RightTop = Multiply(RightTop, mat);
	RightArm.ImageQuad.LeftBottom = Multiply(LeftBottom, mat);
	RightArm.ImageQuad.RightBottom = Multiply(RightBottom, mat);

	RightArm.ImageQuad.LeftTop += RightArm.ImagePos;
	RightArm.ImageQuad.RightTop += RightArm.ImagePos;
	RightArm.ImageQuad.LeftBottom += RightArm.ImagePos;
	RightArm.ImageQuad.RightBottom += RightArm.ImagePos;


	if (BossMotionTime <= MOTIONEND1 + MOTIONEND2) {

	}
	else{
		if (blade.Vec_RotedPos.x == 0) {
			blade.angle = 270 * Direction;
			blade.Vec_RotedPos.y = -100;
		}

		blade.angle += 12 * Direction;

		blade.theta = blade.angle / 180.0f * M_PI;

		if (blade.Roted_t != 1) {
			SwordAttack = true;
			blade.Vec_RotedPos.x = Easing::easing(blade.Roted_t, 0, 600 * Direction, 0.03f, Easing::easeOutCubic);
		}
		else if (blade.Roted_t == 1 && blade.Roted_tback != 1) {

			blade.Vec_RotedPos.x = Easing::easing(blade.Roted_tback, 600 * Direction, 0, 0.02f, Easing::easeInCubic);
		}

		if (blade.Roted_t > 0.8 && blade.Vec_RotedPos.y < 150) {
			blade.Vec_RotedPos.y += 10;
		}

		blade.Vec_RotedPos.y = Clamp::clamp(blade.Vec_RotedPos.y, -100, 150);

		Matrix2x2 mat = MakeRotateMatrix(blade.theta);
		//剣の座標最初の
		Vec2 LeftTop = { -30 , 121 };
		Vec2 RightTop = { 30  , 121 };
		Vec2 LeftBottom = { -30 , -121 };
		Vec2 RightBottom = { 30 , -121 };
		blade.Quad_Pos = { blade.LeftTop,blade.RightTop,blade.LeftBottom,blade.RightBottom };


		blade.LeftTop = Multiply(LeftTop, mat);
		blade.RightTop = Multiply(RightTop, mat);
		blade.LeftBottom = Multiply(LeftBottom, mat);
		blade.RightBottom = Multiply(RightBottom, mat);

		blade.LeftTop += Pos + blade.Vec_RotedPos;
		blade.RightTop += Pos + blade.Vec_RotedPos;
		blade.LeftBottom += Pos + blade.Vec_RotedPos;
		blade.RightBottom += Pos + blade.Vec_RotedPos;


		blade.Quad_Pos = { blade.LeftTop,blade.RightTop,blade.LeftBottom,blade.RightBottom };

		if (blade.Roted_tback == 1) {
			blade.Init();
			Action = false;
			Attack = false;
			SwordAttack = false;
			bNomalRotedSwordAttack = true;
			BossMotionTime = 0;
			RightArm.StandMotionFlag = 1;
			RightArm.MotionPos = { 0,0 };
		}

		BladeImageLink(mat);
	}
	BossMotionTime++;
}
void Boss::NomalRotedSwordAttack2(PlayerMain& player)
{
	int MOTIONEND1 = 50;
	int MOTIONEND2 = 10;
	int MOTIONEND3 = 30;
	int MOTIONEND4 = 40;
	UseBladeGra = Blade_gra;
	RightArm.StandMotionFlag = 0;

	float t = BossMotionTime / MOTIONEND1;
	RightArm.MotionPos.x = 0 * (1.0f - t * t * t * t);



	Vec2 LeftTop = { RightArm.ImageSize.x / 2 , -RightArm.ImageSize.y / 2 + 78 };
	Vec2 RightTop = { -RightArm.ImageSize.x / 2 , -RightArm.ImageSize.y / 2 + 78 };
	Vec2 LeftBottom = { RightArm.ImageSize.x / 2 , RightArm.ImageSize.y / 2 + 78 };
	Vec2 RightBottom = { -RightArm.ImageSize.x / 2 , RightArm.ImageSize.y / 2 + 78 };

	float angle = 0;

	if (BossMotionTime <= MOTIONEND1) {
		t = 1 - (BossMotionTime / MOTIONEND1);
		angle = 180 - 100 * (1 - t * t * t) * Direction;
		RightArm.MotionPos.y = 40;
	}
	else if (BossMotionTime <= MOTIONEND1 + MOTIONEND2) {
		t = (BossMotionTime - MOTIONEND1) / MOTIONEND2;
		angle = 80 * Direction + 120 * t * Direction;
		RightArm.MotionPos.y = 40;
	}
	else {
		angle = 190;
	}


	float theta = angle / 180.0f * M_PI;

	Matrix2x2 mat = MakeRotateMatrix(theta);



	RightArm.ImageQuad.LeftTop = Multiply(LeftTop, mat);
	RightArm.ImageQuad.RightTop = Multiply(RightTop, mat);
	RightArm.ImageQuad.LeftBottom = Multiply(LeftBottom, mat);
	RightArm.ImageQuad.RightBottom = Multiply(RightBottom, mat);

	RightArm.ImageQuad.LeftTop += RightArm.ImagePos;
	RightArm.ImageQuad.RightTop += RightArm.ImagePos;
	RightArm.ImageQuad.LeftBottom += RightArm.ImagePos;
	RightArm.ImageQuad.RightBottom += RightArm.ImagePos;

	if (BossMotionTime <= MOTIONEND1 + MOTIONEND2) {

	}
	else {
		if (blade.Vec_RotedPos.x == 0) {
			blade.angle = 270 * Direction;
		}

		blade.angle += 12 * Direction;

		blade.theta = blade.angle / 180.0f * M_PI;

		if (blade.Roted_t != 1) {
			SwordAttack = true;

			blade.Vec_RotedPos = { Easing::easing(blade.Roted_t, 0, 600 * Direction, 0.03f, Easing::easeOutCubic), -100 };
		}
		else if (blade.Roted_t == 1 && blade.Roted_tback != 1) {

			blade.Vec_RotedPos = { Easing::easing(blade.Roted_tback, 600 * Direction, 0, 0.02f, Easing::easeInCubic), -100 };

		}
		Matrix2x2 mat = MakeRotateMatrix(blade.theta);
		//剣の座標最初の
		Vec2 LeftTop = { -30 , 121 };
		Vec2 RightTop = { 30  , 121 };
		Vec2 LeftBottom = { -30 , -121 };
		Vec2 RightBottom = { 30 , -121 };
		blade.Quad_Pos = { blade.LeftTop,blade.RightTop,blade.LeftBottom,blade.RightBottom };


		blade.LeftTop = Multiply(LeftTop, mat);
		blade.RightTop = Multiply(RightTop, mat);
		blade.LeftBottom = Multiply(LeftBottom, mat);
		blade.RightBottom = Multiply(RightBottom, mat);

		blade.LeftTop += Pos + blade.Vec_RotedPos;
		blade.RightTop += Pos + blade.Vec_RotedPos;
		blade.LeftBottom += Pos + blade.Vec_RotedPos;
		blade.RightBottom += Pos + blade.Vec_RotedPos;

		blade.Quad_Pos = { blade.LeftTop,blade.RightTop,blade.LeftBottom,blade.RightBottom };

		if (blade.Roted_tback == 1) {
			blade.Init();
			Action = false;
			Attack = false;
			SwordAttack = false;
			bNomalRotedSwordAttack = true;
			BossMotionTime = 0;
			RightArm.StandMotionFlag = 1;
			RightArm.MotionPos = { 0,0 };
		}

		BladeImageLink(mat);
	}
	BossMotionTime++;
}
void Boss::JumpAttack(PlayerMain& player,Screen& screen) 
{
	int MOTIONEND1 = 50;
	int MOTIONEND2 = 10;
	int MOTIONEND3 = 5;
	int MOTIONEND4 = 5;
	Head.StandMotionFlag = 0;
	Body.StandMotionFlag = 0;
	RightArm.StandMotionFlag = 0;
	LeftArm.StandMotionFlag = 0;
	Leg.StandMotionFlag = 0;

	float t = 0;
	float angle = 0;
	if (BossMotionTime <= MOTIONEND1) {
		t = 1 - (BossMotionTime / MOTIONEND1);
		Head.MotionPos.y = -80 * (1 - t * t);
		Body.MotionPos.y = -55 * (1 - t * t);
		LeftArm.MotionPos.y = -40 * (1 - t * t);
		RightArm.MotionPos.y = -40 * (1 - t * t);
		Leg.MotionPos.y = -20 * (1 - t * t);
	}
	else {
		if (BossMotionTime - MOTIONEND1 <= MOTIONEND2) {
			t = 1 - (BossMotionTime - MOTIONEND1) / MOTIONEND2;
			Head.MotionPos.y = -80 + 80 * (1 - t * t * t * t);
			Body.MotionPos.y = -55 + 55 * (1 - t * t * t * t);
			LeftArm.MotionPos.y = -40 + 40 * (1 - t * t * t * t);
			RightArm.MotionPos.y = -40 + 40 * (1 - t * t * t * t);
			Leg.MotionPos.y = -20 + 20 * (1 - t * t * t * t);
		}
		if (Attack == false) {
			jumpattack.F_Pos = { Pos };
			jumpattack.PlayerPosF = player.Translation();
			Attack = true;
		}
		else if (Attack == true) {
			if (jumpattack.Matched == false) {
				Pos.x = Easing::easing(jumpattack.EaseT, jumpattack.F_Pos.x, jumpattack.PlayerPosF.x, 0.03f, Easing::easeOutCubic);
				Pos.y = Easing::easing(jumpattack.EaseT2, Size.y / 2, 600, 0.05f, Easing::easeOutCirc);

				if (jumpattack.EaseT == 1) {

					jumpattack.Matched = true;

				}
			}
			else if (jumpattack.Matched == true) {
				Pos.y = Easing::easing(jumpattack.EaseDownT, 600, Size.y / 2, 0.05f, Easing::easeOutBounce);

				if (jumpattack.EaseDownT >= 0.3) {

					if (BossMotionTime - MOTIONEND1 - MOTIONEND2 < MOTIONEND3) {
						t = 1 - (BossMotionTime - MOTIONEND1 - MOTIONEND2) / MOTIONEND3;
						Head.MotionPos.y = -80 * (1 - t * t * t * t);
						Body.MotionPos.y = -55 * (1 - t * t * t * t);
						LeftArm.MotionPos.y = -40 * (1 - t * t * t * t);
						RightArm.MotionPos.y = -40 * (1 - t * t * t * t);
						Leg.MotionPos.y = -20 * (1 - t * t * t * t);
					}
					else if (BossMotionTime - MOTIONEND1 - MOTIONEND2 - MOTIONEND3 < MOTIONEND4) {
						t = 1 - (BossMotionTime - MOTIONEND1 - MOTIONEND2 - MOTIONEND3) / MOTIONEND4;
						Head.MotionPos.y = -80 + 80 * (1 - t);
						Body.MotionPos.y = -55 + 55 * (1 - t);
						LeftArm.MotionPos.y = -40 + 40 * (1 - t);
						RightArm.MotionPos.y = -40 + 40 * (1 - t);
						Leg.MotionPos.y = -20 + 20 * (1 - t);
					}
					BossMotionTime++;
				}
			}

			screen.Shake(0, 0, -10, 10, jumpattack.EaseDownT <= 0.9f && jumpattack.EaseDownT >= 0.8f);

			if (jumpattack.EaseDownT == 1.0f && BossMotionTime > 100) {
				blade.Init();
				jumpattack.Init();
				Attack = false;
				Action = false;
				BossMotionTime = 0;
				Head.StandMotionFlag = 1;
				Body.StandMotionFlag = 1;
				RightArm.StandMotionFlag = 1;
				LeftArm.StandMotionFlag = 1;
			}
		}
	}
	if (BossMotionTime < MOTIONEND1 + MOTIONEND2) {
		BossMotionTime++;
	}
}

void Boss::ShockWaveAttack(PlayerMain& player, Screen& screen)
{
	int MOTIONEND1 = 50;
	int MOTIONEND2 = 10;
	int MOTIONEND3 = 10;
	int MOTIONEND4 = 10;
	Head.StandMotionFlag = 0;
	Body.StandMotionFlag = 0;
	RightArm.StandMotionFlag = 0;
	LeftArm.StandMotionFlag = 0;
	Leg.StandMotionFlag = 0;

	float t = 0;
	float angle = 0;
	if (BossMotionTime <= MOTIONEND1) {
		t = 1 - (BossMotionTime / MOTIONEND1);
		Head.MotionPos.y = -80 * (1 - t * t);
		Body.MotionPos.y = -55 * (1 - t * t);
		LeftArm.MotionPos.y = -40 * (1 - t * t);
		RightArm.MotionPos.y = -40 * (1 - t * t);
		Leg.MotionPos.y = -20 * (1 - t * t);
	}
	else {
		if (BossMotionTime - MOTIONEND1 <= MOTIONEND2) {
			t = 1 - (BossMotionTime - MOTIONEND1) / MOTIONEND2;
			Head.MotionPos.y = -80 + 80 * (1 - t * t * t * t);
			Body.MotionPos.y = -55 + 55 * (1 - t * t * t * t);
			LeftArm.MotionPos.y = -40 + 40 * (1 - t * t * t * t);
			RightArm.MotionPos.y = -40 + 40 * (1 - t * t * t * t);
			Leg.MotionPos.y = -20 + 20 * (1 - t * t * t * t);
		}

		if (Attack == false) {
			jumpattack.F_Pos = { Pos };
			jumpattack.PlayerPosF = player.Translation();
			Attack = true;
		}
		else if (Attack == true) {
			if (jumpattack.Matched == false) {
				Pos.x = Easing::easing(jumpattack.EaseT, jumpattack.F_Pos.x, jumpattack.PlayerPosF.x, 0.02f, Easing::easeOutCubic);
				Pos.y = Easing::easing(jumpattack.EaseT2, Size.y / 2, 600, 0.05f, Easing::easeOutCirc);

				if (jumpattack.EaseT == 1) {

					jumpattack.Matched = true;
					//上に上がり切った
				}
			}
			else if (jumpattack.Matched == true) {
				Pos.y = Easing::easing(jumpattack.EaseDownT, 600, Size.y / 2, 0.05f, Easing::easeOutBounce);
				//下に落ちる
				if (Pos.y == Size.y / 2) {
					Wave[0].WaveKeep = true;
				}

				if (jumpattack.EaseDownT >= 0.3) {
					
					if (BossMotionTime - MOTIONEND1 - MOTIONEND2 < MOTIONEND3) {
						t = 1 - (BossMotionTime - MOTIONEND1 - MOTIONEND2 ) / MOTIONEND3;
						Head.MotionPos.y = -80 * (1 - t * t * t * t);
						Body.MotionPos.y = -55 * (1 - t * t * t * t);
						LeftArm.MotionPos.y = -40 * (1 - t * t * t * t);
						RightArm.MotionPos.y = -40 * (1 - t * t * t * t);
						Leg.MotionPos.y = -20 * (1 - t * t * t * t);
					}
					else if (BossMotionTime - MOTIONEND1 - MOTIONEND2 -MOTIONEND3 < MOTIONEND4) {
						t = 1 - (BossMotionTime - MOTIONEND1 - MOTIONEND2 - MOTIONEND3) / MOTIONEND4;
						Head.MotionPos.y = -80 + 80 * (1 - t );
						Body.MotionPos.y = -55 + 55 * (1 - t );
						LeftArm.MotionPos.y = -40 + 40 * (1 - t );
						RightArm.MotionPos.y = -40 + 40 * (1 - t );
						Leg.MotionPos.y = -20 + 20 * (1 - t );
					}
					BossMotionTime++;
				}
			}

			screen.Shake(0, 0, -10, 10, jumpattack.EaseDownT <= 0.9f && jumpattack.EaseDownT >= 0.8f);

			if (jumpattack.EaseDownT == 1.0f && BossMotionTime > 110) {
				blade.Init();
				jumpattack.Init();
				Attack = false;
				Action = false;
				bShockWaveAttack = true;
				CoolTime = 180;
				BossMotionTime = 0;
				Head.StandMotionFlag = 1;
				Body.StandMotionFlag = 1;
				RightArm.StandMotionFlag = 1;
				LeftArm.StandMotionFlag = 1;
			}
		}
	}
	if (BossMotionTime < MOTIONEND1 + MOTIONEND2) {
		BossMotionTime++;
	}
}
void Boss::ShockWaveAttack2(PlayerMain& player, Screen& screen)
{
	int MOTIONEND1 = 50;
	int MOTIONEND2 = 10;
	int MOTIONEND3 = 10;
	int MOTIONEND4 = 10;
	Head.StandMotionFlag = 0;
	Body.StandMotionFlag = 0;
	RightArm.StandMotionFlag = 0;
	LeftArm.StandMotionFlag = 0;
	Leg.StandMotionFlag = 0;

	float t = 0;
	float angle = 0;
	if (BossMotionTime <= MOTIONEND1) {
		t = 1 - (BossMotionTime / MOTIONEND1);
		Head.MotionPos.y = -80 * (1 - t * t);
		Body.MotionPos.y = -55 * (1 - t * t);
		LeftArm.MotionPos.y = -40 * (1 - t * t);
		RightArm.MotionPos.y = -40 * (1 - t * t);
		Leg.MotionPos.y = -20 * (1 - t * t);
	}
	else {
		if (BossMotionTime - MOTIONEND1 <= MOTIONEND2) {
			t = 1 - (BossMotionTime - MOTIONEND1) / MOTIONEND2;
			Head.MotionPos.y = -80 + 80 * (1 - t * t * t * t);
			Body.MotionPos.y = -55 + 55 * (1 - t * t * t * t);
			LeftArm.MotionPos.y = -40 + 40 * (1 - t * t * t * t);
			RightArm.MotionPos.y = -40 + 40 * (1 - t * t * t * t);
			Leg.MotionPos.y = -20 + 20 * (1 - t * t * t * t);
		}
		if (Attack == false) {
			jumpattack.F_Pos = { Pos };
			jumpattack.PlayerPosF = player.Translation();
			Attack = true;
		}
		else if (Attack == true) {
			if (jumpattack.Matched == false) {
				Pos.x = Easing::easing(jumpattack.EaseT, jumpattack.F_Pos.x, jumpattack.PlayerPosF.x, 0.03f, Easing::easeOutCubic);
				Pos.y = Easing::easing(jumpattack.EaseT2, Size.y / 2, 600, 0.05f, Easing::easeOutCirc);

				if (jumpattack.EaseT == 1) {
					jumpattack.Matched = true;
					//jumpattack.PlayerPosF = player.Translation();
					jumpattack.EaseT = 0;
					jumpattack.EaseT2 = 0;
					//上に上がり切った
				}
			}
			else
				if (jumpattack.Matched == true) {

					Pos.y = Easing::easing(jumpattack.EaseDownT, 600, Size.y / 2, 0.05f, Easing::easeOutBounce);
					if (jumpattack.EaseDownT < 0.1)	jumpattack.PlayerPosF2.x = player.Translation().x;

					if (jumpattack.EaseDownT == 1 && jumpattack.Matched2 == false) {
						jumpattack.Matched2 = true;
						//下に落ちる
						if (Pos.y == Size.y / 2) {
							Wave[0].WaveKeep = true;

						}
						jumpattack.EaseDownT = 0;

					}
					if (jumpattack.Matched2 == true) {
						Pos.y = Easing::easing(jumpattack.EaseT2, Size.y / 2, 600, 0.03f, Easing::easeOutCirc);

						//Pos.x = jumpattack.PlayerPosF2.x + (Direction * 200);

						

						if (jumpattack.EaseT2 == 1) {
							Pos.y = Easing::easing(jumpattack.EaseDownT2, 600, Size.y / 2, 0.05f, Easing::easeOutBounce);
							if (Pos.y == Size.y / 2 && jumpattack.EaseDownT2 == 1) {
								Wave[1].WaveKeep = true;

							}

							if (jumpattack.EaseDownT2 >= 0.3) {

								if (BossMotionTime - MOTIONEND1 - MOTIONEND2 < MOTIONEND3) {
									t = 1 - (BossMotionTime - MOTIONEND1 - MOTIONEND2) / MOTIONEND3;
									Head.MotionPos.y = -80 * (1 - t * t * t * t);
									Body.MotionPos.y = -55 * (1 - t * t * t * t);
									LeftArm.MotionPos.y = -40 * (1 - t * t * t * t);
									RightArm.MotionPos.y = -40 * (1 - t * t * t * t);
									Leg.MotionPos.y = -20 * (1 - t * t * t * t);
								}
								else if (BossMotionTime - MOTIONEND1 - MOTIONEND2 - MOTIONEND3 < MOTIONEND4) {
									t = 1 - (BossMotionTime - MOTIONEND1 - MOTIONEND2 - MOTIONEND3) / MOTIONEND4;
									Head.MotionPos.y = -80 + 80 * (1 - t);
									Body.MotionPos.y = -55 + 55 * (1 - t);
									LeftArm.MotionPos.y = -40 + 40 * (1 - t);
									RightArm.MotionPos.y = -40 + 40 * (1 - t);
									Leg.MotionPos.y = -20 + 20 * (1 - t);
								}
								BossMotionTime++;
							}
						}
					}

				}

			screen.Shake(0, 0, -10, 10, jumpattack.EaseDownT <= 0.9f && jumpattack.EaseDownT >= 0.8f);

			if (jumpattack.EaseDownT2 == 1.0f && jumpattack.Matched2 == true && BossMotionTime > 110) {
				blade.Init();
				jumpattack.Init();
				Attack = false;
				Action = false;
				bShockWaveAttack = true;
				CoolTime = 180;
				BossMotionTime = 0;
				Head.StandMotionFlag = 1;
				Body.StandMotionFlag = 1;
				RightArm.StandMotionFlag = 1;
				LeftArm.StandMotionFlag = 1;
			}
		}
	}
	if (BossMotionTime < MOTIONEND1 + MOTIONEND2) {
		BossMotionTime++;
	}
}

void Boss::ShockWaveAttackCenter(PlayerMain& player)
{
	int MOTIONEND1 = 50;
	int MOTIONEND2 = 10;
	int MOTIONEND3 = 10;
	int MOTIONEND4 = 10;
	Head.StandMotionFlag = 0;
	Body.StandMotionFlag = 0;
	RightArm.StandMotionFlag = 0;
	LeftArm.StandMotionFlag = 0;
	Leg.StandMotionFlag = 0;

	float t = 0;
	float angle = 0;
	if (BossMotionTime <= MOTIONEND1) {
		t = 1 - (BossMotionTime / MOTIONEND1);
		Head.MotionPos.y = -80 * (1 - t * t);
		Body.MotionPos.y = -55 * (1 - t * t);
		LeftArm.MotionPos.y = -40 * (1 - t * t);
		RightArm.MotionPos.y = -40 * (1 - t * t);
		Leg.MotionPos.y = -20 * (1 - t * t);
	}
	else {
		if (BossMotionTime - MOTIONEND1 <= MOTIONEND2) {
			t = 1 - (BossMotionTime - MOTIONEND1) / MOTIONEND2;
			Head.MotionPos.y = -80 + 80 * (1 - t * t * t * t);
			Body.MotionPos.y = -55 + 55 * (1 - t * t * t * t);
			LeftArm.MotionPos.y = -40 + 40 * (1 - t * t * t * t);
			RightArm.MotionPos.y = -40 + 40 * (1 - t * t * t * t);
			Leg.MotionPos.y = -20 + 20 * (1 - t * t * t * t);
		}

		if (Attack == false) {
			jumpattack.F_Pos = { Pos };
			jumpattack.PlayerPosF.x = (2400)/2;
			Attack = true;
		}
		else if (Attack == true) {
			if (jumpattack.Matched == false) {
				Pos.x = Easing::easing(jumpattack.EaseT, jumpattack.F_Pos.x, jumpattack.PlayerPosF.x, 0.02f, Easing::easeOutCubic);
				Pos.y = Easing::easing(jumpattack.EaseT2, Size.y / 2, 600, 0.05f, Easing::easeOutCirc);

				

				if (jumpattack.EaseT == 1) {

					jumpattack.Matched = true;
					//上に上がり切った
				}
			}
			else if (jumpattack.Matched == true) {
				Pos.y = Easing::easing(jumpattack.EaseDownT, 600, Size.y / 2, 0.05f, Easing::easeOutBounce);
				//下に落ちる
				if (Pos.y == Size.y / 2) {
					Wave[0].WaveKeep = true;
				}

				if (jumpattack.EaseDownT >= 0.3) {

					if (BossMotionTime - MOTIONEND1 - MOTIONEND2 < MOTIONEND3) {
						t = 1 - (BossMotionTime - MOTIONEND1 - MOTIONEND2) / MOTIONEND3;
						Head.MotionPos.y = -80 * (1 - t * t * t * t);
						Body.MotionPos.y = -55 * (1 - t * t * t * t);
						LeftArm.MotionPos.y = -40 * (1 - t * t * t * t);
						RightArm.MotionPos.y = -40 * (1 - t * t * t * t);
						Leg.MotionPos.y = -20 * (1 - t * t * t * t);
					}
					else if (BossMotionTime - MOTIONEND1 - MOTIONEND2 - MOTIONEND3 < MOTIONEND4) {
						t = 1 - (BossMotionTime - MOTIONEND1 - MOTIONEND2 - MOTIONEND3) / MOTIONEND4;
						Head.MotionPos.y = -80 + 80 * (1 - t);
						Body.MotionPos.y = -55 + 55 * (1 - t);
						LeftArm.MotionPos.y = -40 + 40 * (1 - t);
						RightArm.MotionPos.y = -40 + 40 * (1 - t);
						Leg.MotionPos.y = -20 + 20 * (1 - t);
					}
					BossMotionTime++;
				}
			}

			//screen.Shake(0, 0, -10, 10, jumpattack.EaseDownT <= 0.9f && jumpattack.EaseDownT >= 0.8f);

			if (jumpattack.EaseDownT == 1.0f && BossMotionTime > 110) {
				blade.Init();
				jumpattack.Init();
				Attack = false;
				Action = false;
				bShockWaveAttack = true;
				CoolTime = 35;
				BossMotionTime = 0;
				Head.StandMotionFlag = 1;
				Body.StandMotionFlag = 1;
				RightArm.StandMotionFlag = 1;
				LeftArm.StandMotionFlag = 1;
			}
		}
	}
	if (BossMotionTime < MOTIONEND1 + MOTIONEND2) {
		BossMotionTime++;
	}
}

void Boss::CircleOfDeathAttack(PlayerMain& player)
{
	if (CircleOfDeathMotionT2 == 0) {
		CircleOfDeathMotion(0);
	}

	if (Circleofdeath_Expflame >= 40) {
		CircleOfDeathMotion(1);
	}

	if (CircleOfDeathMotionT > 0.3) {
		Circleofdeath_flame++;
		for (int i = 0; i < kMAX_CIR; i++) {
			if (Circleofdeath_flame % 13 == 0 && Circleofdeath[i].Set == false && Circleofdeath[kMAX_CIR - 1].Set == false) {
				if (i == 0) {
					Circleofdeath[i].circle.pos = { player.GetPlayerQuad().LeftTop.x, player.GetPlayerQuad().LeftTop.y };

				}
				else
					if (i % 2 == 0) {
						Circleofdeath[i].circle.pos = { Pos.x + (i * 150),Pos.y + Randam::RAND(-100,100) };

					}
					else if (i % 2 == 1) {
						Circleofdeath[i].circle.pos = { Pos.x + (-i * 150),Pos.y + Randam::RAND(-100,100) };

					}

				Circleofdeath[i].fRad = 100;
				Circleofdeath[i].Quad_Pos.Quad::Quad(Circleofdeath[i].circle.pos, Circleofdeath[i].fRad * 2, Circleofdeath[i].fRad * 2, 0);

				Circleofdeath[i].Set = true;
				break;
			}
			if (/*Circleofdeath[i].Set == true*/Circleofdeath[kMAX_CIR - 1].Set == true && CircleOfDeathMotionT == 1 && Circleofdeath_Expflame >= 45) {

				

				if (CircleOfDeathMotionT2 >= 1 ) {
					//Circleofdeath[i].Reserve = false;
					Circleofdeath[i].circle.radius = Easing::easing(Circleofdeath[i].Reserve_t, 0, Circleofdeath[i].fRad, 0.01f, Easing::easeOutExpo);
					Circleofdeath[i].Quad_Pos.Quad::Quad(Circleofdeath[i].circle.pos, Circleofdeath[i].fRad * 2 + Circleofdeath[i].circle.radius, Circleofdeath[i].fRad * 2 + Circleofdeath[i].circle.radius, 0);

					if (Circleofdeath[i].Reserve_t == 1.0f) {
						//Circleofdeath[i].Init();

					}
				}
			}
		}
		for (int i = 0; i < kMAX_CIR; i++) {

			if (Circleofdeath[kMAX_CIR - 1].Reserve_t == 1) {
				Action = false;
				Circleofdeath_flame = 0;
				Circleofdeath_Expflame = 0;
				Circleofdeath[i].Init();
				CoolTime = 80;
				CircleOfDeathMotion(2);
			}
		}
		if (Circleofdeath[kMAX_CIR - 1].Set == true) {
			Circleofdeath_Expflame++;
		}
	}
}



void Boss::RainOfSwordAttack() {

	if (RainofswordMotionT2 == 0) {
		RainOfSwordMotion(0);
	}
	if (Rainofsword[kMAX_RAINSWORD - 1].DownT >= 0.23) {
		RainOfSwordMotion(1);
	}
	Rainofsword_flame++;
	for (int i = 0; i < kMAX_RAINSWORD; i++) {
		if (Rainofsword_flame % 4 == 0 && Rainofsword[i].Set == false) {
			Rainofsword[i].Pos.x = Pos.x+Randam::RAND(-800, 800);
			Rainofsword[i].Pos.y = 800;
			Rainofsword[i].Set = true;
			break;

		}
		if(Rainofsword[i].Set == true&& Rainofsword[i].Reserve == false){

			Rainofsword[i].Width = Easing::easing(Rainofsword[i].AddT, 1, 50, 0.03, Easing::easeInQuint);
			Rainofsword[i].Height = Easing::easing(Rainofsword[i].AddT2,1,100,0.03,Easing::easeInQuint);
			Rainofsword[i].ColWidth = Easing::easing(Rainofsword[i].ColAddT, 1, 10, 0.03, Easing::easeInQuint);
			Rainofsword[i].ColHeight = Easing::easing(Rainofsword[i].ColAddT2, 1, 93, 0.03, Easing::easeInQuint);

			Rainofsword[i].QuadPos = Quad::Quad(Rainofsword[i].Pos, Rainofsword[i].Width, Rainofsword[i].Height);
			Rainofsword[i].ColQuadPos = Quad::Quad(
				{ Rainofsword[i].Pos.x + Rainofsword[i].Width / 2 - Rainofsword[i].ColWidth / 2 , Rainofsword[i].Pos.y - Rainofsword[i].Height / 2 + Rainofsword[i].ColHeight / 2},
				Rainofsword[i].ColWidth, Rainofsword[i].ColHeight);

			if (Rainofsword[i].AddT == 1) {
				Rainofsword[i].Reserve = true;
			}
		}
		if (Rainofsword[kMAX_RAINSWORD-1].Reserve==true && RainofswordMotionT == 1) {
			Rainofsword[i].Pos.y = Easing::easing(Rainofsword[i].DownT, 800, 0, 0.02f, Easing::easeInBack);
			Rainofsword[i].QuadPos = Quad::Quad(Rainofsword[i].Pos, Rainofsword[i].Width, Rainofsword[i].Height);
			Rainofsword[i].ColQuadPos = Quad::Quad(
				{ Rainofsword[i].Pos.x + Rainofsword[i].Width / 2 - Rainofsword[i].ColWidth / 2 , Rainofsword[i].Pos.y - Rainofsword[i].Height / 2 + Rainofsword[i].ColHeight / 2},
				Rainofsword[i].ColWidth, Rainofsword[i].ColHeight);
		}

	}
	for (int i = 0; i < kMAX_RAINSWORD; i++) {
		if (Rainofsword[kMAX_RAINSWORD - 1].DownT == 1) {
			Rainofsword[i].Init();
			Rainofsword_flame = 0;
			Action = false;
			CoolTime = 80;
			RainOfSwordMotion(2);
		}
	}
}

void Boss::KeepWaveAttack()
{
	for (int i = 0; i < kMAX_WAVE; i++) {
		if (Wave[i].WaveKeep == false) {
			Wave[i].QuadPos.Quad::Quad({99999,9999}, 100, 150);
			Wave[i].Quad2Pos.Quad::Quad({9000,9999}, 100, 150);

		}
		if (Wave[i].WaveKeep == true) {
			if (Wave[i].LifeTime == 0) {
				Wave[i].QuadPos.Quad::Quad({ Pos.x - 50,150 }, 100, 150);
				Wave[i].Quad2Pos.Quad::Quad({ Pos.x - 50,150 }, 100, 150);
			}
			Wave[i].QuadPos.LeftTop.x += 20;
			Wave[i].Quad2Pos.LeftTop.x -= 20;
			Wave[i].QuadPos.Quad::Quad(Wave[i].QuadPos.LeftTop, 100, 150);
			Wave[i].Quad2Pos.Quad::Quad(Wave[i].Quad2Pos.LeftTop, 100, 150);

			Wave[i].LifeTime += 0.025f;
			Wave[i].LifeTime = Clamp::clamp(Wave[i].LifeTime, 0, 1);

			if (Wave[i].LifeTime == 1.0f) {
				Wave[i].WaveKeep = false;
				Wave[i].LifeTime = 0;
			}
		}
	}
}



Quad Boss::GetBossQuad(int BossParts)
{
	switch (BossParts)
	{
	case head:
		return Quad(Head.ColQuad);
		break;
	case body:
		return Quad(Body.ColQuad);
		break;
	case leg:
		return Quad(Leg.ColQuad);
		break;
	case rightarm:
		return Quad(RightArm.ColQuad);
		break;
	case leftarm:
		return Quad(LeftArm.ColQuad);
		break;
	}
	
}

Quad Boss::GetShockWave()
{
	for (int i = 0; i < kMAX_WAVE; i++) {

		return Quad(Wave[i].QuadPos);
	}
}

Quad Boss::GetShockWave2()
{
	for (int i = 0; i < kMAX_WAVE; i++) {

		return Quad(Wave[i].Quad2Pos);
	}
}

int Boss::GetBossHP()
{
	return HP;
}

Quad Boss::GetBossAttackQuad()
{
	return Quad(blade.Quad_Pos);
}

Quad Boss::GetBossBladeQuad()
{
	return Quad(blade.Quad_Pos);
}

Quad Boss::GetRainOfSwordQuad(int i)
{
	return Quad(Rainofsword[i].ColQuadPos);
}

Circle Boss::GetCircleOfDeathQuad(int i)
{
	return Circle(Circleofdeath[i].circle);
}

bool Boss::GetAction()
{
	if (Action == true) {
		return true;
	}
	else {

	return false;
	}
}

bool Boss::GetSwordAttack()
{
	if (SwordAttack == true) {
		return true;
	}
	else {
		return false;

	}
}

void Boss::BossHit(bool Hit)
{
	isBossHit = false;
	if (Hit == true) {
		isBossHit = true;

	}
}
void Boss::BossHitReaction(Quad PlayerQuad, bool up, bool down, bool right)
{
	Vec2 ReactionPuls = { 0 , 0 };
	int minus = 3;

	if (up == true) {
		ReactionPuls = { 0 , 30 };
	}
	else if (down == true) {
		ReactionPuls = { 0 , -30 };
	}
	else {
		if (right == true) {
			ReactionPuls = { 30 , 0 };
		}
		else {
			ReactionPuls = { -30 , 0 };
		}
	}

	if (Collision::QuadToQuad(PlayerQuad, Head.ColQuad)) {
		Head.HitReaction = ReactionPuls;
	}
	if (Collision::QuadToQuad(PlayerQuad, Body.ColQuad)) {
		Body.HitReaction = ReactionPuls;
	}
	if (Collision::QuadToQuad(PlayerQuad, Leg.ColQuad)) {
		Leg.HitReaction = ReactionPuls;
	}
	if (Collision::QuadToQuad(PlayerQuad, LeftArm.ColQuad)) {
		LeftArm.HitReaction = ReactionPuls;
	}
	if (Collision::QuadToQuad(PlayerQuad, RightArm.ColQuad)) {
		RightArm.HitReaction = ReactionPuls;
	}

	if (Head.HitReaction.x > 0) {
		Head.HitReaction.x -= minus;
	}
	if (Head.HitReaction.x < 0) {
		Head.HitReaction.x += minus;
	}
	if (Head.HitReaction.y > 0) {
		Head.HitReaction.y -= minus;
	}
	if (Head.HitReaction.y < 0) {
		Head.HitReaction.y += minus;
	}

	if (Body.HitReaction.x > 0) {
		Body.HitReaction.x -= minus;
	}
	if (Body.HitReaction.x < 0) {
		Body.HitReaction.x += minus;
	}
	if (Body.HitReaction.y > 0) {
		Body.HitReaction.y -= minus;
	}
	if (Body.HitReaction.y < 0) {
		Body.HitReaction.y += minus;
	}

	if (Leg.HitReaction.x > 0) {
		Leg.HitReaction.x -= minus;
	}
	if (Leg.HitReaction.x < 0) {
		Leg.HitReaction.x += minus;
	}
	if (Leg.HitReaction.y > 0) {
		Leg.HitReaction.y -= minus;
	}
	if (Leg.HitReaction.y < 0) {
		Leg.HitReaction.y += minus;
	}

	if (LeftArm.HitReaction.x > 0) {
		LeftArm.HitReaction.x -= minus;
	}
	if (LeftArm.HitReaction.x < 0) {
		LeftArm.HitReaction.x += minus;
	}
	if (LeftArm.HitReaction.y > 0) {
		LeftArm.HitReaction.y -= minus;
	}
	if (LeftArm.HitReaction.y < 0) {
		LeftArm.HitReaction.y += minus;
	}

	if (RightArm.HitReaction.x > 0) {
		RightArm.HitReaction.x -= minus;
	}
	if (RightArm.HitReaction.x < 0) {
		RightArm.HitReaction.x += minus;
	}
	if (RightArm.HitReaction.y > 0) {
		RightArm.HitReaction.y -= minus;
	}
	if (RightArm.HitReaction.y < 0) {
		RightArm.HitReaction.y += minus;
	}



}
void Boss::BladeImageLink(Matrix2x2 mat)
{
	Vec2 MostLeftTop = blade.Quad_Pos.LeftTop;
	Vec2 MostRightBottom = blade.Quad_Pos.RightBottom;

	if (MostLeftTop.x > blade.Quad_Pos.RightTop.x) {
		MostLeftTop.x = blade.Quad_Pos.RightTop.x;
	}
	if (MostLeftTop.x > blade.Quad_Pos.LeftBottom.x) {
		MostLeftTop.x = blade.Quad_Pos.LeftBottom.x;
	}
	if (MostLeftTop.x > blade.Quad_Pos.RightBottom.x) {
		MostLeftTop.x = blade.Quad_Pos.RightBottom.x;
	}

	if (MostLeftTop.y < blade.Quad_Pos.RightTop.y) {
		MostLeftTop.y = blade.Quad_Pos.RightTop.y;
	}
	if (MostLeftTop.y < blade.Quad_Pos.LeftBottom.y) {
		MostLeftTop.y = blade.Quad_Pos.LeftBottom.y;
	}
	if (MostLeftTop.y < blade.Quad_Pos.RightBottom.y) {
		MostLeftTop.y = blade.Quad_Pos.RightBottom.y;
	}

	if (MostRightBottom.x < blade.Quad_Pos.RightTop.x) {
		MostRightBottom.x = blade.Quad_Pos.RightTop.x;
	}
	if (MostRightBottom.x < blade.Quad_Pos.LeftBottom.x) {
		MostRightBottom.x = blade.Quad_Pos.LeftBottom.x;
	}
	if (MostRightBottom.x < blade.Quad_Pos.LeftTop.x) {
		MostRightBottom.x = blade.Quad_Pos.LeftTop.x;
	}

	if (MostRightBottom.y > blade.Quad_Pos.RightTop.y) {
		MostRightBottom.y = blade.Quad_Pos.RightTop.y;
	}
	if (MostRightBottom.y > blade.Quad_Pos.LeftBottom.y) {
		MostRightBottom.y = blade.Quad_Pos.LeftBottom.y;
	}
	if (MostRightBottom.y > blade.Quad_Pos.LeftTop.y) {
		MostRightBottom.y = blade.Quad_Pos.LeftTop.y;
	}

	BladeCenterPos = {
		MostLeftTop.x + (MostRightBottom.x - MostLeftTop.x) / 2,
		MostRightBottom.y + (MostLeftTop.y - MostRightBottom.y) / 2 };

	Vec2 ImageLeftTop = { -BladeImageSize.x * -Direction/ 2,BladeImageSize.y / 2 + 100 };
	Vec2 ImageRightTop = { BladeImageSize.x * -Direction / 2,BladeImageSize.y / 2 + 100 };
	Vec2 ImageLeftBottom = { -BladeImageSize.x * -Direction / 2,-BladeImageSize.y / 2 - HoldPlusY + 100 };
	Vec2 ImageRightBottom = { BladeImageSize.x * -Direction / 2,-BladeImageSize.y / 2 - HoldPlusY + 100};

	if (UseBladeGra == Blade_gra) {
		ImageLeftTop = { -BladeImageSize.x * -Direction / 2,BladeImageSize.y / 2 };
		ImageRightTop = { BladeImageSize.x * -Direction / 2,BladeImageSize.y / 2 };
		ImageLeftBottom = { -BladeImageSize.x * -Direction / 2,-BladeImageSize.y / 2 };
		ImageRightBottom = { BladeImageSize.x * -Direction / 2,-BladeImageSize.y / 2 };
	}

	BladeImageQuad.LeftTop = Multiply(ImageLeftTop, mat);
	BladeImageQuad.RightTop = Multiply(ImageRightTop, mat);
	BladeImageQuad.LeftBottom = Multiply(ImageLeftBottom, mat);
	BladeImageQuad.RightBottom = Multiply(ImageRightBottom, mat);

	BladeImageQuad.LeftTop += BladeCenterPos;
	BladeImageQuad.RightTop += BladeCenterPos;
	BladeImageQuad.LeftBottom += BladeCenterPos;
	BladeImageQuad.RightBottom += BladeCenterPos;

	BladeImageQuad = { BladeImageQuad.LeftTop,BladeImageQuad.RightTop,BladeImageQuad.LeftBottom,BladeImageQuad.RightBottom };
}

void Boss::CircleOfDeathMotion(int type) {

	if (type == 0) {
		RightArm.StandMotionFlag = 0;
		LeftArm.StandMotionFlag = 0;
		Head.StandMotionFlag = 0;
		Body.StandMotionFlag = 0;

		Easing::easing(CircleOfDeathMotionT, 0, 90, 1.0f / 60, Easing::easeOutQuart);

		RightArm.MotionPos.x = 90.0f * CircleOfDeathMotionT + 16 * Direction;
		LeftArm.MotionPos.x = -90.0f * CircleOfDeathMotionT + 16 * Direction;
		RightArm.MotionPos.y = 70.0f * CircleOfDeathMotionT;
		LeftArm.MotionPos.y = 70.0f * CircleOfDeathMotionT;
		Head.MotionPos.x = 10.0f * CircleOfDeathMotionT * Direction;
		Head.MotionPos.y = -30.0f * CircleOfDeathMotionT;
		Body.MotionPos.y = -20.0f * CircleOfDeathMotionT;

		int angle = -180 + 150 * CircleOfDeathMotionT;

		float theta = angle / 180.0f * M_PI;

		Matrix2x2 mat = MakeRotateMatrix(theta);

		Vec2 LeftTop = { -RightArm.ImageSize.x / 2 , -RightArm.ImageSize.y / 2 };
		Vec2 RightTop = { RightArm.ImageSize.x / 2 , -RightArm.ImageSize.y / 2 };
		Vec2 LeftBottom = { -RightArm.ImageSize.x / 2 , RightArm.ImageSize.y / 2 };
		Vec2 RightBottom = { RightArm.ImageSize.x / 2 , RightArm.ImageSize.y / 2 };

		RightArm.ImageQuad.LeftTop = Multiply(LeftTop, mat);
		RightArm.ImageQuad.RightTop = Multiply(RightTop, mat);
		RightArm.ImageQuad.LeftBottom = Multiply(LeftBottom, mat);
		RightArm.ImageQuad.RightBottom = Multiply(RightBottom, mat);

		RightArm.ImageQuad.LeftTop += RightArm.ImagePos;
		RightArm.ImageQuad.RightTop += RightArm.ImagePos;
		RightArm.ImageQuad.LeftBottom += RightArm.ImagePos;
		RightArm.ImageQuad.RightBottom += RightArm.ImagePos;

		theta = -angle / 180.0f * M_PI;

		mat = MakeRotateMatrix(theta);

		LeftTop = { -LeftArm.ImageSize.x / 2 , -LeftArm.ImageSize.y / 2 };
		RightTop = { LeftArm.ImageSize.x / 2 , -LeftArm.ImageSize.y / 2 };
		LeftBottom = { -LeftArm.ImageSize.x / 2 , LeftArm.ImageSize.y / 2 };
		RightBottom = { LeftArm.ImageSize.x / 2 , LeftArm.ImageSize.y / 2 };

		LeftArm.ImageQuad.LeftTop = Multiply(LeftTop, mat);
		LeftArm.ImageQuad.RightTop = Multiply(RightTop, mat);
		LeftArm.ImageQuad.LeftBottom = Multiply(LeftBottom, mat);
		LeftArm.ImageQuad.RightBottom = Multiply(RightBottom, mat);

		LeftArm.ImageQuad.LeftTop += LeftArm.ImagePos;
		LeftArm.ImageQuad.RightTop += LeftArm.ImagePos;
		LeftArm.ImageQuad.LeftBottom += LeftArm.ImagePos;
		LeftArm.ImageQuad.RightBottom += LeftArm.ImagePos;
	}
	else if (type == 1) {

		Easing::easing(CircleOfDeathMotionT2, 0, 1.0f, 1.0f / 5, Easing::easeInOutBack);
		RightArm.MotionPos.x = 90.0f - 160.0f * CircleOfDeathMotionT2 + 16 * Direction;
		LeftArm.MotionPos.x = -90.0f + 160.0f * CircleOfDeathMotionT2 + 16 * Direction;
		RightArm.MotionPos.y = 110.0f * CircleOfDeathMotionT2;
		LeftArm.MotionPos.y = 110.0f * CircleOfDeathMotionT2;
		Head.MotionPos.x = 10.0f * Direction - 15.0f * CircleOfDeathMotionT * Direction;
		Head.MotionPos.y = -30.0f + 40.0f * CircleOfDeathMotionT;
		Body.MotionPos.y = -20.0f + 25.0f * CircleOfDeathMotionT;

		int angle = -30 - 260.0f * CircleOfDeathMotionT2;

		float theta = angle / 180.0f * M_PI;

		Matrix2x2 mat = MakeRotateMatrix(theta);

		Vec2 LeftTop = { RightArm.ImageSize.x / 2 , -RightArm.ImageSize.y / 2 };
		Vec2 RightTop = { -RightArm.ImageSize.x / 2 , -RightArm.ImageSize.y / 2 };
		Vec2 LeftBottom = { RightArm.ImageSize.x / 2 , RightArm.ImageSize.y / 2 };
		Vec2 RightBottom = { -RightArm.ImageSize.x / 2 , RightArm.ImageSize.y / 2 };

		RightArm.ImageQuad.LeftTop = Multiply(LeftTop, mat);
		RightArm.ImageQuad.RightTop = Multiply(RightTop, mat);
		RightArm.ImageQuad.LeftBottom = Multiply(LeftBottom, mat);
		RightArm.ImageQuad.RightBottom = Multiply(RightBottom, mat);

		RightArm.ImageQuad.LeftTop += RightArm.ImagePos;
		RightArm.ImageQuad.RightTop += RightArm.ImagePos;
		RightArm.ImageQuad.LeftBottom += RightArm.ImagePos;
		RightArm.ImageQuad.RightBottom += RightArm.ImagePos;

		theta = -angle / 180.0f * M_PI;

		mat = MakeRotateMatrix(theta);

		LeftTop = { LeftArm.ImageSize.x / 2 , -LeftArm.ImageSize.y / 2 };
		RightTop = { -LeftArm.ImageSize.x / 2 , -LeftArm.ImageSize.y / 2 };
		LeftBottom = { LeftArm.ImageSize.x / 2 , LeftArm.ImageSize.y / 2 };
		RightBottom = { -LeftArm.ImageSize.x / 2 , LeftArm.ImageSize.y / 2 };

		LeftArm.ImageQuad.LeftTop = Multiply(LeftTop, mat);
		LeftArm.ImageQuad.RightTop = Multiply(RightTop, mat);
		LeftArm.ImageQuad.LeftBottom = Multiply(LeftBottom, mat);
		LeftArm.ImageQuad.RightBottom = Multiply(RightBottom, mat);

		LeftArm.ImageQuad.LeftTop += LeftArm.ImagePos;
		LeftArm.ImageQuad.RightTop += LeftArm.ImagePos;
		LeftArm.ImageQuad.LeftBottom += LeftArm.ImagePos;
		LeftArm.ImageQuad.RightBottom += LeftArm.ImagePos;
	}
	else{
		CircleOfDeathMotionT = 0;
		CircleOfDeathMotionT2 = 0;

		RightArm.MotionPos = { 0,0 };
		LeftArm.MotionPos = { 0,0 };
		Body.MotionPos = { 0,0 };
		Head.MotionPos = { 0,0 };

		RightArm.StandMotionFlag = 1;
		LeftArm.StandMotionFlag = 1;
		Body.StandMotionFlag = 1;
		Head.StandMotionFlag = 1;

	}
}

void Boss::RainOfSwordMotion(int type) {
	if (type == 0) {
		RightArm.StandMotionFlag = 0;
		LeftArm.StandMotionFlag = 0;
		Head.StandMotionFlag = 0;
		Body.StandMotionFlag = 0;
		Leg.StandMotionFlag = 0;

		Easing::easing(RainofswordMotionT, 0, 1, 1.0f / 120, Easing::easeInSine);

		RightArm.MotionPos.y = 20 + 180.0f * RainofswordMotionT;
		LeftArm.MotionPos.y = 20 + 180.0f * RainofswordMotionT;
		Head.MotionPos.y = 30.0f * RainofswordMotionT;
		Body.MotionPos.y = 20.0f * RainofswordMotionT;
		Leg.MotionPos.y = 10.0f * RainofswordMotionT;

		int angle = 180 - 150 * RainofswordMotionT;

		float theta = angle / 180.0f * M_PI;

		Matrix2x2 mat = MakeRotateMatrix(theta);

		Vec2 LeftTop = { -RightArm.ImageSize.x / 2 , -RightArm.ImageSize.y / 2 + 72 };
		Vec2 RightTop = { RightArm.ImageSize.x / 2 , -RightArm.ImageSize.y / 2 + 72 };
		Vec2 LeftBottom = { -RightArm.ImageSize.x / 2 , RightArm.ImageSize.y / 2 + 72 };
		Vec2 RightBottom = { RightArm.ImageSize.x / 2 , RightArm.ImageSize.y / 2 + 72 };

		LeftTop.x *= Direction;
		RightTop.x *= Direction;
		LeftBottom.x *= Direction;
		RightBottom.x *= Direction;

		RightArm.ImageQuad.LeftTop = Multiply(LeftTop, mat);
		RightArm.ImageQuad.RightTop = Multiply(RightTop, mat);
		RightArm.ImageQuad.LeftBottom = Multiply(LeftBottom, mat);
		RightArm.ImageQuad.RightBottom = Multiply(RightBottom, mat);

		RightArm.ImageQuad.LeftTop += RightArm.ImagePos;
		RightArm.ImageQuad.RightTop += RightArm.ImagePos;
		RightArm.ImageQuad.LeftBottom += RightArm.ImagePos;
		RightArm.ImageQuad.RightBottom += RightArm.ImagePos;

		theta = -angle / 180.0f * M_PI;

		mat = MakeRotateMatrix(theta);

		LeftTop = { -LeftArm.ImageSize.x / 2 , -LeftArm.ImageSize.y / 2 + 72 };
		RightTop = { LeftArm.ImageSize.x / 2 , -LeftArm.ImageSize.y / 2 + 72 };
		LeftBottom = { -LeftArm.ImageSize.x / 2 , LeftArm.ImageSize.y / 2 + 72 };
		RightBottom = { LeftArm.ImageSize.x / 2 , LeftArm.ImageSize.y / 2 + 72 };

		LeftTop.x *= Direction;
		RightTop.x *= Direction;
		LeftBottom.x *= Direction;
		RightBottom.x *= Direction;

		LeftArm.ImageQuad.LeftTop = Multiply(LeftTop, mat);
		LeftArm.ImageQuad.RightTop = Multiply(RightTop, mat);
		LeftArm.ImageQuad.LeftBottom = Multiply(LeftBottom, mat);
		LeftArm.ImageQuad.RightBottom = Multiply(RightBottom, mat);

		LeftArm.ImageQuad.LeftTop += LeftArm.ImagePos;
		LeftArm.ImageQuad.RightTop += LeftArm.ImagePos;
		LeftArm.ImageQuad.LeftBottom += LeftArm.ImagePos;
		LeftArm.ImageQuad.RightBottom += LeftArm.ImagePos;
	}else if (type == 1) {

		Easing::easing(RainofswordMotionT2, 0, 1, 1.0f / 15, Easing::easeInOutBack);

		RightArm.MotionPos.y = 180.0f - 200.0f * RainofswordMotionT2;
		LeftArm.MotionPos.y = 180.0f - 200.0f * RainofswordMotionT2;
		Head.MotionPos.y = 30.0f - 70.0f * RainofswordMotionT2;
		Body.MotionPos.y = 20.0f - 50.0f * RainofswordMotionT2;
		Leg.MotionPos.y = 10.0f - 20.0f * RainofswordMotionT2;

		int angle = 30 + 150 * RainofswordMotionT;

		float theta = angle / 180.0f * M_PI;

		Matrix2x2 mat = MakeRotateMatrix(theta);

		Vec2 LeftTop = { RightArm.ImageSize.x / 2 , -RightArm.ImageSize.y / 2 };
		Vec2 RightTop = { -RightArm.ImageSize.x / 2 , -RightArm.ImageSize.y / 2  };
		Vec2 LeftBottom = { RightArm.ImageSize.x / 2 , RightArm.ImageSize.y / 2  };
		Vec2 RightBottom = { -RightArm.ImageSize.x / 2 , RightArm.ImageSize.y / 2  };

		LeftTop.x *= Direction;
		RightTop.x *= Direction;
		LeftBottom.x *= Direction;
		RightBottom.x *= Direction;

		RightArm.ImageQuad.LeftTop = Multiply(LeftTop, mat);
		RightArm.ImageQuad.RightTop = Multiply(RightTop, mat);
		RightArm.ImageQuad.LeftBottom = Multiply(LeftBottom, mat);
		RightArm.ImageQuad.RightBottom = Multiply(RightBottom, mat);

		RightArm.ImageQuad.LeftTop += RightArm.ImagePos;
		RightArm.ImageQuad.RightTop += RightArm.ImagePos;
		RightArm.ImageQuad.LeftBottom += RightArm.ImagePos;
		RightArm.ImageQuad.RightBottom += RightArm.ImagePos;

		theta = -angle / 180.0f * M_PI;

		mat = MakeRotateMatrix(theta);

		LeftTop = { LeftArm.ImageSize.x / 2 , -LeftArm.ImageSize.y / 2};
		RightTop = { -LeftArm.ImageSize.x / 2 , -LeftArm.ImageSize.y / 2 };
		LeftBottom = { LeftArm.ImageSize.x / 2 , LeftArm.ImageSize.y / 2 };
		RightBottom = { -LeftArm.ImageSize.x / 2 , LeftArm.ImageSize.y / 2 };

		LeftTop.x *= Direction;
		RightTop.x *= Direction;
		LeftBottom.x *= Direction;
		RightBottom.x *= Direction;

		LeftArm.ImageQuad.LeftTop = Multiply(LeftTop, mat);
		LeftArm.ImageQuad.RightTop = Multiply(RightTop, mat);
		LeftArm.ImageQuad.LeftBottom = Multiply(LeftBottom, mat);
		LeftArm.ImageQuad.RightBottom = Multiply(RightBottom, mat);

		LeftArm.ImageQuad.LeftTop += LeftArm.ImagePos;
		LeftArm.ImageQuad.RightTop += LeftArm.ImagePos;
		LeftArm.ImageQuad.LeftBottom += LeftArm.ImagePos;
		LeftArm.ImageQuad.RightBottom += LeftArm.ImagePos;
	}
	else {

	RainofswordMotionT = 0;
	RainofswordMotionT2 = 0;

	RightArm.MotionPos = { 0,0 };
	LeftArm.MotionPos = { 0,0 };
	Body.MotionPos = { 0,0 };
	Head.MotionPos = { 0,0 };
	Leg.MotionPos = { 0,0 };

	RightArm.StandMotionFlag = 1;
	LeftArm.StandMotionFlag = 1;
	Body.StandMotionFlag = 1;
	Head.StandMotionFlag = 1;
	Leg.StandMotionFlag = 1;

	}
}
