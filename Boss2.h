#pragma once
#include<Novice.h>
#include "Vec2.h"
#include "Quad.h"
#include"Screen.h"
#include"PlayerMain.h"
#include"Circle.h"
#include "Effect2.h"
#include "Effect3.h"
#include "Effect4.h"
#include "Sound.h"

//const int MAX_PATTERN= 100;
//const int kMAX_CIR = 7;
//const int kMAX_RAINSWORD = 30;
//const int kMAX_WAVE = 2;
const int MAX2_PATTERN = 100;
const int Max_Zan = 20;
//BulletAttck
const int swordNum = 20;
//UndertaleAttack
const int chaseBulletNum = 5;
const int savechaseframe = 3;
const int rotateBulletNum = 20;
const int saveUndertaleFrame = 900;
//nyokkiAttack
const int nyokkiNum = 30;
//Asgore
const int allBulletNum = 1000;
const int BulletOriginNum = 20;
const int EmitNum = 20;
const int EmitCoolTime = 20;
const int saveEmitActionNum = 16;


class Boss2 {

	bool isCollisionWall = false;

	int bossAttackHP = 33;//ボスに攻撃当てた時のへるHP 
	//画像の宣言
	int Rainsword_gra = 0;
	int Mahoujin_gra = 0;
	int Blade_gra = 0;
	int HoldBlade_gra = 0;
	int UseBladeGra = Blade_gra;
	int Boss2HpBar_gra = 0;

	Sound sound;

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

	Vec2 ImageSize;
	Quad ImageQuad;
	
	float HP = 1800.0f;
	
	const int MAXHP = 1800;
	const int HalfHP = HP * 0.3f;
	const int ThreeQuarterHP = HP * 0.6f;
	unsigned int HpColor = 0x00FF44FF;
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
		Vec2 Size = { 88,184 };
		int sheets = 4;
		int LifeTime = 0;
		bool bSet = 0;
		int Gra;
		int SrcX;
		int AnimeFlame = 0;
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

	//CenterofDarkness

		float gravityT = 0.0f;

	float centerOfDarknessMoveT = 0;
	bool isCenteroOfDarknessMove = true;
	bool isCenterOfDarkness = 0;
	bool isGetPos = false;
	float saveBoss2x;
	float savePlayerx;
	Effect2 centerOfDarknessLeft;
	Effect2 centerOfDarknessRight;
	Effect2 centerOfDarknessUnder;
	Effect2 centerOfDarknessUnderLeft;
	Effect2 centerOfDarknessUnderRight;
	float gravityPower = 6.0f;
	int saveCenterOfDarknessCooltime = 1000;
	int centerOfDarknessCooltime = 1000;

	bool isGetcenterNyokki = false;
	Quad centerNyokki[3];
	int centerNyokkiUpSrcX[3];
	int centerNyokkiKeepSrcX[3];
	float centerNyokkiT[3];
	int centerNyokkiUpSheets = 13;
	int centerNyokkiKeepSheets = 3;
	int centerNyokkiUpAnimationFrame = 0;
	int centerNyokkiKeepAnimationFrame = 0;
	int centerNyokkiSwitchAnimationFrame = 4;
	bool iscenterNyokki = false;
	int centerNyokkiWidth = 108;
	int centerNyokkiHeight = SCREEN_HEIGHT - Floor;
	int centerNyokkispace = 50;
	bool iscenterNyokkiCollision = false;
	bool isFeedCenterNyokki = false;


	//BulletAttack
	
	Quad initialSword = {Pos,30,30,};
	Quad effectSword[swordNum];
	Quad sword[swordNum];
	bool isBulletAttack = false;
	float radius = 200.0f;
	float mostRadius = 2000.0f;
	float theta[swordNum];
	bool isSword[swordNum];
	unsigned int orbitColor[swordNum];
	bool isRelease = false;
	bool getFrag[swordNum];
	Effect3 swordEffect;
	float swordT[swordNum] ;
	const int saveBulletAttackCoolTime = 2000;
	int bulletAttackCoolTime = saveBulletAttackCoolTime;
	bool isOrbit[swordNum] ;

