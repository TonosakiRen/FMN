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

	if (Head.PulsPos.y >= 0) {
		Head.PulsPosSpeed *= -1;
	}
	else if (Head.PulsPos.y <= -10) {
		Head.PulsPosSpeed *= -1;
	}

	if (Body.PulsPos.y >= 0) {
		Body.PulsPosSpeed *= -1;
	}
	else if (Body.PulsPos.y <= -10) {
		Body.PulsPosSpeed *= -1;
	}

	if (Leg.PulsPos.y >= 0) {
		Leg.PulsPosSpeed *= -1;
	}
	else if (Leg.PulsPos.y <= -10) {
		Leg.PulsPosSpeed *= -1;
	}

	if (RightArm.PulsPos.y >= 0) {
		RightArm.PulsPosSpeed *= -1;
	}
	else if (RightArm.PulsPos.y <= -10) {
		RightArm.PulsPosSpeed *= -1;
	}

	if (LeftArm.PulsPos.y >= 0) {
		LeftArm.PulsPosSpeed *= -1;
	}
	else if (LeftArm.PulsPos.y <= -10) {
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

	Body.ImagePos = { Pos .x + Body.PosMisal.x * Direction + Body.PulsPos.x,Pos.y + Body.PosMisal.y + Body.PulsPos.y };
	Body.ImageQuad = { {Body.ImagePos.x - Body.ImageSize.x / 2, Body.ImagePos.y + Body.ImageSize.y / 2},
		int(Body.ImageSize.x),int(Body.ImageSize.y) };
	Body.ColQuad = { { Body.ImagePos.x - Body.ColMisal.x * Direction - Body.ColSize.x / 2, Body.ImagePos.y + Body.ColMisal.y + Body.ColSize.y / 2},
		int(Body.ColSize.x),int(Body.ColSize.y) };

	Head.ImagePos = { Pos.x + Head.PosMisal.x * Direction + Head.PulsPos.x,Pos.y + Head.PosMisal.y + Head.PulsPos.y };
	Head.ImageQuad = { {Head.ImagePos.x - Head.ImageSize.x / 2, Head.ImagePos.y + Head.ImageSize.y / 2},
		int(Head.ImageSize.x),int(Head.ImageSize.y) };
	Head.ColQuad = { { Head.ImagePos.x - Head.ColMisal.x * Direction - Head.ColSize.x / 2, Head.ImagePos.y + Head.ColMisal.y + Head.ColSize.y / 2},
		int(Head.ColSize.x),int(Head.ColSize.y) };

	Leg.ImagePos = { Pos.x + Leg.PosMisal.x * Direction + Leg.PulsPos.x,Pos.y + Leg.PosMisal.y + Leg.PulsPos.y };
	Leg.ImageQuad = { {Leg.ImagePos.x - Leg.ImageSize.x / 2, Leg.ImagePos.y + Leg.ImageSize.y / 2},
		int(Leg.ImageSize.x),int(Leg.ImageSize.y) };
	Leg.ColQuad = { { Leg.ImagePos.x - Leg.ColMisal.x * Direction - Leg.ColSize.x / 2, Leg.ImagePos.y + Leg.ColMisal.y + Leg.ColSize.y / 2},
		int(Leg.ColSize.x),int(Leg.ColSize.y) };

	RightArm.ImagePos = { Pos.x + RightArm.PosMisal.x * Direction + RightArm.PulsPos.x,Pos.y + RightArm.PosMisal.y + RightArm.PulsPos.y };
	RightArm.ImageQuad = { {RightArm.ImagePos.x - RightArm.ImageSize.x / 2, RightArm.ImagePos.y + RightArm.ImageSize.y / 2},
		int(RightArm.ImageSize.x),int(RightArm.ImageSize.y) };
	RightArm.ColQuad = { { RightArm.ImagePos.x - RightArm.ColMisal.x * Direction - RightArm.ColSize.x / 2, RightArm.ImagePos.y + RightArm.ColMisal.y + RightArm.ColSize.y / 2},
		int(RightArm.ColSize.x),int(RightArm.ColSize.y) };


	LeftArm.ImagePos = { Pos.x + LeftArm.PosMisal.x * Direction + LeftArm.PulsPos.x,Pos.y + LeftArm.PosMisal.y + LeftArm.PulsPos.y };
	LeftArm.ImageQuad = { {LeftArm.ImagePos.x - LeftArm.ImageSize.x / 2, LeftArm.ImagePos.y + LeftArm.ImageSize.y / 2},
		int(LeftArm.ImageSize.x),int(LeftArm.ImageSize.y) };
	LeftArm.ColQuad = { { LeftArm.ImagePos.x - LeftArm.ColMisal.x * Direction - LeftArm.ColSize.x / 2, LeftArm.ImagePos.y + LeftArm.ColMisal.y + LeftArm.ColSize.y / 2},
		int(LeftArm.ColSize.x),int(LeftArm.ColSize.y) };

	//çUåÇÇìñÇƒÇÁÇÍÇΩéûÇÃèàóù
	if (isBossHit == true) {
		HP-=50;
	};

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
	}
	bool BossisFlip = false;

	if (Direction == 1) {
		BossisFlip = true;
	}
	else {
		BossisFlip = false;
	}

	screen.DrawQuad2(blade.Quad_Pos, 0, 0, 0, 0, 0, 0xFFFFFF11);
	
	screen.DrawQuad2(Wave.QuadPos, 0, 0, 0, 0, 0, 0x00FF0011);
	screen.DrawQuad2(Wave.Quad2Pos, 0, 0, 0, 0, 0, 0x00FF0011);
	
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

	for (int i = 0; i < kMAX_CIR; i++) {
		screen.DrawEllipse(Circleofdeath[i].circle.pos.x, Circleofdeath[i].circle.pos.y, Circleofdeath[i].circle.radius, Circleofdeath[i].circle.radius, 0, 0xFFFFFF66, kFillModeSolid);
		screen.DrawEllipse(Circleofdeath[i].circle.pos.x, Circleofdeath[i].circle.pos.y, Circleofdeath[i].fRad, Circleofdeath[i].fRad, 0, 0xFFFFFFFF, kFillModeWireFrame);
		screen.DrawQuad2(Circleofdeath[i].Quad_Pos, 0, 0, 600, 600, Mahoujin_gra, WHITE);
	}
	Novice::DrawBox(20, 20, HP, 80, 0, GREEN, kFillModeSolid);
	for (int i = 0; i < kMAX_RAINSWORD; i++) {
		screen.DrawQuad2(Rainofsword[i].QuadPos, 0, 0, 100, 200, Rainsword_gra, RED);
	}
	Novice::ScreenPrintf(0, 70, "Boss HitCount %d", HP);
	Clamp::clamp(HP, 0, 10000);
}

