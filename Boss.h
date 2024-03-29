#include<Novice.h>
#include "Vec2.h"
#include "Quad.h"
#include"Screen.h"
#include"PlayerMain.h"
#include"Circle.h"
#include "Effect5.h"

#include"Sound.h"
#define kMAX_RAINSWORD 30
#define kMAX_CIR 7

const int MAX_PATTERN = 100;
const int kMAX_CIR_Par = 15;
//const int kMAX_CIR = 7;
//const int kMAX_RAINSWORD = 30;
const int kMAX_WAVE = 2;
class Boss {
	int bossAttackHP = 28;//ボスに攻撃当てた時のへるHP 

	float endT = 0.0f;
	float bossendT = 0.0f;
	float bossendTspeed ;
	float endTspeed;
public:
	bool EmitEffect = false;;
private:

	//画像の宣言
	int Rainsword_gra = 0;
	int Mahoujin_gra = 0;
	int Blade_gra = 0;
	int HoldBlade_gra = 0;
	int Tatsumaki_gra = 0;
	int UseBladeGra = Blade_gra;
	int ShockWave_gra=0;
	int HpBar_gra = 0;
	int CirPar_gra = 0;
	//音
	Sound sound;
	Sound::Effect effect;
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
	int HoldPlusY = 42;

	int HP = 2000;
	unsigned int HpColor = 0x00FF44FF;
	const int HalfHP = HP*0.3f;
	const int ThreeQuarterHP = HP * 0.6f;

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
		float t_back = 0;
		float t_back2=0;
		bool Back=0;
		Vec2 FPosBoss = {};
		int Delay = 0;
		float Boss_t = 0;
		float Boss_t2 = 0;
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
			Boss_t2 = 0;
			t_back2 = 0;
			Delay = 0;
		}
		Vec2 Vec_RotedPos;
		float Roted_t = 0;
		float Roted_tback = 0;
		

	};
	struct ShockWave {
		Quad QuadPos = { { 9999,9999 } , { 10000,9999 } , { 9999,10000 }, { 10000,10000 } };
		Quad Quad2Pos = { { 9999,9999 } , { 10000,9999 } , { 9999,10000 }, { 10000,10000 } };
		Quad QuadPosAnime = { { 9999,9999 } , { 10000,9999 } , { 9999,10000 }, { 10000,10000 } };
		Quad Quad2PosAnime = { { 9999,9999 } , { 10000,9999 } , { 9999,10000 }, { 10000,10000 } };
		/*Vec2 Pos = {};
		Vec2 Pos2 = {};*/
		float LifeTime = 0;
		bool WaveKeep = false;
		bool Reserve = true;
		int SrcX = 0;
		int AnimeFlame = 0;
		void Init() {
			LifeTime = 0;
			WaveKeep = false;
			Reserve = false;

		}

	}Wave[kMAX_WAVE];

	public:

	struct CircleOfDeath {
		Circle circle = { {0,0},0 };
		Quad Quad_Pos = {};
		float fRad = {};
		bool Set = false;
		bool Reserve = true;
		float Reserve_t = 0;
		float Feedt = 0.0f;
		void Init() {
			Set = false;
			Reserve = true;
			Reserve_t = 0;
			fRad = 0;
		}

	}Circleofdeath[kMAX_CIR];
	int Circleofdeath_flame;
	int Circleofdeath_flame2;
	int Circleofdeath_Expflame;
	bool isEmitwhite = false;
	bool isWhiteFeedout = false;
	bool isFeedCircelOfDeath = false;

	private:

	struct RainOfSword {
		Vec2 Pos= { 9999,9999 };
		Quad QuadPos = { {9999,9999},{10000,9999},{9999,10000},{10000,10000} };
		Quad ColQuadPos = { {9999,9999},{10000,9999},{9999,10000},{10000,10000} };
		bool Set = false;
		bool Reserve = false;
		int Width = 1;
		int Height = 1;
		int ColWidth = 1;
		int ColHeight = 1;
		float DownT = 0;
		float AddT = 0;
		float AddT2 = 0;
		float ColAddT = 0;
		float ColAddT2 = 0;

		void Init() {
			Pos = {9990,9990};
			 AddT2 = 0;

			Reserve = false;
			QuadPos = { {9999,9999},{10000,9999},{9999,10000},{10000,10000} };
			Set = false;
			DownT = 0;
			AddT = 0;
			Width = 1;
			Height = 1;
			ColWidth = 1;
			ColHeight = 1;
			ColAddT = 0;
			ColAddT2 = 0;
			ColQuadPos = { {9999,9999},{10000,9999},{9999,10000},{10000,10000} };
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
		float EaseDownT = 0;
		float EaseDownT2=0;
		Vec2 PlayerPosF;
		Vec2 PlayerPosF2;
		float Delay = 0;
		Vec2 F_Pos;
		bool Matched=false;
		bool Matched2 = false;
		void Init() {
			EaseT = 0;
			EaseDownT2 = 0;
			EaseDownT = 0; 
			EaseT2 = 0;
			Matched2 = false;
			Matched = false;
			PlayerPosF={};
			F_Pos={};
			PlayerPosF2 = {};
			Delay = 0;
		}
	};
	JumpAttack jumpattack;

	bool isBossHit = false; //攻撃を当てられた

	Vec2 BladeCenterPos;

	float BossMotionTime = 0;
	
#pragma region Parts
	struct ImageStruct {
		Vec2 ImagePos; //ボスの座標 + パーツの位置 +パーツ位置のズレ 初期設定は{0,0}でおｋ
		Vec2 ImageSize; // パーツのサイズ
		Vec2 PosMisal; //  !!!!値を変更しないで!!!! パーツの位置 この値をボスの中心座標に加算する
		Quad ImageQuad; // クアッドホッパーピンクとか追加されないかなぁ。ポイントセンサーとグレートバリアがいいなぁ。ホントはサメ使いたいけど
		Vec2 PulsPos; //パーツ位置のズレ、立ちで動かすときに使う
		Vec2 PulsPosSpeed;
		int StandMotionFlag;
		Vec2 MotionPos; 
		Vec2 ColSize; //当たり判定のサイズ
		Vec2 ColMisal; //当たり判定の位置
		Quad ColQuad; //当たり判定のクアッド
		Vec2 HitReaction;
		int SrcX;
		int AnimeFlame;
		Vec2 MoviePulsPos;
	};


	ImageStruct Head = {
		{0,0},
		{176,160},
		{10,155},
		{ { Head.ImagePos.x - Head.ImageSize.x / 2, Head.ImagePos.y + Head.ImageSize.y / 2},
		int(Head.ImageSize.x),int(Head.ImageSize.y) },
		{0,-2},
		{0,0.5},
		1,
		{0,0},
		{64,70},
		{2,-5},
		{ { Head.ImagePos.x - Head.ColMisal.x - Head.ColSize.x / 2, Head.ImagePos.y + Head.ColMisal.y + Head.ColSize.y / 2},
		int(Head.ColSize.x),int(Head.ColSize.y) },
		{0,0},
		0,
		0,
		{0,0}
	};

	ImageStruct Body = {
		{0,0},
		{144,164},
		{2,52},
		{ { Body.ImagePos.x - Body.ImageSize.x / 2, Body.ImagePos.y + Body.ImageSize.y / 2},
		int(Body.ImageSize.x),int(Body.ImageSize.y) },
		{0,0},
		{0,0.5},
		1,
		{0,0},
		{132,144},
		{5,-4},
		{ { Body.ImagePos.x - Body.ColMisal.x - Body.ColSize.x / 2, Body.ImagePos.y + Body.ColMisal.y + Body.ColSize.y / 2},
		int(Body.ColSize.x),int(Body.ColSize.y) },
		{0,0},
		0,
		0,
		{0,0}
	};

	ImageStruct Leg = {
		{0,0},
		{128,128},
		{-4,-59},
		{ { Leg.ImagePos.x - Leg.ImageSize.x / 2, Leg.ImagePos.y + Leg.ImageSize.y / 2},
		int(Leg.ImageSize.x),int(Leg.ImageSize.y) },
		{0,0},
		{0,0},
		1,
		{0,0},
		{96,106},
		{1,11},
		{ { Leg.ImagePos.x - Leg.ColMisal.x - Leg.ColSize.x / 2, Leg.ImagePos.y + Leg.ColMisal.y + Leg.ColSize.y / 2},
		int(Leg.ColSize.x),int(Leg.ColSize.y) },
		{0,0},
		0,
		0,
		{0,0}
	};

	ImageStruct RightArm = {
		{0,0},
		{52,116},
		{-94,-4},
		{ { RightArm.ImagePos.x - RightArm.ImageSize.x / 2, RightArm.ImagePos.y + RightArm.ImageSize.y / 2},
		int(RightArm.ImageSize.x),int(RightArm.ImageSize.y) },
		{0,-5},
		{0,0.5},
		1,
		{0,0},
		{38,74},
		{-3,-11},
		{ { RightArm.ImagePos.x - RightArm.ColMisal.x - RightArm.ColSize.x / 2, RightArm.ImagePos.y + RightArm.ColMisal.y + RightArm.ColSize.y / 2},
		int(RightArm.ColSize.x),int(RightArm.ColSize.y) },
		{0,0},
		0,
		0,
		{0,0}
	};

	ImageStruct LeftArm = {
		{0,0},
		{52,116},
		{86,-4},
		{ { LeftArm.ImagePos.x - LeftArm.ImageSize.x / 2, LeftArm.ImagePos.y + LeftArm.ImageSize.y / 2},
		int(LeftArm.ImageSize.x),int(LeftArm.ImageSize.y) },
		{0,-5},
		{0,0.5},
		1,
		{0,0},
		{38,74},
		{3,-11},
		{ { LeftArm.ImagePos.x - LeftArm.ColMisal.x - LeftArm.ColSize.x / 2, LeftArm.ImagePos.y + LeftArm.ColMisal.y + LeftArm.ColSize.y / 2},
		int(LeftArm.ColSize.x),int(LeftArm.ColSize.y) },
		{0,0},
		0,
		0,
		{0,0}
	};

	float ArmPosAngle = 2.8125;
	float ArmPosAngleSpeed = 2.8125;


	int MovieTime = 0;
	bool CanMove = true;
	bool MovieEnd = false;
	bool isImageDead = false;
	bool isRedBlackEffect = true;

	struct StyleChangeStruct {
		bool Flag = false;
		float Alpha = 0;
		int ScrX = 0;
		Vec2 ImageSize = { 256,1080 };
		Quad Quad;
		int Anime;
	};

	StyleChangeStruct StyleChange = {
		false,
		0,0,
		{384,1080},
		{ { Pos.x - StyleChange.ImageSize.x / 2, Pos.y - StyleChange.ImageSize.y + 190},
		int(StyleChange.ImageSize.x),int(StyleChange.ImageSize.y) },
		0
	};

	int NextBossTime = 0;

#pragma endregion

	float StepT = 0;
	int StepFPos = 0;
	bool bStep = 0;
	
	float CircleOfDeathMotionT;
	float CircleOfDeathMotionT2;
	void CircleOfDeathMotion(int type);
	float RainofswordMotionT;
	float RainofswordMotionT2;
	void RainOfSwordMotion(int type);

	bool bJumpAttack2 = false;
public:
	Boss();
	void Set();
	void Init();
	void Draw(Screen& screen,int texsture, int headtex, int bodytex, int legtex, int rightarm, int leftarm, int deadbody, int deadrightarm, int deadleftarm);
	void DrawStyleChange(Screen& screen, int StyleChangeGra);
	void UpDate();
	void State(PlayerMain& player);
	void KeepUP(PlayerMain& player);
	void KeepUpWaitBack(PlayerMain& player);
	void BackStep(PlayerMain& player);
	void DirectionGet(PlayerMain& player);
	void RandamMoveSelect(int rand,PlayerMain& player, Screen& screen);
	void RandMoveSet();
	int ReloadMove(int Movearry);
	void LoadGra();
	//スキル
	void AttackFunction01(Screen& screen);
	void NomalSwordAttack(PlayerMain& player);
	void NomalSwordAttack2(PlayerMain& player);
	void NomalSwordAttack3(PlayerMain& player);
	void NomalRotedSwordAttack(PlayerMain& player);
	void NomalRotedSwordAttack2(PlayerMain& player);
	void JumpAttack(PlayerMain& player,Screen& screen);
	void ShockWaveAttack(PlayerMain& player, Screen& screen);
	void ShockWaveAttack2(PlayerMain& player, Screen& screen);
	void ShockWaveAttackCenter(PlayerMain& player);

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

	int GetBossHP();
	float GetBossX() { return Pos.x; };
	Quad GetBossAttackQuad();
	Quad GetBossBladeQuad();
	Quad GetRainOfSwordQuad(int i);
	Circle GetCircleOfDeathQuad(int i);
	bool GetAction();
	bool GetSwordAttack();
	bool IsLife = true;
	
	void BossHit(bool Hit);

	enum {
		up,
		down,
		left,
		right
	};

	void BossHitReaction(Quad PlayerQuad, bool up, bool down, bool right);

	void BladeImageLink(Matrix2x2 mat);
	
	void StyleChangeUpdate(Screen& screen);

	void MovieInit();
	void Movie();
	bool MovieEnded();
	bool RedBlackEffectFlag();
	void StyleChangeFalse() { StyleChange.Flag = false; };
	bool GetstyleChange() { return StyleChange.Flag; }

	bool isBossDead();
};
