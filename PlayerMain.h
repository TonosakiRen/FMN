#pragma once
#include "Vec2.h"
#include <Novice.h>
#include "Clamp.h"
#include "ControllerInput.h"
#include "Collision.h"
#include "Key.h"
#include "Screen.h"
#include "Quad.h"
#include "Stopper.h"

class PlayerMain
{
	private:
		
		int HitStop = 0;

	//Pos �ʒu(��������)
	//HitBoxSize �����蔻��̑傫��
	struct GeneralStruct {
		Vec2 Pos;
		Vec2 HitBoxSize;
		Quad Quad;
		int AnimeFlame;
		int SrcX;
		unsigned int Color;
	};
	
	//FaceRight �v���C���[���ǂ��������Ă邩���� false �� : �E true
	bool FaceRight = true;

	//FaceDown �v���C���[�����L�[�����Ă���true ��������false ���E�Ƃ͋������Ⴄ��
	bool FaceDown = false;
	//FaceUp �v���C���[����L�[�����Ă���true ��������false ���E�Ƃ͋������Ⴄ��
	bool FaceUp = false;

	GeneralStruct Player = {
		{100,500},
		{ 60,96 },
		{ {Player.Pos.x - Player.HitBoxSize.x / 2, Player.Pos.y + Player.HitBoxSize.y / 2},
		int(Player.HitBoxSize.x),int(Player.HitBoxSize.y)},
		9,
		0,
		WHITE,
	};

	//Speed �v���C���[���������Ƃ��Ɏg��
	Vec2 Speed = { 0,0 };
	//OtherSpeed  ���̑��v���œ�������鎞�Ɏg�� �m�b�N�o�b�N�Ȃ�
	Vec2 OtherSpeed = {0,0};

	Vec2 HitBack = { 0,0 };

	float Gravity = 0;

	//G �d�͂���
	const float G = 9.8;
	
	//JumpTime �W�����v���Ă�ԉ��Z
	int JumpTime = 0;

	//JUMPPOWER �W�����v�͂�...�ł����˂�...
	float JUMPPOWER = 2.3;

	//JumpFlag �W�����v������t���O True�̊Ԃ�Speed�ɃW�����v�͂�����
	bool JumpFlag = false;
	//PreJumpKey 1F�O�̃W�����v�L�[
	bool PreJumpKey = false;
	//CanJump �W�����v���\���ǂ���
	bool CanJump = false;

	bool DashFlag = false;
	int DashTime = 0;
	const int DASHSPEED = 34;
	int DashCoolTime = 20;
	bool DashFaseRight = true;
	
	GeneralStruct Sword = {
		{9999,9999},
		{48,256},
		{ {Sword.Pos.x - Sword.HitBoxSize.x / 2, Sword.Pos.y - Sword.HitBoxSize.y / 2},
		int(Sword.HitBoxSize.x),int(Sword.HitBoxSize.y) },
		9,
		0,
		WHITE
	};

	const int FLOOR = 0;

	Vec2 HitRatio = {0,0};

	int HitCoolDown = 0;

	Quad hitAttackPos = { {0,0}, 0,0};
	bool isSwordHit = false;

public:

	Quad GetPlayerQuad()
	{
		return Quad(Player.Quad);
	}

	int HitStopOver() {
		int a = 0;
		if (HitStop > 0) {
			a = HitStop;
			HitStop = 0;
		}
		return a;
	}

	void Move();

	void NormalAttack();

	void SwordHit(Quad Target);

	Quad GetHitAttackPos() { return hitAttackPos; }

	bool GetHitSword() { return isSwordHit; }

	void PlayerHit(Quad Target, Screen& screen);

	bool GetisFaceRigh() { return FaceRight; }
	bool GetisFaceUp() { return FaceUp; }
	bool GetisFaceDown() { return FaceDown; }

	void Draw(Screen& screen,int texture);
	Vec2 Translation();
};

