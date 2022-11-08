#include "Boss.h"

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

void Boss::Draw(Screen& screen)
{
	screen.DrawQuad2Renban(Quad_Pos, SrcX, 0, 0, 0, 0, 60, AnimeFlame, 0, RED, Direction);
	screen.DrawQuad2(blade.Quad_Pos, 0, 0, 0, 0, 0, WHITE);
	screen.DrawQuad2(Wave.QuadPos, 0, 0, 0, 0, 0, GREEN);
	screen.DrawQuad2(Wave.Quad2Pos, 0, 0, 0, 0, 0, GREEN);
	for (int i = 0; i < kMAX_CIR; i++) {
		screen.DrawEllipse(Circleofdeath[i].Pos.x, Circleofdeath[i].Pos.y, Circleofdeath[i].Rad, Circleofdeath[i].Rad, 0, WHITE, kFillModeSolid);
		screen.DrawEllipse(Circleofdeath[i].Pos.x, Circleofdeath[i].Pos.y, Circleofdeath[i].fRad, Circleofdeath[i].fRad, 0, WHITE, kFillModeWireFrame);

	}

	
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
	}

}
void Boss::KeepUP(PlayerMain& player) {
	//ÉvÉåÉCÉÑÅ[Ç…Ç¬Ç¢ÇƒÇ¢Ç≠ä÷êîégÇÌÇ»Ç¢Ç©Ç‡ÇµÇÍÇ»Ç¢
	Vec2 vel = (player.Translation() - Pos).Normalized();
	Pos.x += vel.x*20;

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

void Boss::RandamMoveSelect(int rand,PlayerMain& player,Screen& screen)
{
	

	Novice::ScreenPrintf(1000, 0, "Cooltime::%d", CoolTime);
	Novice::ScreenPrintf(1000, 20, "Action_Boss::%d", Action);
	Novice::ScreenPrintf(1000, 40, "Movearray::%d", MoveArray);
	Novice::ScreenPrintf(1000, 60, "MovePattarn::%d", MovePattern[MoveArray]);
	Novice::ScreenPrintf(1000, 80, "boss:state:%d", pattarn);


	

	if (CoolTime == 0&&Action==false) {
		MoveArray =rand;
		Action =true;
		DirectionGet(player);

	}
	else if (CoolTime != 0&&Action==false) {
		CoolTime--;
		State(player);

	}
		RandMoveSet();

		KeepWaveAttack();

		if (Action == true) {
			CoolTime = 30;

			switch (pattarn) {
			case NEAR_1:
			{
				if (MovePattern[MoveArray] == array.NormalAttack) {
					//í èÌçUåÇÇÃÉRÅ[ÉhÇÕÇ±Ç±
					//NomalSwordAttack(player);
					CircleOfDeathAttack();
					//ShockWaveAttack(player, screen);
					CoolTime = 50;

				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%ÇÃçUåÇ
					//NomalRotedSwordAttack(player);
					NomalSwordAttack(player);

					/*Action = false;*/
				}
				if (MovePattern[MoveArray] == array.AttackFunction02) {
					//5%ÇÃçUåÇ
					//NomalRotedSwordAttack(player);
					//NomalRotedSwordAttack(player);
					NomalSwordAttack(player);

					/*Action = false;*/

				}
				if (MovePattern[MoveArray] == array.AttackFunction03) {
					//5%ÇÃçUåÇ
					//NomalSwordAttack(player);

					NomalRotedSwordAttack(player);
					/*Action = false;*/

				}
				if (MovePattern[MoveArray] == array.AttackFunction04) {
					//5%ÇÃçUåÇ
					//JumpAttack(player);
					//NomalRotedSwordAttack(player);
					NomalSwordAttack(player);

					/*Action = false;*/

				}
				if (MovePattern[MoveArray] == array.AttackFunction05) {
					//5%ÇÃçUåÇ
					//JumpAttack(player);
					//NomalRotedSwordAttack(player);
					NomalSwordAttack(player);

					/*Action = false;*/

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
					CoolTime = 50;

				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%ÇÃçUåÇ
					NomalRotedSwordAttack(player);

					/*Action = false;*/
				}
				if (MovePattern[MoveArray] == array.AttackFunction02) {
					//5%ÇÃçUåÇ
					//NomalRotedSwordAttack(player);
					NomalRotedSwordAttack(player);

					/*Action = false;*/

				}
				if (MovePattern[MoveArray] == array.AttackFunction03) {
					//5%ÇÃçUåÇ
					NomalRotedSwordAttack(player);
					/*Action = false;*/

				}
				if (MovePattern[MoveArray] == array.AttackFunction04) {
					//5%ÇÃçUåÇ
					//JumpAttack(player);
					NomalRotedSwordAttack(player);

					/*Action = false;*/

				}
				if (MovePattern[MoveArray] == array.AttackFunction05) {
					//5%ÇÃçUåÇ
					//JumpAttack(player);
					NomalRotedSwordAttack(player);

					/*Action = false;*/

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

					CoolTime = 50;

				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%ÇÃçUåÇ
					//NomalRotedSwordAttack(player);
					//JumpAttack(player, screen);
					ShockWaveAttack(player, screen);

					/*Action = false;*/
				}
				if (MovePattern[MoveArray] == array.AttackFunction02) {
					//5%ÇÃçUåÇ
					//NomalRotedSwordAttack(player);
					//NomalRotedSwordAttack(player);
					ShockWaveAttack(player, screen);
					//JumpAttack(player, screen);
					/*Action = false;*/

				}
				if (MovePattern[MoveArray] == array.AttackFunction03) {
					//5%ÇÃçUåÇ
					//NomalRotedSwordAttack(player);
					//JumpAttack(player, screen);
					/*Action = false;*/
					ShockWaveAttack(player, screen);

				}
				if (MovePattern[MoveArray] == array.AttackFunction04) {
					//5%ÇÃçUåÇ
					//JumpAttack(player, screen);
					ShockWaveAttack(player, screen);

					/*Action = false;*/

				}
				if (MovePattern[MoveArray] == array.AttackFunction05) {
					//5%ÇÃçUåÇ
					//JumpAttack(player, screen);
					ShockWaveAttack(player, screen);

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

		screen.DrawQuad2(ArkSword.quad[i], 0, 0, 0, 0, 0, GREEN);
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
			Vec2 LeftTop = { -Size.x / 3,Size.y };
			Vec2 RightTop = { Size.x / 3 ,Size.y };
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
		blade.Vec_RotedPos = { Easing::easing(blade.Roted_tback, 750 * Direction, 0, 0.02f, Easing::easeInCubic), 100 };

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

			}
		}
}

void Boss::CircleOfDeathAttack()
{
	Circleofdeath_flame++;
	for (int i = 0; i < kMAX_CIR; i++) {
		if (Circleofdeath_flame%10==0&&Circleofdeath[i].Set == false/*&& Circleofdeath[i].Reserve==true*/&& Circleofdeath[kMAX_CIR-1].Set==false) {
			Circleofdeath[i].Pos = { Pos.x + Randam::RAND(-800,800),Pos.y + Randam::RAND(-100,300) };
			Circleofdeath[i].fRad = 100;

			Circleofdeath[i].Set=true;
			break;
		}
		if (/*Circleofdeath[i].Set == true*/Circleofdeath[kMAX_CIR - 1].Set==true) {
			Circleofdeath[i].Reserve = false;
			Circleofdeath[i].Rad = Easing::easing(Circleofdeath[i].Reserve_t, 0, Circleofdeath[i].fRad, 0.01f, Easing::easeInBounce);
			if (Circleofdeath[i].Reserve_t == 1.0f) {
				Circleofdeath[i].Init();
				Circleofdeath_flame = 0;
				
			}
		}
			if (Circleofdeath[kMAX_CIR - 1].Reserve_t == 1) {
				Action = false;
			}
	}
}

void Boss::KeepWaveAttack()
{
	if (Wave.WaveKeep == false) {
		Wave.QuadPos.Quad::Quad({ Pos.x - 50,Pos.y  }, 100, 200);
		Wave.Quad2Pos.Quad::Quad({ Pos.x - 50,Pos.y }, 100, 200);

	}
	if (Wave.WaveKeep == true) {
		Wave.QuadPos.LeftTop.x += 40;
		Wave.Quad2Pos.LeftTop.x -= 40;
		Wave.QuadPos.Quad::Quad(Wave.QuadPos.LeftTop, 100, 200);
		Wave.Quad2Pos.Quad::Quad(Wave.Quad2Pos.LeftTop, 100, 200);

		Wave.LifeTime += 0.01f;
		Wave.LifeTime = Clamp::clamp(Wave.LifeTime, 0, 1);

		if (Wave.LifeTime == 1.0f) {
			Wave.WaveKeep = false;
			Wave.LifeTime = 0;
		}
	}
}



Quad Boss::GetBossQuad()
{
	return Quad(Quad_Pos);
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
