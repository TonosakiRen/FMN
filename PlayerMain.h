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
	//Pos 位置
	Vec2 Pos = {100,500};

	//HitBoxWide 当たり判定の大きさ
	Vec2 PlayerHitBoxSize = { 32,48 };

	Quad PlayerQuad = {Pos,PlayerHitBoxSize.x,PlayerHitBoxSize.y};

	int AnimeFlame = 9;
	int SrcX;

	//Speed プレイヤーが動かすときに使う
	//OtherSpeed  その他要因で動かされる時に使う 重力、ノックバックなど
	Vec2 Speed = { 0,0 };
	Vec2 OtherSpeed = {0,0};

	//G 重力じゃ
	const float G = 9.8;
	
	//JumpTime ジャンプしてる間加算
	int JumpTime = 0;

	//JUMPPOWER ジャンプ力ぅ...ですかねぇ...
	float JUMPPOWER = 2;

	//JumpFlag ジャンプさせるフラグ Trueの間はSpeedにジャンプ力が入る
	//PreJumpKey 1F前のジャンプキー
	//CanJump ジャンプが可能かどうか
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

