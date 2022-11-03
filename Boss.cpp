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
	screen.DrawQuad2(blade.Quad_Pos, 0, 0, 0, 0, 0, BLACK);
	
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
		if (0 <= i && i <= 4) {
		MovePattern[i] = array.AttackFunction01;

		}else
		if (5 <= i && i <= 9) {
			MovePattern[i] = array.AttackFunction02;

		}else
		if (10 <= i && i <= 14) {
			MovePattern[i] = array.AttackFunction03;

		}else
		if (15 <= i && i <= 19) {
			MovePattern[i] = array.AttackFunction04;

		}else
		if (20 <= i && i <= 24) {
			MovePattern[i] = array.AttackFunction05;

		}else
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

		//ŠÖ”‚ÌI‚í‚è‚ÉAction=false‚ÆŠÖ”“à‚ÅŽg‚Á‚½•Ï”‚Ì‰Šú‰»‚ð‚µ‚ë‚¨‚¨‚¨‚¨‚¨‚¨‚¨
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

void Boss::NomalSwordAttack()
{
	/*blade.t += 0.00125f;
	blade.t =Clamp::clamp(blade.t,0,1.0f);*/

	/*blade.theta = easing(Easing::easeInQuart(blade.t), 0, 6);*/
	blade.theta = Easing::easing(blade.t, 0, 90, 0.01f, Easing::easeInBack);


	Matrix2x2 mat = MakeRotateMatrix(blade.theta);
	//Œ•‚ÌÀ•WÅ‰‚Ì
	Vec2 LeftTop = { -Size.x/3,Size.y };
	Vec2 RightTop = { Size.x/3 ,Size.y };
	Vec2 LeftBottom = { -Size.x/3,0 };
	Vec2 RightBottom = { Size.x/3,0 };
	blade.Quad_Pos = { blade.LeftTop,blade.RightTop,blade.LeftBottom,blade.RightBottom };


	blade.LeftTop = Multiply(LeftTop, mat);
	blade.RightTop = Multiply(RightTop, mat);
	blade.LeftBottom = Multiply(LeftBottom, mat);
	blade.RightBottom= Multiply(RightBottom, mat);

	blade.LeftTop += Pos;
	blade.RightTop += Pos;
	blade.LeftBottom += Pos;
	blade.RightBottom += Pos;

	blade.Quad_Pos = { blade.LeftTop,blade.RightTop,blade.LeftBottom,blade.RightBottom };

	if (blade.t == 1) {
		blade.Init();
		Action = false;
	}

}
