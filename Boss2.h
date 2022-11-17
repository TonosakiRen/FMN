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

class Boss2 {

	//�摜�̐錾
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


	int load = 0;//�摜�ǂݗ���
	
	struct Keep {
		int Time = 0;
		int rand = 0;
	}keep;
	//�X�E�B�b�`
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
	//�z��̕ϐ�
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

	
	

	bool isBossHit = false; //�U���𓖂Ă�ꂽ

	Vec2 BladeCenterPos;

	float BossMotionTime = 0;

	public:
	bool isCenterOfDarkness = 0;
	Effect2 centerOfDarknessLeft;
	Effect2 centerOfDarknessRight;
	Effect2 centerOfDarknessUnder;


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
	//�X�L��
	


	//�X�L���o�������ǂ����F�F���ɏo�����ς����
	

	//�h���X�L��::�s�����I����Ă��o������I�Ȃ���
	

	Quad GetBossQuad(int BossParts);

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
