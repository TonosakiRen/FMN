#pragma once
#include<Novice.h>
#include "Vec2.h"
#include "Clamp.h"
#include "Quad.h"
#include "Key.h"
#include"Screen.h"
#include"PlayerMain.h"
#include "Easing.h"
#include "Randam.h"

const int MAX_PATTERN = 100;
class Boss {


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
	float HP = 5000;
	struct Blade
	{
		Quad Quad_Pos = { {0,0} , {1,0} , {0,1} , {1,1} };
		Vec2 LeftTop = { 0,0 };
		Vec2 RightTop = { 1,0 };
		Vec2 LeftBottom = { 0,1 };
		Vec2 RightBottom = { 1,1 };
		float theta = 0;
		float angle = 0;
		float t = 0;
		void Init() {
			Quad_Pos = { {0,0} , { 1,0 } , {0,1} , {1,1} };
			LeftTop = { 0,0 };
			RightTop = { 1,0 };
			LeftBottom = { 0,1 };
			RightBottom = { 1,1 };
			angle = 0; //angleで角度を0 ~ 360 で表す。それをThetaに直すんだよ
			theta = 0;
			t = 0;
			Vec_RotedPos={};
			Roted_t = 0;
			Roted_tback = 0;
		}
		Vec2 Vec_RotedPos;
		float Roted_t = 0;
		float Roted_tback = 0;


	};
	struct ShockWave {
		Quad QuadPos = {};
		Quad Quad2Pos = {};
		Vec2 Pos = {};
		Vec2 Pos2 = {};
		float LifeTime = {};
		bool WaveKeep = false;
		bool Reserve = true;


	}Wave;
	enum Pattarn
	{
		NEAR_1,
		MIDDLE,
		FAR_1,
	};

	Pattarn pattarn = MIDDLE;
	//配列の変数
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
	
	int Direction = -1;
	int AnimeFlame=9;
	int SrcX;

	int MovePattern[MAX_PATTERN];
	int MoveArray;
	int CoolTime;
	bool NormalAttack;
	bool Action;
	bool Attack;
	bool SwordAttack;
	int AttackStartTime = 0;
	struct NomalAttak {
		Quad quad;
		
	};
	NomalAttak nomalattack;
	struct JumpAttack {
		float EaseT = 0;
		float EaseT2=0;
		float EaseDownT=0;
		Vec2 PlayerPosF;
		Vec2 F_Pos;
		bool Matched=false;
		void Init() {
			EaseT = 0;
			EaseDownT = 0; 
			EaseT2 = 0;
			Matched = false;
			PlayerPosF={};
			F_Pos={};
		}
	};
	JumpAttack jumpattack;

	struct ImageStruct {
		Vec2 ImagePos; //ボスの座標 + パーツの位置 +パーツ位置のズレ 初期設定は{0,0}でおｋ
		Vec2 ImageSize; // パーツのサイズ
		Vec2 PosMisal; //  !!!!値を変更しないで!!!! パーツの位置 この値をボスの中心座標に加算する
		Quad ImageQuad; // クアッドホッパーピンクとか追加されないかなぁ。ポイントセンサーとグレートバリアがいいなぁ。ホントはサメ使いたいけど
		Vec2 PulsPos; //パーツ位置のズレ、モーションとかで動かすときに使う
		Vec2 ColSize; //当たり判定のサイズ
		Vec2 ColMisal; //当たり判定の位置
		Quad ColQuad; //当たり判定のクアッド
	};

	ImageStruct Base = {
		{0,0},
		{ 250,400 },
		{0,0},
		{ {Base.ImagePos.x - Base.ImageSize.x / 2, Base.ImagePos.y + Base.ImageSize.y / 2},
		int(Base.ImageSize.x),int(Base.ImageSize.y) },
		{0,0}
	};

	ImageStruct Head = {
		{0,0},
		{90,82},
		{18,155},
		{ { Head.ImagePos.x - Head.ImageSize.x / 2, Head.ImagePos.y + Head.ImageSize.y / 2},
		int(Head.ImageSize.x),int(Head.ImageSize.y) },
		{0,0},
		{64,70},
		{-2,-5},
		{ { Head.ImagePos.x - Head.ColMisal.x - Head.ColSize.x / 2, Head.ImagePos.y + Head.ColMisal.y + Head.ColSize.y / 2},
		int(Head.ColSize.x),int(Head.ColSize.y) },
	};

