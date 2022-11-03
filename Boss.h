#pragma once
#include<Novice.h>
#include "Vec2.h"
#include "Clamp.h"
#include "Quad.h"
#include"Screen.h"
#include"PlayerMain.h"
#include "Easing.h"

const int MAX_PATTERN = 100;
class Boss {

	float easing(float t, float start, float end) {

		return((1.0f - t) * start + t * end);
	};
	int  easing(float t, int start, int end) {

		return((1.0f - t) * start + t * end);
	};
	static struct Matrix2x2
	{
		float m[2][2];
	};
	Vec2 Multiply(Vec2 vector, Matrix2x2 matrix) {
		Vec2 matrix3 = { 0,0 };
		matrix3.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0];
		matrix3.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1];
		return matrix3;

	}
	Matrix2x2 MakeRotateMatrix(float theta)
	{

		Matrix2x2 matrix;
		matrix.m[0][0] = cos(theta);
		matrix.m[0][1] = sin(theta);
		matrix.m[1][0] = -sin(theta);
		matrix.m[1][1] = cos(theta);

		return matrix;
	}

	Vec2 Pos;
	Quad Quad_Pos;
	Vec2 Size;
	Vec2 LeftTop;
	Vec2 RightTop;
	Vec2 LeftBottom;
	Vec2 RightBottom;
	struct Blade
	{
		Quad Quad_Pos;
		Vec2 LeftTop = { 0,0 };
		Vec2 RightTop = { 0,0 };
		Vec2 LeftBottom = { 0,0 };
		Vec2 RightBottom = { 0,0 };
		float theta = 0;
		float t = 0;
		void Init() {
			Quad_Pos = {};
			LeftTop = { 0,0 };
			RightTop = { 0,0 };
			LeftBottom = { 0,0 };
			RightBottom = { 0,0 };
			theta = 0;
			t = 0;
		}

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
	Blade blade;
	
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
	void NomalSwordAttack();
	
};
