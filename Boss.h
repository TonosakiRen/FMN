#pragma once
#include<Novice.h>
#include "Vec2.h"
#include "Clamp.h"
#include "Quad.h"
#include"Screen.h"
#include"PlayerMain.h"

const int MAX_PATTERN = 100;
class Boss {
	Vec2 Pos;
	Quad Quad_Pos;
	Vec2 Size;
	Vec2 LeftTop;
	Vec2 RightTop;
	Vec2 LeftBottom;
	Vec2 RightBottom;
	struct Blade {
		Vec2 Pos;
		
	};
	enum Pattarn
	{
		NEAR_1,
		FAR_1,
		MIDDLE,
	};

	Pattarn pattarn = MIDDLE;
	//îzóÒÇÃïœêî
	struct  Array {
		int Min;
		int Max;
		int Normal;

		int  NormalAttack=9992;
		int AttackFunction01 = 83029;
		int AttackFunction02 = 839;
		int AttackFunction03 = 23029;
		int AttackFunction04 = 329;
		int AttackFunction05 = 129;
	};
	struct AttackFunction01 {
		Quad quad[6];
	};
	Array array;
	AttackFunction01 ArkSword;
	
	bool Direction;
	int AnimeFlame=9;
	int SrcX;

	int MovePattern[MAX_PATTERN];
	int MoveArray;
	int CoolTime;
	bool NormalAttack;
	bool Action;

	struct NomalAttak {
		Quad quad;
	};
	NomalAttak nomalattack;


public:
	Boss();
	void Set();
	void Draw(Screen& screen);
	void State(PlayerMain& player);
	void RandamMoveSelect();
	void AttackFunction01(Screen& screen);
	
};
