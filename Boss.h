#include<Novice.h>
#include "Vec2.h"
#include "Quad.h"
#include"Screen.h"
#include"PlayerMain.h"
#include"Circle.h"


const int MAX_PATTERN = 100;
const int kMAX_CIR = 7;
const int kMAX_RAINSWORD = 30;
const int kMAX_WAVE = 3;
class Boss {
	//画像の宣言
	int Rainsword_gra = 0;
	int Mahoujin_gra = 0;
	int Blade_gra = 0;

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

	Quad BladeImageQuad;
	Vec2 BladeImageSize = {140,460};

	int HP = 2000;
	int HalfHP = HP / 2;
	int load = 0;//画像読み来み
	struct Blade
	{
		Quad Quad_Pos = { { 9999,9999 },{ 10000,9999 },{ 9999,10000 },{ 10000,10000 } };
		Vec2 LeftTop = { 9999,9999 };
		Vec2 RightTop = { 10000,9999 };
		Vec2 LeftBottom = { 9999,10000 };
		Vec2 RightBottom = { 10000,10000 };
		float theta = 0;
		float angle = 0;
		float t = 0;
		float t_back=0;
		bool Back=0;
		Vec2 FPosBoss = {};
		float Boss_t = 0;
		void Init() {
			Quad_Pos = { { 9999,9999 } , { 10000,9999 } , { 9999,10000 }, { 10000,10000 } };
			LeftTop = { 9999,9999 };
			RightTop = { 10000,9999 };
			LeftBottom = { 9999,10000 };
			RightBottom = { 10000,10000 };
			angle = 0; //angleで角度を0 ~ 360 で表す。それをThetaに直すんだよ
			theta = 0;
			t = 0;
			Vec_RotedPos={};
			Roted_t = 0;
			Roted_tback = 0;
			t_back = 0;
			Back = 0;
			FPosBoss = {};
			Boss_t = 0;
		}
		Vec2 Vec_RotedPos;
		float Roted_t = 0;
		float Roted_tback = 0;
		

	};
	struct ShockWave {
		Quad QuadPos = { {0,0},{0,0},{0,0},{0,0} };
		Quad Quad2Pos = { {0,0},{0,0},{0,0},{0,0} };
		/*Vec2 Pos = {};
		Vec2 Pos2 = {};*/
		float LifeTime = 0;
		bool WaveKeep = false;
		bool Reserve = true;


	}Wave;
	struct CircleOfDeath {
		Circle circle = { {0,0},0 };
		Quad Quad_Pos = {};
		float fRad = {};
		bool Set = false;
		bool Reserve = true;
		float Reserve_t = 0;
		
		void Init() {
			circle = { {0,0},0 };
			Quad_Pos = {};
			Set = false;
			Reserve = true;
			Reserve_t = 0;
			fRad = 0;

		}

	}Circleofdeath[kMAX_CIR];
	int Circleofdeath_flame;
	struct RainOfSword {
		Vec2 Pos={0,0};
		Quad QuadPos= {};
		bool Set = false;
		bool Reserve = false;
		int Width = 0;
		int Height = 0;
		float DownT = 0;
		float AddT = 0;
		float AddT2 = 0;

		void Init() {
			Pos = {9990,9990};
			 AddT2 = 0;

			Reserve = false;
			QuadPos = {};
			Set = false;
			DownT = 0;
			AddT = 0;
			Width = 0;
			Height = 0;
		}

	}Rainofsword[kMAX_RAINSWORD];
	int Rainofsword_flame;

	struct Keep {
		int Time = 0;
		int rand = 0;
	}keep;
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
	} hppattarn=NORMAL;
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

		bool bNormalAttack = false;
		bool bAttackFunction01 = false;
		bool bAttackFunction02 = false;
		bool bAttackFunction03 = false;
		bool bAttackFunction04 = false;
		bool bAttackFunction05 = false;
		
		
		
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
	int FMoveArray;
	int CoolTime;
	bool NormalAttack;
	bool Action;
	bool Attack;
	bool SwordAttack;
	int AttackStartTime = 0;

	int reload = 0;

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

	bool isBossHit = false; //攻撃を当てられた

	Vec2 BladeCenterPos;