	ImageStruct Body = {
		{0,0},
		{146,164},
		{2,52},
		{ { Body.ImagePos.x - Body.ImageSize.x / 2, Body.ImagePos.y + Body.ImageSize.y / 2},
		int(Body.ImageSize.x),int(Body.ImageSize.y) },
		{0,0},
		{132,144},
		{-5,-4},
		{ { Body.ImagePos.x - Body.ColMisal.x - Body.ColSize.x / 2, Body.ImagePos.y + Body.ColMisal.y + Body.ColSize.y / 2},
		int(Body.ColSize.x),int(Body.ColSize.y) },
	};

	ImageStruct Leg = {
		{0,0},
		{130,130},
		{-4,-59},
		{ { Leg.ImagePos.x - Leg.ImageSize.x / 2, Leg.ImagePos.y + Leg.ImageSize.y / 2},
		int(Leg.ImageSize.x),int(Leg.ImageSize.y) },
		{0,0},
		{96,106},
		{-1,11},
		{ { Leg.ImagePos.x - Leg.ColMisal.x - Leg.ColSize.x / 2, Leg.ImagePos.y + Leg.ColMisal.y + Leg.ColSize.y / 2},
		int(Leg.ColSize.x),int(Leg.ColSize.y) },
	};

	ImageStruct RightArm = {
		{0,0},
		{52,116},
		{-94,-4},
		{ { RightArm.ImagePos.x - RightArm.ImageSize.x / 2, RightArm.ImagePos.y + RightArm.ImageSize.y / 2},
		int(RightArm.ImageSize.x),int(RightArm.ImageSize.y) },
		{0,0},
		{38,74},
		{-1,-11},
		{ { RightArm.ImagePos.x - RightArm.ColMisal.x - RightArm.ColSize.x / 2, RightArm.ImagePos.y + RightArm.ColMisal.y + RightArm.ColSize.y / 2},
		int(RightArm.ColSize.x),int(RightArm.ColSize.y) },
	};

	ImageStruct LeftArm = {
		{0,0},
		{52,116},
		{86,-4},
		{ { LeftArm.ImagePos.x - LeftArm.ImageSize.x / 2, LeftArm.ImagePos.y + LeftArm.ImageSize.y / 2},
		int(LeftArm.ImageSize.x),int(LeftArm.ImageSize.y) },
		{0,0},
		{38,74},
		{1,-11},
		{ { LeftArm.ImagePos.x - LeftArm.ColMisal.x - LeftArm.ColSize.x / 2, LeftArm.ImagePos.y + LeftArm.ColMisal.y + LeftArm.ColSize.y / 2},
		int(LeftArm.ColSize.x),int(LeftArm.ColSize.y) },
	};

public:
	Boss();
	void Set();
	void Draw(Screen& screen,int texsture, int headtex, int bodytex, int legtex, int rightarm, int leftarm);
	void UpDate();
	void State(PlayerMain& player);
	void KeepUP(PlayerMain& player);
	void DirectionGet(PlayerMain& player);
	void RandamMoveSelect(int rand,PlayerMain& player, Screen& screen);
	void RandMoveSet();

	//スキル
	void AttackFunction01(Screen& screen);
	void NomalSwordAttack(PlayerMain& player);
	void NomalRotedSwordAttack(PlayerMain& player);
	void JumpAttack(PlayerMain& player,Screen& screen);
	void ShockWaveAttack(PlayerMain& player, Screen& screen);
	//派生スキル::行動が終わっても出続ける的なもの
	void KeepWaveAttack();
	

	enum {
		head,
		body,
		leg,
		rightarm,
		leftarm
	};
	
	Quad GetBossQuad(int BossParts);

	Quad GetBossAttackQuad();
	Quad GetBossBladeQuad();
	bool GetAction();
	bool GetSwordAttack();

};
