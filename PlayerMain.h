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
	//Pos 位置(中央だぜ)
	//HitBoxSize 当たり判定の大きさ
	struct GeneralStruct {
		Vec2 Pos;
		Vec2 HitBoxSize;
		Quad Quad;
		int AnimeFlame;
		int SrcX;
	};
	
	//FaceRight プレイヤーがどっち向いてるか判別 false 左 : 右 true
	bool FaceRight = true;

	//FaceDown プレイヤーが下キーを入れてたらtrue 離したらfalse 左右とは挙動が違うよ
	//FaceUp プレイヤーが上キーを入れてたらtrue 離したらfalse 左右とは挙動が違うよ
	bool FaceDown = false;
	bool FaceUp = false;

	GeneralStruct Player = {
		{100,500},
		{ 32,48 },
		{ {Player.Pos.x - Player.HitBoxSize.x / 2, Player.Pos.y - Player.HitBoxSize.y / 2},
		int(Player.HitBoxSize.x),int(Player.HitBoxSize.y)},
		9,
		0,
	};

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

	void Draw(Screen& screen,int texture);
	Vec2 Translation();
};

