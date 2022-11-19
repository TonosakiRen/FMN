#pragma once
#include<Novice.h>
#include "Vec2.h"
#include "Quad.h"
#include"Screen.h"
#include"PlayerMain.h"
#include"Circle.h"
#include "Effect2.h"


//const int MAX_PATTERN= 100;
//const int kMAX_CIR = 7;
//const int kMAX_RAINSWORD = 30;
//const int kMAX_WAVE = 2;
const int MAX2_PATTERN = 100;
const int Max_Zan = 20;
class Boss2 {

	//画像の宣言
	int Rainsword_gra = 0;
	int Mahoujin_gra = 0;
	int Blade_gra = 0;
	int HoldBlade_gra = 0;
	int Boss_gra = 0;
	int UseBladeGra = Blade_gra;

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
	
	int HP = 2000;
	const int HalfHP = HP * 0.3f;
	const int ThreeQuarterHP = HP * 0.6f;

	struct Keep {
		int Time = 0;
		int rand = 0;
		float theta = 0;
		float YMove = 0;
		float Ease_T = 0;
		float FPos = 0;
		bool bMove = false;
		void Init() {
			
			Ease_T = 0;
			bMove = false;
		}

	}keep;
	struct Zanzou {
		Quad Pos = { {9999,9999},{9999,9999},{9999,9999},{9999,9999} };
		int LifeTime = 0;
		bool bSet = 0;
	}zanzou[Max_Zan];
	int Zanflame = 0;
	int load = 0;//画像読み来み
	
	
	//スウィッチ
	enum Pattarn
	{
		NEAR_1,
		MIDDLE,
		FAR_1,
	};
	enum HpPattarn {
		NORMAL,
		THREEQUARTERS,
		HALF,
	} hppattarn = NORMAL;
	Pattarn pattarn = MIDDLE;
	//配列の変数
	struct  Array {
		int Min;
		int Max;
		int Normal;

		int  NormalAttack = 9992;
		int AttackFunction01 = 83029;
		int AttackFunction02 = 839;
		int AttackFunction03 = 23029;
		int AttackFunction04 = 329;
		int AttackFunction05 = 129;

		bool bNormalAttack = false;
		bool bAttackFunction01 = false;
		bool bAttackFunction02 = false;
		bool bAttackFunction03 = false;
		bool bAttackFunction04 = false;
		bool bAttackFunction05 = false;



	};
	
	Array array;

	

	int Direction = -1;
	int AnimeFlame = 9;
	int SrcX;

	int MovePattern[MAX2_PATTERN];
	int MoveArray;
	int FMoveArray;
	int CoolTime;
	bool NormalAttack;
	bool Action;
	bool Attack;
	bool SwordAttack;
	int AttackStartTime = 0;

	int reload = 0;

	
	

	bool isBossHit = false; //攻撃を当てられた

	Vec2 BladeCenterPos;

	float BossMotionTime = 0;

	public:
	float centerOfDarknessMoveT = 0;
	bool isCenteroOfDarknessMove = true;
	bool isCenterOfDarkness = 0;
	bool isGetPos = false;
	float saveBoss2x;
	float savePlayerx;
	Effect2 centerOfDarknessLeft;
	Effect2 centerOfDarknessRight;
	Effect2 centerOfDarknessUnder;
	float gravityPower = 5.0f;
	const int saveCenterOfDarknessCooltime = 1000;
	int centerOfDarknessCooltime = 1000;

public:
	Boss2();
	void Set();
	void Draw(Screen& screen);
	void UpDate();
	void State(PlayerMain& player);
	void KeepUP(PlayerMain& player);
	void KeepUpWaitBack(PlayerMain& player);
	void DirectionGet(PlayerMain& player);
	void RandamMoveSelect(int rand, PlayerMain& player, Screen& screen);
	void RandMoveSet();
	int ReloadMove(int Movearry);
	void Zanzou();
	//スキル
	void CenterOfDarknessAttack(PlayerMain& player);


	//スキル出したかどうか：：次に出すやつを変えれる
	

	//派生スキル::行動が終わっても出続ける的なもの
	

	Quad GetBossQuad(){ return Quad_Pos; }

	Quad GetShockWave();
	Quad GetShockWave2();


	Quad GetBossAttackQuad();
	Quad GetBossBladeQuad();
	Quad GetRainOfSwordQuad(int i);
	Circle GetCircleOfDeathQuad(int i);
	bool GetAction();
	bool GetSwordAttack();
	bool IsLife = false;

	void BossHit(bool Hit);

	enum {
		up,
		down,
		left,
		right
	};

	void BossHitReaction(Quad PlayerQuad, bool up, bool down, bool right);

	void BladeImageLink(Matrix2x2 mat);

};