#pragma region Parts
	struct ImageStruct {
		Vec2 ImagePos; //ボスの座標 + パーツの位置 +パーツ位置のズレ 初期設定は{0,0}でおｋ
		Vec2 ImageSize; // パーツのサイズ
		Vec2 PosMisal; //  !!!!値を変更しないで!!!! パーツの位置 この値をボスの中心座標に加算する
		Quad ImageQuad; // クアッドホッパーピンクとか追加されないかなぁ。ポイントセンサーとグレートバリアがいいなぁ。ホントはサメ使いたいけど
		Vec2 PulsPos; //パーツ位置のズレ、モーションとかで動かすときに使う
		Vec2 PulsPosSpeed;
		Vec2 ColSize; //当たり判定のサイズ
		Vec2 ColMisal; //当たり判定の位置
		Quad ColQuad; //当たり判定のクアッド
	};


	ImageStruct Head = {
		{0,0},
		{90,82},
		{18,155},
		{ { Head.ImagePos.x - Head.ImageSize.x / 2, Head.ImagePos.y + Head.ImageSize.y / 2},
		int(Head.ImageSize.x),int(Head.ImageSize.y) },
		{0,-2},
		{0,0.25},
		{64,70},
		{2,-5},
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
		{0,0.25},
		{132,144},
		{5,-4},
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
		{0,0},
		{96,106},
		{1,11},
		{ { Leg.ImagePos.x - Leg.ColMisal.x - Leg.ColSize.x / 2, Leg.ImagePos.y + Leg.ColMisal.y + Leg.ColSize.y / 2},
		int(Leg.ColSize.x),int(Leg.ColSize.y) },
	};

	ImageStruct RightArm = {
		{0,0},
		{52,116},
		{-94,-4},
		{ { RightArm.ImagePos.x - RightArm.ImageSize.x / 2, RightArm.ImagePos.y + RightArm.ImageSize.y / 2},
		int(RightArm.ImageSize.x),int(RightArm.ImageSize.y) },
		{0,-5},
		{0,0.25},
		{38,74},
		{1,-11},
		{ { RightArm.ImagePos.x - RightArm.ColMisal.x - RightArm.ColSize.x / 2, RightArm.ImagePos.y + RightArm.ColMisal.y + RightArm.ColSize.y / 2},
		int(RightArm.ColSize.x),int(RightArm.ColSize.y) },
	};

	ImageStruct LeftArm = {
		{0,0},
		{52,116},
		{86,-4},
		{ { LeftArm.ImagePos.x - LeftArm.ImageSize.x / 2, LeftArm.ImagePos.y + LeftArm.ImageSize.y / 2},
		int(LeftArm.ImageSize.x),int(LeftArm.ImageSize.y) },
		{0,-5},
		{0,0.25},
		{38,74},
		{-1,-11},
		{ { LeftArm.ImagePos.x - LeftArm.ColMisal.x - LeftArm.ColSize.x / 2, LeftArm.ImagePos.y + LeftArm.ColMisal.y + LeftArm.ColSize.y / 2},
		int(LeftArm.ColSize.x),int(LeftArm.ColSize.y) },
	};

	float ArmPosAngle = 2.25;
	float ArmPosAngleSpeed = 2.25;

#pragma endregion

public:
	Boss();
	void Set();
	void Draw(Screen& screen,int texsture, int headtex, int bodytex, int legtex, int rightarm, int leftarm);
	void UpDate();
	void State(PlayerMain& player);
	void KeepUP(PlayerMain& player);
	void KeepUpWaitBack(PlayerMain& player);
	void DirectionGet(PlayerMain& player);
	void RandamMoveSelect(int rand,PlayerMain& player, Screen& screen);
	void RandMoveSet();
	int ReloadMove(int Movearry);
	//スキル
	void AttackFunction01(Screen& screen);
	void NomalSwordAttack(PlayerMain& player);
	void NomalSwordAttack2(PlayerMain& player);
	void NomalRotedSwordAttack(PlayerMain& player);
	void NomalRotedSwordAttack2(PlayerMain& player);
	void JumpAttack(PlayerMain& player,Screen& screen);
	void ShockWaveAttack(PlayerMain& player, Screen& screen);
	void CircleOfDeathAttack(PlayerMain& player);
	void RainOfSwordAttack();
	//スキル出したかどうか：：次に出すやつを変えれる
	bool bNomalSwordAttack = false;
	bool bNomalRotedSwordAttack = false;
	bool bJumpAttack = false;
	bool bShockWaveAttack = false;
	bool bCircleOfDeathAttack = false;
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

	Quad GetShockWave();
	Quad GetShockWave2();


	Quad GetBossAttackQuad();
	Quad GetBossBladeQuad();
	bool GetAction();
	bool GetSwordAttack();

	void BossHit(bool Hit);

	void BladeImageLink(Matrix2x2 mat);

};
