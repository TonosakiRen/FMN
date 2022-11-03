#pragma once
#include "Vec2.h"
#include <Novice.h>
#include "Clamp.h"
#include "ControllerInput.h"
#include "Collision.h"
#include "Key.h"
#include "Screen.h"
#include "Quad.h"


class PlayerMain
{
	private:
	//Pos �ʒu(��������)
	//HitBoxSize �����蔻��̑傫��
	struct GeneralStruct {
		Vec2 Pos;
		Vec2 HitBoxSize;
		Quad Quad;
		int AnimeFlame;
		int SrcX;
	};
	
	//FaceRight �v���C���[���ǂ��������Ă邩���� false �� : �E true
	bool FaceRight = true;

	//FaceDown �v���C���[�����L�[�����Ă���true ��������false ���E�Ƃ͋������Ⴄ��
	bool FaceDown = false;
	//FaceUp �v���C���[����L�[�����Ă���true ��������false ���E�Ƃ͋������Ⴄ��
	bool FaceUp = false;

	GeneralStruct Player = {
		{100,500},
		{ 32,48 },
		{ {Player.Pos.x - Player.HitBoxSize.x / 2, Player.Pos.y + Player.HitBoxSize.y / 2},
		int(Player.HitBoxSize.x),int(Player.HitBoxSize.y)},
		9,
		0,
	};

	//Speed �v���C���[���������Ƃ��Ɏg��
	Vec2 Speed = { 0,0 };
	//OtherSpeed  ���̑��v���œ�������鎞�Ɏg�� �d�́A�m�b�N�o�b�N�Ȃ�
	Vec2 OtherSpeed = {0,0};

	//G �d�͂���
	const float G = 9.8;
	
	//JumpTime �W�����v���Ă�ԉ��Z
	int JumpTime = 0;

	//JUMPPOWER �W�����v�͂�...�ł����˂�...
	float JUMPPOWER = 2;

	//JumpFlag �W�����v������t���O True�̊Ԃ�Speed�ɃW�����v�͂�����
	bool JumpFlag = false;
	//PreJumpKey 1F�O�̃W�����v�L�[
	bool PreJumpKey = false;
	//CanJump �W�����v���\���ǂ���
	bool CanJump = false;

	bool DashFlag = false;
	int DashTime = 0;
	int DashCoolTime = 20;
	bool DashFaseRight = true;
	
	GeneralStruct Sword = {
		{9999,9999},
		{48,256},
		{ {Sword.Pos.x - Sword.HitBoxSize.x / 2, Sword.Pos.y - Sword.HitBoxSize.y / 2},
		int(Sword.HitBoxSize.x),int(Sword.HitBoxSize.y) },
		9,
		0,
	};

	const int FLOOR = 0;

public:
	void Move();

	void NormalAttack();

	void SwordHit(Quad Target);

	void Draw(Screen& screen,int texture);
};