void Boss::State(PlayerMain& player)
{
	Vec2 Distance = Pos - player.Translation();
	if (Action == false) {
		if (Distance.Length() < 400) {
			pattarn = NEAR_1;
		}
		else
			if (Distance.Length() < 800) {
				pattarn = MIDDLE;
			}
			else {
				pattarn = FAR_1;
			}
		if (HP < HalfHP) {
			hppattarn = HALF;
		}
		else {
			hppattarn = NORMAL;
		}
	}
}
void Boss::KeepUP(PlayerMain& player) {
	//ÉvÉåÉCÉÑÅ[Ç…Ç¬Ç¢ÇƒÇ¢Ç≠ä÷êîégÇÌÇ»Ç¢Ç©Ç‡ÇµÇÍÇ»Ç¢
	Vec2 vel = (player.Translation() - Pos).Normalized();
	Pos.x += vel.x*20;

}
void Boss::KeepUpWaitBack(PlayerMain&player)
{
	
	keep.Time++;
	if (keep.Time == 30) {
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
void Boss::DirectionGet(PlayerMain& player) {
	//ÉvÉåÉCÉÑÅ[ÇÃà íuÇ…ÇÊÇ¡ÇƒÉ}ÉCÉiÉXÇ©ÉvÉâÉXÇ©ÇÌÇ©ÇÈä÷âHêîÇ§Ç∑Ç§Ç∑êiëÉ
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

	}

		KeepWaveAttack();

		if (Action == true) {
			
			switch (hppattarn)
			{
				
			case NORMAL:
				CoolTime = 60;

				switch (pattarn) {
				case NEAR_1:
				{
					if (MovePattern[MoveArray] == array.NormalAttack) {
						//í èÌçUåÇÇÃÉRÅ[ÉhÇÕÇ±Ç±
						NomalSwordAttack(player);
						//RainOfSwordAttack();
						//CircleOfDeathAttack();
						//ShockWaveAttack(player, screen);
						
						FMoveArray = array.NormalAttack;
					}
					if (MovePattern[MoveArray] == array.AttackFunction01) {
						//5%ÇÃçUåÇ
						NomalRotedSwordAttack(player);
						/*NomalSwordAttack(player);
						array.bAttackFunction01 = true;
						array.InitNotThis(array.bAttackFunction01);*/
						/*CoolTime = 40;*/
						FMoveArray = array.AttackFunction01;

						
						//Action = false;
					}
					if (MovePattern[MoveArray] == array.AttackFunction02 ) {
						//5%ÇÃçUåÇ
						//NomalRotedSwordAttack(player);
						//NomalSwordAttack(player);

						
						
						//FMoveArray = array.AttackFunction02;
						CoolTime = 0;
						Action = false;
					}
					if (MovePattern[MoveArray] == array.AttackFunction03 ) {
						//5%ÇÃçUåÇ
						//NomalSwordAttack(player);
						ShockWaveAttack(player, screen);

						//NomalRotedSwordAttack(player);
						/*Action = false;
						CoolTime = 0;*/
						FMoveArray = array.AttackFunction03;


					}
					if (MovePattern[MoveArray] == array.AttackFunction04 ) {
						//5%ÇÃçUåÇ
						//JumpAttack(player);
						//NomalRotedSwordAttack(player);
						//NomalSwordAttack(player);
						ShockWaveAttack(player, screen);						
						FMoveArray = array.AttackFunction04;
						/*CoolTime = 0;
						Action = false;*/

					}
					if (MovePattern[MoveArray] == array.AttackFunction05 ) {
						//5%ÇÃçUåÇ
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
					//ä÷êîÇÃèIÇÌÇËÇ…Action=falseÇ∆ä÷êîì‡Ç≈égÇ¡ÇΩïœêîÇÃèâä˙âªÇÇµÇÎÇ®Ç®Ç®Ç®Ç®Ç®Ç®
					//ä÷êîÇ»Ç¢Ç∆Ç±Ç…ÇÕAction=falseÇì¸ÇÍÇÈÇ±Ç∆ÅB
					break;
				}
				case MIDDLE:
				{
					if (MovePattern[MoveArray] == array.NormalAttack) {
						//í èÌçUåÇÇÃÉRÅ[ÉhÇÕÇ±Ç±
						//NomalSwordAttack(player);
						NomalRotedSwordAttack(player);
						FMoveArray = array.NormalAttack;
					}
					if (MovePattern[MoveArray] == array.AttackFunction01) {
						//5%ÇÃçUåÇ
						//NomalRotedSwordAttack(player);
						NomalSwordAttack(player);
						/*Action = false;*/
						FMoveArray = array.AttackFunction01;

					}
					if (MovePattern[MoveArray] == array.AttackFunction02) {
						//5%ÇÃçUåÇ
						//NomalRotedSwordAttack(player);
						NomalSwordAttack(player);

						FMoveArray = array.AttackFunction02;
						/*Action = false;*/

					}
					if (MovePattern[MoveArray] == array.AttackFunction03) {
						//5%ÇÃçUåÇ
						NomalSwordAttack(player);

						//NomalRotedSwordAttack(player);
						/*Action = false;*/
						FMoveArray = array.AttackFunction03;
					}
					if (MovePattern[MoveArray] == array.AttackFunction04) {
						//5%ÇÃçUåÇ
						//JumpAttack(player);
						//NomalRotedSwordAttack(player);
						ShockWaveAttack(player, screen);
						/*Action = false;*/
						FMoveArray = array.AttackFunction04;
					}
					if (MovePattern[MoveArray] == array.AttackFunction05) {
						//5%ÇÃçUåÇ
						//JumpAttack(player);
						//NomalRotedSwordAttack(player);
						ShockWaveAttack(player, screen);
						CoolTime = 30;
						/*Action = false;*/
						FMoveArray = array.AttackFunction05;
					}
					if (MovePattern[MoveArray] == 0) {
						Action = false;
					}
					//ä÷êîÇÃèIÇÌÇËÇ…Action=falseÇ∆ä÷êîì‡Ç≈égÇ¡ÇΩïœêîÇÃèâä˙âªÇÇµÇÎÇ®Ç®Ç®Ç®Ç®Ç®Ç®
					//ä÷êîÇ»Ç¢Ç∆Ç±Ç…ÇÕAction=falseÇì¸ÇÍÇÈÇ±Ç∆ÅB
					break;
				}
				case FAR_1:
				{
					if (MovePattern[MoveArray] == array.NormalAttack) {
						//í èÌçUåÇÇÃÉRÅ[ÉhÇÕÇ±Ç±
						//NomalSwordAttack(player);
						//JumpAttack(player, screen);
						ShockWaveAttack(player, screen);

						FMoveArray = array.NormalAttack;

					}
					if (MovePattern[MoveArray] == array.AttackFunction01) {
						//5%ÇÃçUåÇ
						//NomalRotedSwordAttack(player);
						//JumpAttack(player, screen);
						NomalSwordAttack(player);
						//ShockWaveAttack(player, screen);
						//CircleOfDeathAttack(player);
						/*Action = false;*/
						FMoveArray = array.AttackFunction01;
					}
					if (MovePattern[MoveArray] == array.AttackFunction02) {
						//5%ÇÃçUåÇ
						//NomalRotedSwordAttack(player);
						//NomalRotedSwordAttack(player);
						//CircleOfDeathAttack(player);
						NomalSwordAttack(player);
						//ShockWaveAttack(player, screen);
						//JumpAttack(player, screen);
						/*Action = false;*/
						FMoveArray = array.AttackFunction02;
					}
					if (MovePattern[MoveArray] == array.AttackFunction03) {
						//5%ÇÃçUåÇ
						//NomalRotedSwordAttack(player);
						//JumpAttack(player, screen);
						//ShockWaveAttack(player, screen);
						CircleOfDeathAttack(player);
						FMoveArray = array.AttackFunction03;
						/*Action = false;*/
					}
					if (MovePattern[MoveArray] == array.AttackFunction04) {
						//5%ÇÃçUåÇ
						//JumpAttack(player, screen);
						//ShockWaveAttack(player, screen);
						CircleOfDeathAttack(player);
						FMoveArray = array.AttackFunction04;
						/*Action = false;*/
					}
					if (MovePattern[MoveArray] == array.AttackFunction05) {
						//5%ÇÃçUåÇ
						//JumpAttack(player, screen);
						//ShockWaveAttack(player, screen);
						CircleOfDeathAttack(player);
						FMoveArray = array.AttackFunction05;
						/*Action = false;*/
					}
					if (MovePattern[MoveArray] == 0) {
						Action = false;
					}
					//ä÷êîÇÃèIÇÌÇËÇ…Action=falseÇ∆ä÷êîì‡Ç≈égÇ¡ÇΩïœêîÇÃèâä˙âªÇÇµÇÎÇ®Ç®Ç®Ç®Ç®Ç®Ç®
					//ä÷êîÇ»Ç¢Ç∆Ç±Ç…ÇÕAction=falseÇì¸ÇÍÇÈÇ±Ç∆ÅB
					break;
				}
				}
				break;

				case THREEQUARTERS:
					CoolTime = 45;

					switch (pattarn) {
					case NEAR_1:
					{
						if (MovePattern[MoveArray] == array.NormalAttack) {
							//í èÌçUåÇÇÃÉRÅ[ÉhÇÕÇ±Ç±
							NomalSwordAttack2(player);
							//CircleOfDeathAttack();
							//ShockWaveAttack(player, screen);

							FMoveArray = array.NormalAttack;
						}
						if (MovePattern[MoveArray] == array.AttackFunction01) {
							//5%ÇÃçUåÇ
							NomalRotedSwordAttack(player);
							/*NomalSwordAttack(player);
							array.bAttackFunction01 = true;
							array.InitNotThis(array.bAttackFunction01);*/
							/*CoolTime = 40;*/
							FMoveArray = array.AttackFunction01;


							//Action = false;
						}
						if (MovePattern[MoveArray] == array.AttackFunction02) {
							//5%ÇÃçUåÇ
							//NomalRotedSwordAttack(player);
							NomalSwordAttack(player);



							FMoveArray = array.AttackFunction02;
							/*CoolTime = 0;
							Action = false;*/
						}
						if (MovePattern[MoveArray] == array.AttackFunction03) {
							//5%ÇÃçUåÇ
							//NomalSwordAttack(player);
							ShockWaveAttack(player, screen);

							//NomalRotedSwordAttack(player);
							/*Action = false;
							CoolTime = 0;*/
							FMoveArray = array.AttackFunction03;


						}
						if (MovePattern[MoveArray] == array.AttackFunction04) {
							//5%ÇÃçUåÇ
							//JumpAttack(player);
							//NomalRotedSwordAttack(player);
							//NomalSwordAttack(player);
							ShockWaveAttack(player, screen);


							FMoveArray = array.AttackFunction04;

							/*CoolTime = 0;

							Action = false;*/

						}
						if (MovePattern[MoveArray] == array.AttackFunction05) {
							//5%ÇÃçUåÇ
							//JumpAttack(player);
							NomalRotedSwordAttack2(player);
							//NomalSwordAttack(player);
							//ShockWaveAttack(player, screen);


							FMoveArray = array.AttackFunction05;

							/*Action = false;
							CoolTime = 0;*/

						}
						if (MovePattern[MoveArray] == 0) {

							Action = false;
						}
						//ä÷êîÇÃèIÇÌÇËÇ…Action=falseÇ∆ä÷êîì‡Ç≈égÇ¡ÇΩïœêîÇÃèâä˙âªÇÇµÇÎÇ®Ç®Ç®Ç®Ç®Ç®Ç®
						//ä÷êîÇ»Ç¢Ç∆Ç±Ç…ÇÕAction=falseÇì¸ÇÍÇÈÇ±Ç∆ÅB
						break;
					}
					case MIDDLE:
					{
						if (MovePattern[MoveArray] == array.NormalAttack) {
							//í èÌçUåÇÇÃÉRÅ[ÉhÇÕÇ±Ç±
							//NomalSwordAttack(player);
							NomalRotedSwordAttack2(player);
							FMoveArray = array.NormalAttack;
						}
						if (MovePattern[MoveArray] == array.AttackFunction01) {
							//5%ÇÃçUåÇ
							//NomalRotedSwordAttack(player);
							NomalSwordAttack2(player);
							/*Action = false;*/
							FMoveArray = array.AttackFunction01;

						}
						if (MovePattern[MoveArray] == array.AttackFunction02) {
							//5%ÇÃçUåÇ
							//NomalRotedSwordAttack(player);
							NomalSwordAttack2(player);

							FMoveArray = array.AttackFunction02;
							/*Action = false;*/

						}
						if (MovePattern[MoveArray] == array.AttackFunction03) {
							//5%ÇÃçUåÇ
							NomalSwordAttack(player);

							//NomalRotedSwordAttack(player);
							/*Action = false;*/
							FMoveArray = array.AttackFunction03;
						}
						if (MovePattern[MoveArray] == array.AttackFunction04) {
							//5%ÇÃçUåÇ
							//JumpAttack(player);
							//NomalRotedSwordAttack(player);
							ShockWaveAttack(player, screen);
							/*Action = false;*/
							FMoveArray = array.AttackFunction04;
						}
						if (MovePattern[MoveArray] == array.AttackFunction05) {
							//5%ÇÃçUåÇ
							//JumpAttack(player);
							//NomalRotedSwordAttack(player);
							ShockWaveAttack(player, screen);
							CoolTime = 30;
							/*Action = false;*/
							FMoveArray = array.AttackFunction05;
						}
						if (MovePattern[MoveArray] == 0) {
							Action = false;
						}
						//ä÷êîÇÃèIÇÌÇËÇ…Action=falseÇ∆ä÷êîì‡Ç≈égÇ¡ÇΩïœêîÇÃèâä˙âªÇÇµÇÎÇ®Ç®Ç®Ç®Ç®Ç®Ç®
						//ä÷êîÇ»Ç¢Ç∆Ç±Ç…ÇÕAction=falseÇì¸ÇÍÇÈÇ±Ç∆ÅB
						break;
					}
					case FAR_1:
					{
						if (MovePattern[MoveArray] == array.NormalAttack) {
							//í èÌçUåÇÇÃÉRÅ[ÉhÇÕÇ±Ç±
							//NomalSwordAttack(player);
							//JumpAttack(player, screen);
							ShockWaveAttack(player, screen);

							FMoveArray = array.NormalAttack;

						}
						if (MovePattern[MoveArray] == array.AttackFunction01) {
							//5%ÇÃçUåÇ
							//NomalRotedSwordAttack(player);
							//JumpAttack(player, screen);
							//ShockWaveAttack(player, screen);
							CircleOfDeathAttack(player);
							/*Action = false;*/
							FMoveArray = array.AttackFunction01;
						}
						if (MovePattern[MoveArray] == array.AttackFunction02) {
							//5%ÇÃçUåÇ
							//NomalRotedSwordAttack(player);
							//NomalRotedSwordAttack(player);
							CircleOfDeathAttack(player);

							//ShockWaveAttack(player, screen);
							//JumpAttack(player, screen);
							/*Action = false;*/
							FMoveArray = array.AttackFunction02;
						}
						if (MovePattern[MoveArray] == array.AttackFunction03) {
							//5%ÇÃçUåÇ
							//NomalRotedSwordAttack(player);
							//JumpAttack(player, screen);
							/*Action = false;*/
							//ShockWaveAttack(player, screen);
							CircleOfDeathAttack(player);
							FMoveArray = array.AttackFunction03;
						}
						if (MovePattern[MoveArray] == array.AttackFunction04) {
							//5%ÇÃçUåÇ
							//JumpAttack(player, screen);
							//ShockWaveAttack(player, screen);
							CircleOfDeathAttack(player);

							/*Action = false;*/
							FMoveArray = array.AttackFunction04;
						}
						if (MovePattern[MoveArray] == array.AttackFunction05) {
							//5%ÇÃçUåÇ
							//JumpAttack(player, screen);
							//ShockWaveAttack(player, screen);
							CircleOfDeathAttack(player);

							/*Action = false;*/
							FMoveArray = array.AttackFunction05;
						}
						if (MovePattern[MoveArray] == 0) {
							Action = false;
						}
						//ä÷êîÇÃèIÇÌÇËÇ…Action=falseÇ∆ä÷êîì‡Ç≈égÇ¡ÇΩïœêîÇÃèâä˙âªÇÇµÇÎÇ®Ç®Ç®Ç®Ç®Ç®Ç®
						//ä÷êîÇ»Ç¢Ç∆Ç±Ç…ÇÕAction=falseÇì¸ÇÍÇÈÇ±Ç∆ÅB
						break;
					}
					}
					break;

			case HALF:
				CoolTime = 30;
				switch (pattarn) {
				case NEAR_1:
				{
					if (MovePattern[MoveArray] == array.NormalAttack) {
						//í èÌçUåÇÇÃÉRÅ[ÉhÇÕÇ±Ç±
						NomalSwordAttack2(player);
						//CircleOfDeathAttack();
						//ShockWaveAttack(player, screen);
						/*CoolTime = 50;*/
						FMoveArray = array.NormalAttack;
					}
					if (MovePattern[MoveArray] == array.AttackFunction01) {
						//5%ÇÃçUåÇ
						//NomalRotedSwordAttack(player);
						NomalSwordAttack2(player);
						FMoveArray = array.AttackFunction01;
						/*Action = false;*/
					}
					if (MovePattern[MoveArray] == array.AttackFunction02) {
						//5%ÇÃçUåÇ
						//NomalRotedSwordAttack(player);
						NomalSwordAttack2(player);
						FMoveArray = array.AttackFunction02;
						/*Action = false;*/

					}
					if (MovePattern[MoveArray] == array.AttackFunction03) {
						//5%ÇÃçUåÇ
						//NomalSwordAttack(player);
						ShockWaveAttack(player, screen);

						//NomalRotedSwordAttack(player);
						/*Action = false;*/
						FMoveArray = array.AttackFunction03;
					}
					if (MovePattern[MoveArray] == array.AttackFunction04) {
						//5%ÇÃçUåÇ
						//JumpAttack(player);
						//NomalRotedSwordAttack(player);
						//NomalSwordAttack(player);
						ShockWaveAttack(player, screen);

						/*Action = false;*/
						FMoveArray = array.AttackFunction04;
					}
					if (MovePattern[MoveArray] == array.AttackFunction05) {
						//5%ÇÃçUåÇ
						//JumpAttack(player);
						//NomalRotedSwordAttack(player);
						//NomalSwordAttack(player);
						ShockWaveAttack(player, screen);

						/*Action = false;*/
						FMoveArray = array.AttackFunction05;
					}
					if (MovePattern[MoveArray] == 0) {
						Action = false;
					}
					//ä÷êîÇÃèIÇÌÇËÇ…Action=falseÇ∆ä÷êîì‡Ç≈égÇ¡ÇΩïœêîÇÃèâä˙âªÇÇµÇÎÇ®Ç®Ç®Ç®Ç®Ç®Ç®
					//ä÷êîÇ»Ç¢Ç∆Ç±Ç…ÇÕAction=falseÇì¸ÇÍÇÈÇ±Ç∆ÅB
					break;
				}
				case MIDDLE:
				{
					if (MovePattern[MoveArray] == array.NormalAttack) {
						//í èÌçUåÇÇÃÉRÅ[ÉhÇÕÇ±Ç±
						//NomalSwordAttack(player);
						NomalRotedSwordAttack(player);
						FMoveArray = array.NormalAttack;
					}
					if (MovePattern[MoveArray] == array.AttackFunction01) {
						//5%ÇÃçUåÇ
						//NomalRotedSwordAttack(player);
						CircleOfDeathAttack(player);

						//NomalSwordAttack(player);
						/*Action = false;*/
						FMoveArray = array.AttackFunction01;
					}
					if (MovePattern[MoveArray] == array.AttackFunction02) {
						//5%ÇÃçUåÇ
						//NomalRotedSwordAttack(player);
						//NomalSwordAttack(player);
						CircleOfDeathAttack(player);

						/*Action = false;*/
						FMoveArray = array.AttackFunction02;
					}
					if (MovePattern[MoveArray] == array.AttackFunction03) {
						//5%ÇÃçUåÇ
						//NomalSwordAttack(player);
						CircleOfDeathAttack(player);

						//NomalRotedSwordAttack(player);
						/*Action = false;*/
						FMoveArray = array.AttackFunction03;
					}
					if (MovePattern[MoveArray] == array.AttackFunction04) {
						//5%ÇÃçUåÇ
						//JumpAttack(player);
						//NomalRotedSwordAttack(player);
						ShockWaveAttack(player, screen);
						/*Action = false;*/
						FMoveArray = array.AttackFunction04;
					}
					if (MovePattern[MoveArray] == array.AttackFunction05) {
						//5%ÇÃçUåÇ
						//JumpAttack(player);
						//NomalRotedSwordAttack(player);
						ShockWaveAttack(player, screen);

						/*Action = false;*/
						FMoveArray = array.AttackFunction05;
					}
					if (MovePattern[MoveArray] == 0) {
						Action = false;
					}
					//ä÷êîÇÃèIÇÌÇËÇ…Action=falseÇ∆ä÷êîì‡Ç≈égÇ¡ÇΩïœêîÇÃèâä˙âªÇÇµÇÎÇ®Ç®Ç®Ç®Ç®Ç®Ç®
					//ä÷êîÇ»Ç¢Ç∆Ç±Ç…ÇÕAction=falseÇì¸ÇÍÇÈÇ±Ç∆ÅB
					break;
				}
				case FAR_1:
				{
					if (MovePattern[MoveArray] == array.NormalAttack) {
						//í èÌçUåÇÇÃÉRÅ[ÉhÇÕÇ±Ç±
						//NomalSwordAttack(player);
						//JumpAttack(player, screen);
						ShockWaveAttack(player, screen);

						FMoveArray = array.NormalAttack;

					}
					if (MovePattern[MoveArray] == array.AttackFunction01) {
						//5%ÇÃçUåÇ
						//NomalRotedSwordAttack(player);
						//JumpAttack(player, screen);
						//ShockWaveAttack(player, screen);
						CircleOfDeathAttack(player);
						/*Action = false;*/
						FMoveArray = array.AttackFunction01;
					}
					if (MovePattern[MoveArray] == array.AttackFunction02) {
						//5%ÇÃçUåÇ
						//NomalRotedSwordAttack(player);
						//NomalRotedSwordAttack(player);
						CircleOfDeathAttack(player);

						//ShockWaveAttack(player, screen);
						//JumpAttack(player, screen);
						/*Action = false;*/
						FMoveArray = array.AttackFunction02;
					}
					if (MovePattern[MoveArray] == array.AttackFunction03) {
						//5%ÇÃçUåÇ
						//NomalRotedSwordAttack(player);
						//JumpAttack(player, screen);
						/*Action = false;*/
						//ShockWaveAttack(player, screen);
						CircleOfDeathAttack(player);
						FMoveArray = array.AttackFunction03;
					}
					if (MovePattern[MoveArray] == array.AttackFunction04) {
						//5%ÇÃçUåÇ
						//JumpAttack(player, screen);
						//ShockWaveAttack(player, screen);
						CircleOfDeathAttack(player);

						/*Action = false;*/
						FMoveArray = array.AttackFunction04;
					}
					if (MovePattern[MoveArray] == array.AttackFunction05) {
						//5%ÇÃçUåÇ
						//JumpAttack(player, screen);
						//ShockWaveAttack(player, screen);
						CircleOfDeathAttack(player);

						/*Action = false;*/
						FMoveArray = array.AttackFunction05;
					}
					if (MovePattern[MoveArray] == 0) {
						Action = false;
					}
					//ä÷êîÇÃèIÇÌÇËÇ…Action=falseÇ∆ä÷êîì‡Ç≈égÇ¡ÇΩïœêîÇÃèâä˙âªÇÇµÇÎÇ®Ç®Ç®Ç®Ç®Ç®Ç®
					//ä÷êîÇ»Ç¢Ç∆Ç±Ç…ÇÕAction=falseÇì¸ÇÍÇÈÇ±Ç∆ÅB
					break;
				}
				}
				break;


			}
		}
}


///ÉXÉLÉãä÷êî
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
	SwordAttack = true;
	Vec2 Distance = Pos - player.Translation();
	if (Distance.Length() < 300 || Attack == true) {
		if (Attack == false) {
			AttackStartTime = 4;
		}
		Attack = true;
	}
	else { 
		KeepUP(player); 
		
	}
	//DirectionGet(player);

	if (Attack == true) {
		if (AttackStartTime <= 0) {
			blade.angle = Easing::easing(blade.t, 0, 180, 0.035f, Easing::easeInBack) * -Direction;

			blade.theta = blade.angle / 180.0f * M_PI;

			Matrix2x2 mat = MakeRotateMatrix(blade.theta);
			//åïÇÃç¿ïWç≈èâÇÃ
			Vec2 LeftTop = { -Size.x / 3,Size.y + 30 };
			Vec2 RightTop = { Size.x / 3 ,Size.y+30 };
			Vec2 LeftBottom = { -Size.x / 3,0 };
			Vec2 RightBottom = { Size.x / 3,0 };
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

			if (blade.t == 1) {
				blade.Init();
				Action = false;
				Attack = false;
				SwordAttack = false;
				bNomalSwordAttack = true;
			}
		}
		else {
			AttackStartTime--;
		}
	}
}
void Boss::NomalSwordAttack2(PlayerMain& player)
{
	SwordAttack = true;
	
	//int Fpos = Pos.x;
	Vec2 Distance = Pos - player.Translation();
	if (Distance.Length() < 300 || Attack == true) {
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
	if (Attack == false) {
		blade.FPosBoss.x = Pos.x;

	}
	if (Attack == true) {
		if (AttackStartTime <= 0) {
			blade.angle = Easing::easing(blade.t, 0, 200, 0.035f, Easing::easeInBack) * -Direction;

			blade.theta = blade.angle / 180.0f * M_PI;
			if (blade.t == 1) {
				blade.angle = Easing::easing(blade.t_back, 200, 0, 0.025f, Easing::easeInOutBack) * -Direction;

				blade.theta = blade.angle / 180.0f * M_PI;
				Pos.x = Easing::easing(blade.Boss_t, blade.FPosBoss.x, blade.FPosBoss.x +(150*Direction),0.05,Easing::easeInQuart );
			}
			else {
			}
			Matrix2x2 mat = MakeRotateMatrix(blade.theta);
			//åïÇÃç¿ïWç≈èâÇÃ
			Vec2 LeftTop = { -Size.x / 3,Size.y + 30 };
			Vec2 RightTop = { Size.x / 3 ,Size.y + 30 };
			Vec2 LeftBottom = { -Size.x / 3,0 };
			Vec2 RightBottom = { Size.x / 3,0 };
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
			}
		}
		else {
			AttackStartTime--;
		}
	}
}
void Boss::NomalRotedSwordAttack(PlayerMain& player) {
	//DirectionGet(player);
	if (blade.Vec_RotedPos.x == 0) {
		blade.angle = 30 * Direction;
	}
	
	blade.angle -= 12 * Direction;
	
	blade.theta = blade.angle / 180.0f * M_PI;
	
	if (blade.Roted_t != 1) {
		SwordAttack = true;

		blade.Vec_RotedPos = { Easing::easing(blade.Roted_t, 0, 750 * Direction, 0.02f, Easing::easeInCubic), -100 };
	}
	else if (blade.Roted_t == 1 && blade.Roted_tback != 1) {
		blade.Vec_RotedPos = { Easing::easing(blade.Roted_tback, 750 * Direction, 0, 0.02f, Easing::easeInCubic), 150 };

	}
	Matrix2x2 mat = MakeRotateMatrix(blade.theta);
	//åïÇÃç¿ïWç≈èâÇÃ
	Vec2 LeftTop = { -Size.x / 3,Size.y/2 };
	Vec2 RightTop = { Size.x / 3 ,Size.y/2 };
	Vec2 LeftBottom = { -Size.x / 3,-Size.y / 2 };
	Vec2 RightBottom = { Size.x / 3,-Size.y / 2 };
	blade.Quad_Pos = { blade.LeftTop,blade.RightTop,blade.LeftBottom,blade.RightBottom };


	blade.LeftTop = Multiply(LeftTop, mat);
	blade.RightTop = Multiply(RightTop, mat);
	blade.LeftBottom = Multiply(LeftBottom, mat);
	blade.RightBottom = Multiply(RightBottom, mat);

	blade.LeftTop += Pos+ blade.Vec_RotedPos;
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
	}
}
void Boss::NomalRotedSwordAttack2(PlayerMain& player)
{
	//DirectionGet(player);
	if (blade.Vec_RotedPos.x == 0) {
		blade.angle = 30 * Direction;
	}

	blade.angle -= 12 * Direction;

	blade.theta = blade.angle / 180.0f * M_PI;

	if (blade.Roted_t != 1) {
		SwordAttack = true;

		blade.Vec_RotedPos = { Easing::easing(blade.Roted_t, 0, 750 * Direction, 0.02f, Easing::easeInCubic), -100 };
	}
	else if (blade.Roted_t == 1 && blade.Roted_tback != 1) {
		blade.Vec_RotedPos = { Easing::easing(blade.Roted_tback, 750 * Direction, 0, 0.02f, Easing::easeInCubic), -100 };

	}
	Matrix2x2 mat = MakeRotateMatrix(blade.theta);
	//åïÇÃç¿ïWç≈èâÇÃ
	Vec2 LeftTop = { -Size.x / 3,Size.y / 2 };
	Vec2 RightTop = { Size.x / 3 ,Size.y / 2 };
	Vec2 LeftBottom = { -Size.x / 3,-Size.y / 2 };
	Vec2 RightBottom = { Size.x / 3,-Size.y / 2 };
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
	}
}
void Boss::JumpAttack(PlayerMain& player,Screen& screen) 
{
	
	if (Attack == false) {
		jumpattack.F_Pos = {Pos};
		jumpattack.PlayerPosF = player.Translation();
		Attack = true;
	}else
	if (Attack == true) {
		if (jumpattack.Matched == false) {
			Pos.x = Easing::easing(jumpattack.EaseT, jumpattack.F_Pos.x, jumpattack.PlayerPosF.x, 0.03f, Easing::easeOutCubic);
			Pos.y = Easing::easing(jumpattack.EaseT2, Size.y / 2, 600, 0.03f, Easing::easeOutCirc);

			if (jumpattack.EaseT==1) {
			
				jumpattack.Matched = true;

			}
		}
		else
		if (jumpattack.Matched == true) {
			Pos.y = Easing::easing(jumpattack.EaseDownT, 600, Size.y/2, 0.05f, Easing::easeOutBounce);
		
		}
			
			screen.Shake(0, 0, -10, 10, jumpattack.EaseDownT<=0.9f&& jumpattack.EaseDownT >= 0.8f);
		
		if (jumpattack.EaseDownT == 1.0f) {
			blade.Init();
			jumpattack.Init();
			Attack = false;
			Action = false;

		}
	}
}