	//undertale



	bool isUndertaleAttack = false;
	float xMove = 0;
	float xSpeed = 1;
	float yMove = 0;
	float ytheta = 0;
	float ythetaSpeed = M_PI / 30;
	Vec2 savePlayerPos;
	Quad initialRotateBullet;
	Quad rotateBullet[rotateBulletNum];
	Quad bullet[rotateBulletNum];
	float bulletRadius = 500;
	float rotatetheta[rotateBulletNum];
	float rotatethetaSpeed = M_PI / 35.0f;
	bool isRotateBullet[rotateBulletNum];
	bool isRotateBullet2[rotateBulletNum];
	float rotateT;
	float upCircleY = 0;
	float wideMostMove = 100;

	float undertaleMoveT = 0.0f;
	Vec2 saveUndertalePos;

	Effect4 chaseEffect;
	int chaseframe[chaseBulletNum];
	Vec2 leftVec[chaseBulletNum];
	Vec2 rightVec[chaseBulletNum];
	Vec2 chaseVec[chaseBulletNum];
	float chaseTheta = 5.0f * M_PI / 180;
	bool isGet[chaseBulletNum];
	Vec2 playerToEffect[chaseBulletNum];
	bool isFeedrotateBullet = false;
	float rotateBulletT[rotateBulletNum];
	bool emitchaseEffect = true;
	bool isUndertaleCollision = false;
	
	Vec2 UndertalePos;

	int undertaleFrame = saveUndertaleFrame;

	//nyokki
	float  saveBossY;
	float  saveBossY2;
	float  saveUnderBossY;
	float underPos = 92.0f;
	float dropT = 0.0f;
	bool isSaveBossY = false;
	bool isSaveBossY2 = false;
	bool isSaveBossY3 = false;
	float upSpeed = 0.02;
	float dropSpeed = 0.02;
	bool isdropMove = false;
	bool isdrop = false;
	float dropMoveT = 0.0f;
	float returnMoveT = 0.0f;
	float upDropMove = 70;
	bool isNyokki = false;
	bool isreturn = false;
	int leftNyokkiUpSrcX[nyokkiNum / 2];
	int leftNyokkiKeepSrcX[nyokkiNum / 2];
	int rightNyokkiUpSrcX[nyokkiNum / 2];
	int rightNyokkiKeepSrcX[nyokkiNum / 2];
	int nyokkiUpSheets = 13;
	int nyokkiKeepSheets = 3;
	int nyokkiUpAnimationFrame = 0;
	int nyokkiKeepAnimationFrame = 0;
	int nyokkiSwitchAnimationFrame = 4;
	int CollisionHeight = 0;
	float space = 80;
	float leftInitial = Pos.x - 54 - 108;
	float rightInitial = Pos.x + 54;
	int nyokkiWidth = 108;
	int nyokkiHeight = SCREEN_HEIGHT - Floor;
	bool isNyokkiCollsion = false;

	bool isFeedNyokki = false;

	float leftNyokkiT[nyokkiNum / 2];
	float rightNyokkiT[nyokkiNum / 2];

	bool isGetNyokkiPos = false;

	enum NyokkiStats {
		Up,
		Keep
	};

	NyokkiStats nyokkistats = Up;
	NyokkiStats centerNyokkistats = Up;
	
	struct Nyokki {
		Quad Quad;
	};

	Nyokki leftNyokki[nyokkiNum / 2];
	Nyokki rightNyokki[nyokkiNum / 2];

	//AsgoreAttack
	Vec2 EmitPos = { 0.0f,SCREEN_HEIGHT - Floor };
	float distanceSpeed = 6.0f;
	Vec2 allSpeed = { 2.0f,-1.0f };
	Vec2 distance[BulletOriginNum];
	struct Bullet {
		Quad quad;
		bool isBullet;
		Vec2 distance;
		float t;
	};
	Bullet AsgoreBullet[allBulletNum];
	int coolTime = 0;
	float AsgoreTheta = 2 * M_PI / BulletOriginNum;
	int emitNum = 0;
	int Asgorewidth = 30;
	int emitActionNum = saveEmitActionNum;

