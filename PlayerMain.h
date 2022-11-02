#pragma once
#include "Vec2.h"
#include <Novice.h>
#include "Clamp.h"
#include "ControllerInput.h"
#include "Key.h"
#include "Screen.h"
#include "Quad.h"

class PlayerMain
{
	//Pos �ʒu
	Vec2 Pos = {100,500};

	//HitBoxWide �����蔻��̑傫��
	Vec2 PlayerHitBoxSize = { 32,48 };

	Quad PlayerQuad = {Pos,PlayerHitBoxSize.x,PlayerHitBoxSize.y};

	int AnimeFlame = 9;
	int SrcX;

	//Speed �v���C���[���������Ƃ��Ɏg��
	//OtherSpeed  ���̑��v���œ�������鎞�Ɏg�� �d�́A�m�b�N�o�b�N�Ȃ�
	Vec2 Speed = { 0,0 };
	Vec2 OtherSpeed = {0,0};

	//G �d�͂���
	const float G = 9.8;
	
	//JumpTime �W�����v���Ă�ԉ��Z
	int JumpTime = 0;

	//JUMPPOWER �W�����v�͂�...�ł����˂�...
	float JUMPPOWER = 2;

	//JumpFlag �W�����v������t���O True�̊Ԃ�Speed�ɃW�����v�͂�����
	//PreJumpKey 1F�O�̃W�����v�L�[
	//CanJump �W�����v���\���ǂ���
	bool JumpFlag = false;
	bool PreJumpKey = false;
	bool CanJump = false;

	//Vec2  = {};
	Vec2 AttackHitBox = {};



	const int FLOOR = 0;

public:
	void Move();
	

	void NormalAttack();

	void Draw(Screen& screen,int texture);
	Vec2 Translation();
};

