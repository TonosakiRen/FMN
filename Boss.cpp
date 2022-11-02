#include "Boss.h"

Boss::Boss()
{
	Size = { 150,400 };

	Pos = { 1000,Size.y/2};
	LeftTop = { Pos.x - (Size.x / 2),Pos.y + (Size.y / 2)};
	LeftBottom = Vec2(Pos - (Size/2));
	RightTop= Vec2(Pos + (Size/2));
	RightBottom = { Pos.x + (Size.x / 2),Pos.y - (Size.y / 2) };
	Quad_Pos = { LeftTop,RightTop,LeftBottom,RightBottom};
	CoolTime = 200;
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
	
	
}

void Boss::State(PlayerMain& player)
{
	Vec2 Distance = Pos - player.Translation();
	if (Distance.Length() < (Vec2(nomalattack.quad.RightBottom - nomalattack.quad.LeftBottom)).Length()) {
		pattarn = NEAR_1;
	}else
	if (Distance.Length() > (Vec2(nomalattack.quad.RightBottom - nomalattack.quad.LeftBottom)).Length()+650) {
		pattarn = FAR_1;
	}
	else {
		pattarn = MIDDLE;
	}
	



}

void Boss::RandamMoveSelect()
{
	for (int i = 0; i < MAX_PATTERN; i++) {
		MovePattern[0 || 1 || 2 || 3 || 4] = array.AttackFunction01;
		MovePattern[5 || 6 || 7 || 8 || 9] = array.AttackFunction02;
		MovePattern[10 || 11 || 12 || 13 || 14] = array.AttackFunction03;
		MovePattern[15 || 16 || 17 || 18 || 19] = array.AttackFunction04;
		MovePattern[20 || 21 || 22 || 23|| 24] = array.AttackFunction05;




		if (MovePattern[i] == 0) {
			MovePattern[i] = array.NormalAttack;

		}
	}


	if (CoolTime == 0&&Action==false) {
		MoveArray = Randam::RAND(0, MAX_PATTERN);
		CoolTime == 200;
		Action == true;
	}
	else if (CoolTime != 0&&Action==false) {
		CoolTime--;
	}

	if (Action == true) {

		if (MovePattern[MoveArray] == array.NormalAttack) {
			//’ÊíUŒ‚‚ÌƒR[ƒh‚Í‚±‚±
		}
		if (MovePattern[MoveArray] == array.AttackFunction01) {
			//5%‚ÌUŒ‚
		}
		if (MovePattern[MoveArray] == array.AttackFunction02) {
			//5%‚ÌUŒ‚
		}
		if (MovePattern[MoveArray] == array.AttackFunction03) {
			//5%‚ÌUŒ‚
		}
		if (MovePattern[MoveArray] == array.AttackFunction04) {
			//5%‚ÌUŒ‚
		}
		if (MovePattern[MoveArray] == array.AttackFunction05) {
			//5%‚ÌUŒ‚
		}
	}
}

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