void Boss::ShockWaveAttack(PlayerMain& player, Screen& screen)
{

	if (Attack == false) {
		jumpattack.F_Pos = { Pos };
		jumpattack.PlayerPosF = player.Translation();
		Attack = true;
	}
	else
		if (Attack == true) {
			if (jumpattack.Matched == false) {
				Pos.x = Easing::easing(jumpattack.EaseT, jumpattack.F_Pos.x, jumpattack.PlayerPosF.x, 0.03f, Easing::easeOutCubic);
				Pos.y = Easing::easing(jumpattack.EaseT2, Size.y / 2, 600, 0.03f, Easing::easeOutCirc);

				if (jumpattack.EaseT == 1) {

					jumpattack.Matched = true;
					//è„Ç…è„Ç™ÇËêÿÇ¡ÇΩ
				}
			}
			else
				if (jumpattack.Matched == true) {
					Pos.y = Easing::easing(jumpattack.EaseDownT, 600, Size.y / 2, 0.05f, Easing::easeOutBounce);
					//â∫Ç…óéÇøÇÈ
					if (Pos.y == Size.y/2) {
						Wave.WaveKeep = true;
						
					}
				}

			screen.Shake(0, 0, -10, 10, jumpattack.EaseDownT <= 0.9f && jumpattack.EaseDownT >= 0.8f);
			
			if (jumpattack.EaseDownT == 1.0f) {
				blade.Init();
				jumpattack.Init();
				Attack = false;
				Action = false;
				bShockWaveAttack = true;
			}
		}
}