	bool isMoveCenter = false;
	bool isGetAsgore = false;
	Vec2 savePosAsgore;
	float AsgoreMoveTx = 0.0f;
	float AsgoreMoveTy = 0.0f;
	bool isAsgoreCollision = false;

	bool isAsgoreAttack = false;
	int saveWaitTime = 60;
	bool isWait = false;
	int waitTime = saveWaitTime;
	bool isAsgoreFeed = false;
	bool isGetPosRetrun = false;
	Vec2 savePosreturn;
	float AsgoreReturnTx = 0.0f;
	float AsgoreReturnTy = 0.0f;
	bool setWhich = false;

	//moveAttack
	Quad moveBullet[4];
	Quad movemoveBullet[16];
	bool ismoveBullet[4];
	bool ismoveBullet2[4];
	bool ismovemoveBullet[16];
	float movetheta[4];
	float movemovetheta[16];
	float moveradius = 450.0f;
	float movemoveradius = 80.0f;

	float moveAttackBulletFeedinT[16];
	float movemoveAttackBulletFeedinT[16];


	
	float moveAttackBulletFeedoutT[4];
	float movemoveAttackBulletFeedoutT[16];
	bool moveIsFeedout = false;

	float movethetaSpeed = 1.75f * M_PI / 180.0f;
	float movemovethetaSpeed = 8.0f * M_PI / 180.0f;

	Quad initialmoveBullet;
	Quad initialmovemoveBullet;

	bool ismoveMoveAttack = false;
	bool issavePosMoveAttack;
	Vec2 savePosMoveAttack;
	float moveMoveAttackTx = 0.0f;
	float moveAttackSpeed = 5.0f;
	bool ismovexMoveAttack = false;

	float LastPosx = 2100.0f;
	float startPosx;
	bool iswhichlr = false;

	//Teleportaitoni
	Vec2 TeleSavePos;
	Vec2 TeleportPos;
	bool GetTeleportPos = false;
	bool isTeleport = false;
	float TeleportTx = 0.0f;
	bool isTelechaseFeed = false;
	Effect4 TelechaseEffect;
	int Telechaseframe[chaseBulletNum];
	Vec2 TeleleftVec[chaseBulletNum];
	Vec2 TelerightVec[chaseBulletNum];
	Vec2 TelechaseVec[chaseBulletNum];
	float TelechaseTheta = 5.0f * M_PI / 180;
	bool TeleisGet[chaseBulletNum];
	Vec2 TeleplayerToEffect[chaseBulletNum];
	bool TeleisFeedrotateBullet = false;
	int TeleportNum = 3;
	int TeleChaceFrame = 120;
	int savedelayframe = 40;
	int delayframe = savedelayframe;
	

	int sheets = 4;
	int SrcX = 0;
	int AnimeFlame = 0;
	int colanime = 0;
	int colSrcX = 0;



	

	enum {
		Normal,
		Nyokki1,
		Nyokki2,
		Nyokki3,
		Charge
	};

	int AnimeSelect = Normal;

	//�摜
	int Boss_gra = 0;
	int BossNormal_gra = 0;
	int BossNyokki1_gra = 0;
	int BossNyokki2_gra = 0;
	int BossNyokki3_gra = 0;
	int BossCharge_gra = 0;

	int Bosspregra = 0;

public:

	bool BossDeathFlag = false;
	bool isGameClear = false;

	Boss2();
	void Init();
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
	void LoadGra();
	//スキル
	void CenterOfDarknessAttack(PlayerMain& player);
	void BulletAttack(PlayerMain& player);//自分の周りに出して放つ
	void UndertaleAttack(PlayerMain& player);//ハムスターのやつ
	void nyokkiAttack(PlayerMain& player);//台風が下から出てくるやつ
	void AsgoreAttack(PlayerMain& player);//上から円状にいっぱい㋐放つ
	void MoveAttack(PlayerMain& player);//四つの弾が回りながら横移動（ソウルのやつ）
	void Teleportation(PlayerMain& player);

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

	void PosLink(float posx);

	void Animation();

};
