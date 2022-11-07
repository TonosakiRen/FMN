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
	screen.DrawQuad2(blade.Quad_Pos, 0, 0, 0, 0, 0, BLACK);
	
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
	Novice::ScreenPrintf(500, 400, "boss:state:%d", pattarn);

}
void Boss::KeepUP(PlayerMain& player) {
	//プレイヤーについていく関数使わないかもしれない
	Vec2 vel = (player.Translation() - Pos).Normalized();
	Pos.x += vel.x*20;

}
void Boss::DirectionGet(PlayerMain& player) {
	//プレイヤーの位置によってマイナスかプラスかわかる関羽数うすうす進巣
	if (player.Translation().x <= Pos.x) {
		Direction = -1;
	}
	else Direction = 1;
}
void Boss::RandMoveSet() {
	
	switch (pattarn) {
		case NEAR_1:


		for (int i = 0; i < MAX_PATTERN; i++) {
			if (0 <= i && i <= 4) {
				MovePattern[i] = array.AttackFunction01;

			}
			else
				if (5 <= i && i <= 9) {
					MovePattern[i] = array.AttackFunction02;

				}
				else
					if (10 <= i && i <= 14) {
						MovePattern[i] = array.AttackFunction03;

					}
					else
						if (15 <= i && i <= 19) {
							MovePattern[i] = array.AttackFunction02;

						}
						else
							if (20 <= i && i <= 24) {
								MovePattern[i] = array.AttackFunction02;

							}
							else
								if (MovePattern[i] == 0) {
									MovePattern[i] = array.NormalAttack;

								}
		}
		break;
		case MIDDLE:
			for (int i = 0; i < MAX_PATTERN; i++) {
				if (0 <= i && i <= 4) {
					MovePattern[i] = 0;
				}else
				if (5 <= i && i <= 9) {
					MovePattern[i] = 0;
				}else
				if (10 <= i && i <= 14) {
					MovePattern[i] = 0;
				}else
				if (15 <= i && i <= 19) {
					MovePattern[i] =0;
				}else
				if (20 <= i && i <= 24) {
					MovePattern[i] = 0;
				}else
				if (MovePattern[i] == 0) {
					MovePattern[i] = 0;
				}
			}
			break;
		case FAR_1:
			for (int i = 0; i < MAX_PATTERN; i++) {
				if (0 <= i && i <= 4) {
					MovePattern[i] = array.AttackFunction05;
				}
				else
					if (5 <= i && i <= 9) {
						MovePattern[i] = array.AttackFunction05;
					}
					else
						if (10 <= i && i <= 14) {
							MovePattern[i] = array.AttackFunction05;
						}
						else
							if (15 <= i && i <= 19) {
								MovePattern[i] = array.AttackFunction05;
							}
							else
								if (20 <= i && i <= 24) {
									MovePattern[i] = array.AttackFunction05;
								}
								else
									if (MovePattern[i] == 0) {
										MovePattern[i] = array.AttackFunction05;
									}
			}
			break;
	}
}

void Boss::RandamMoveSelect(int rand,PlayerMain& player)
{
	

	Novice::ScreenPrintf(1000, 0, "Cooltime::%d", CoolTime);
	Novice::ScreenPrintf(1000, 20, "Action_Boss::%d", Action);
	Novice::ScreenPrintf(1000, 40, "Movearray::%d", MoveArray);
	Novice::ScreenPrintf(1000, 60, "MovePattarn::%d", MovePattern[MoveArray]);


	

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

	if (Action == true) {
		CoolTime = 80;

		if (MovePattern[MoveArray] == array.NormalAttack) {
			//通常攻撃のコードはここ
			NomalSwordAttack(player);
			CoolTime = 50;

		}
		if (MovePattern[MoveArray] == array.AttackFunction01) {
			//5%の攻撃
			NomalRotedSwordAttack(player);

			/*Action = false;*/
		}
		if (MovePattern[MoveArray] == array.AttackFunction02) {
			//5%の攻撃
			//NomalRotedSwordAttack(player);
			NomalRotedSwordAttack(player);

			/*Action = false;*/

		}
		if (MovePattern[MoveArray] == array.AttackFunction03) {
			//5%の攻撃
			NomalRotedSwordAttack(player);
			/*Action = false;*/

		}
		if (MovePattern[MoveArray] == array.AttackFunction04) {
			//5%の攻撃
			JumpAttack(player);

			/*Action = false;*/

		}
		if (MovePattern[MoveArray] == array.AttackFunction05) {
			//5%の攻撃
			JumpAttack(player);

			/*Action = false;*/

		}
		if (MovePattern[MoveArray] == 0) {
			Action = false;
		}
		//関数の終わりにAction=falseと関数内で使った変数の初期化をしろおおおおおおお
		//関数ないとこにはAction=falseを入れること。
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

		screen.DrawQuad2(ArkSword.quad[i], 0, 0, 0, 0, 0, GREEN);
	}
}

void Boss::NomalSwordAttack(PlayerMain& player)
{
	Vec2 Distance = Pos - player.Translation();
	if (Distance.Length() < 300||Attack==true) {
		Attack = true;
	}
	else KeepUP(player);
	//DirectionGet(player);

	if (Attack == true) {
		blade.angle = Easing::easing(blade.t, 0, 180, 0.025f, Easing::easeInBack)*-Direction;

		blade.theta = blade.angle / 180.0f * M_PI;

		Matrix2x2 mat = MakeRotateMatrix(blade.theta);
		//剣の座標最初の
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
		}
	}
}
void Boss::NomalRotedSwordAttack(PlayerMain& player) {
	//DirectionGet(player);

	blade.angle += 10;

	blade.theta = blade.angle / 180.0f * M_PI;
	
	if (blade.Roted_t != 1) {
		blade.Vec_RotedPos = { Easing::easing(blade.Roted_t, 0, 750 * Direction, 0.02f, Easing::easeInCubic), 0 };
	}
	else if (blade.Roted_t == 1 && blade.Roted_tback != 1) {
		blade.Vec_RotedPos = { Easing::easing(blade.Roted_tback, 750 * Direction, 0, 0.02f, Easing::easeInCubic), 0 };

	}
	Matrix2x2 mat = MakeRotateMatrix(blade.theta);
	//剣の座標最初の
	Vec2 LeftTop = { -Size.x / 3,Size.y };
	Vec2 RightTop = { Size.x / 3 ,Size.y };
	Vec2 LeftBottom = { -Size.x / 3,0 };
	Vec2 RightBottom = { Size.x / 3,0 };
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
	}
}
void Boss::JumpAttack(PlayerMain& player) 
{
	
	if (Attack == false) {
		jumpattack.F_Pos = {Pos};
		jumpattack.PlayerPosF = player.Translation();
		Attack = true;
	}else
	if (Attack == true) {
		if (jumpattack.Matched == false) {
			Pos.x = Easing::easing(jumpattack.EaseT, jumpattack.F_Pos.x, jumpattack.PlayerPosF.x, 0.02f, Easing::easeOutCubic);
			Pos.y = Easing::easing(jumpattack.EaseT2, Size.y / 2, 600, 0.03f, Easing::easeOutCirc);

			if (jumpattack.EaseT==1) {
			
				jumpattack.Matched = true;

			}
		}
		else
		if (jumpattack.Matched == true) {
			Pos.y = Easing::easing(jumpattack.EaseDownT, 600, Size.y/2, 0.02f, Easing::easeOutBounce);
		}
		if (jumpattack.EaseDownT == 1.0f) {
			blade.Init();
			jumpattack.Init();
			Attack = false;
			Action = false;

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