void Boss::CircleOfDeathAttack(PlayerMain& player)
{
	Circleofdeath_flame++;
	for (int i = 0; i < kMAX_CIR; i++) {
		if (Circleofdeath_flame%13==0&&Circleofdeath[i].Set == false&& Circleofdeath[kMAX_CIR-1].Set==false) {
			if(i==0) {
				Circleofdeath[i].circle.pos = { player.GetPlayerQuad().LeftTop.x, player.GetPlayerQuad().LeftTop.y };

			}else
			if (i % 2 == 0) {
				Circleofdeath[i].circle.pos = { Pos.x + (i*150),Pos.y + Randam::RAND(-100,100) };

			}
			else if (i % 2 == 1) {
				Circleofdeath[i].circle.pos = { Pos.x + ( - i * 150),Pos.y + Randam::RAND(-100,100)};

			}
			
			Circleofdeath[i].fRad = 100;
			Circleofdeath[i].Quad_Pos.Quad::Quad(Circleofdeath[i].circle.pos, Circleofdeath[i].fRad * 2 , Circleofdeath[i].fRad * 2 , 0);

			Circleofdeath[i].Set=true;
			break;
		}
		if (/*Circleofdeath[i].Set == true*/Circleofdeath[kMAX_CIR - 1].Set==true) {
			//Circleofdeath[i].Reserve = false;
			Circleofdeath[i].circle.radius = Easing::easing(Circleofdeath[i].Reserve_t, 0, Circleofdeath[i].fRad, 0.01f, Easing::easeOutElastic);
			Circleofdeath[i].Quad_Pos.Quad::Quad(Circleofdeath[i].circle.pos, Circleofdeath[i].fRad *2+ Circleofdeath[i].circle.radius, Circleofdeath[i].fRad *2+ Circleofdeath[i].circle.radius, 0);

			if (Circleofdeath[i].Reserve_t == 1.0f) {
				//Circleofdeath[i].Init();
				
			}
		}
			
	}
	for (int i = 0; i < kMAX_CIR; i++) {

		if (Circleofdeath[kMAX_CIR - 1].Reserve_t == 1) {
			Action = false;
			Circleofdeath_flame = 0;
			Circleofdeath[i].Init();

		}
	}
}

void Boss::RainOfSwordAttack() {

	Rainofsword_flame++;
	for (int i = 0; i < kMAX_RAINSWORD; i++) {
		if (Rainofsword_flame % 4 == 0 && Rainofsword[i].Set == false) {
			Rainofsword[i].Pos.x = Pos.x+Randam::RAND(-700, 700);
			Rainofsword[i].Pos.y = 800;
			Rainofsword[i].Set = true;
			break;

		}
		if(Rainofsword[i].Set == true&& Rainofsword[i].Reserve == false){

			Rainofsword[i].Width = Easing::easing(Rainofsword[i].AddT, 0, 50, 0.03, Easing::easeInQuint);
			Rainofsword[i].Height = Easing::easing(Rainofsword[i].AddT2,0,100,0.03,Easing::easeInQuint);
			
			Rainofsword[i].QuadPos = Quad::Quad(Rainofsword[i].Pos, Rainofsword[i].Width, Rainofsword[i].Height);
			if (Rainofsword[i].AddT == 1) {
				Rainofsword[i].Reserve = true;
			}
		}
		if (Rainofsword[kMAX_RAINSWORD-1].Reserve==true) {
			Rainofsword[i].Pos.y = Easing::easing(Rainofsword[i].DownT, 800, 0 + Rainofsword[i].Height, 0.03f, Easing::easeInOutCirc);
			Rainofsword[i].QuadPos = Quad::Quad(Rainofsword[i].Pos, Rainofsword[i].Width, Rainofsword[i].Height);

		}

	}
	for (int i = 0; i < kMAX_RAINSWORD; i++) {
		if (Rainofsword[kMAX_RAINSWORD - 1].DownT == 1) {
			Rainofsword[i].Init();
			Rainofsword_flame = 0;
			Action = false;
		}
	}
}
void Boss::KeepWaveAttack()
{
	
		if (Wave.WaveKeep == false) {
			Wave.QuadPos.Quad::Quad({ Pos.x - 50,Pos.y }, 100, 200);
			Wave.Quad2Pos.Quad::Quad({ Pos.x - 50,Pos.y }, 100, 200);

		}
		if (Wave.WaveKeep == true) {
			Wave.QuadPos.LeftTop.x += 30;
			Wave.Quad2Pos.LeftTop.x -= 30;
			Wave.QuadPos.Quad::Quad(Wave.QuadPos.LeftTop, 100, 200);
			Wave.Quad2Pos.Quad::Quad(Wave.Quad2Pos.LeftTop, 100, 200);

			Wave.LifeTime += 0.025f;
			Wave.LifeTime = Clamp::clamp(Wave.LifeTime, 0, 1);

			if (Wave.LifeTime == 1.0f) {
				Wave.WaveKeep = false;
				Wave.LifeTime = 0;
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
	return Quad(Wave.QuadPos);
}

Quad Boss::GetShockWave2()
{
	return Quad(Wave.Quad2Pos);
}

Quad Boss::GetBossAttackQuad()
{
	return Quad(blade.Quad_Pos);
}

Quad Boss::GetBossBladeQuad()
{
	return Quad(blade.Quad_Pos);
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
