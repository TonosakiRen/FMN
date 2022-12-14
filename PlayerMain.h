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
#include "Sound.h"
class PlayerMain
{
	private:
		
		int HitStop = 0;
		int Load = 0;
		int PlayerHpBar_gra = 0;

		Sound sound;

	//Pos 位置(中央だぜ)
	//HitBoxSize 当たり判定の大きさ
	struct GeneralStruct {
		Vec2 Pos;
		Vec2 HitBoxSize;
		Quad Quad;
		int AnimeFlame;
		int SrcX;
		unsigned int Color;
		Vec2 ImageSize;
		int ImageMisal;
	};
	
	//FaceRight プレイヤーがどっち向いてるか判別 false 左 : 右 true
	bool FaceRight = true;

	//FaceDown プレイヤーが下キーを入れてたらtrue 離したらfalse 左右とは挙動が違うよ
	bool FaceDown = false;
	//FaceUp プレイヤーが上キーを入れてたらtrue 離したらfalse 左右とは挙動が違うよ
	bool FaceUp = false;

	GeneralStruct Player = {
		{300,0},
		{ 40,70 },
		{ {Player.Pos.x - Player.HitBoxSize.x / 2, Player.Pos.y + Player.HitBoxSize.y / 2},
		int(Player.HitBoxSize.x),int(Player.HitBoxSize.y)},
		9,
		0,
		WHITE,
		{ 108,108 },
		int(Player.HitBoxSize.y - Player.ImageSize.y) / 2,
	};

	int MaxHp = 12;
	int HP = MaxHp;
	

	//Speed プレイヤーが動かすときに使う
	Vec2 Speed = { 0,0 };
	//OtherSpeed  その他要因で動かされる時に使う ノックバックなど
	Vec2 OtherSpeed = {0,0};

	Vec2 HitBack = { 0,0 };

	float Gravity = 0;

	//G 重力じゃ
	const float G = 9.8;
	
	//JumpTime ジャンプしてる間加算
	int JumpTime = 0;

	//JUMPPOWER ジャンプ力ぅ...ですかねぇ...
	float JUMPPOWER = 1.7;

	//JumpFlag ジャンプさせるフラグ Trueの間はSpeedにジャンプ力が入る
	bool JumpFlag = false;
	//PreJumpKey 1F前のジャンプキー
	bool PreJumpKey = false;
	//CanJump ジャンプが可能かどうか
	bool CanJump = false;

	bool DashFlag = false;
	int DashTime = 0;
	const int DASHSPEED = 24;
	const int MAXDASHTIME = 7;
	int DashCoolTime = 30;
	bool DashFaseRight = true;
	bool DashAvoid = false;
	
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

	//HitCoolDown 要は無敵時間じゃ
	int HitCoolDown = 0;
	const int HITCOOLDOWNMAX = 90;

	int AttackCoolDown = 0;
	int ATTACKCOOLDOWNMAX = 20;

	int isAttack = 0;
	bool isSwordAppear = 0;
	bool isSaveSwordHit = 0;

	Quad hitAttackPos = { {0,0}, 0,0};
	int attackstarttime = -1;
	bool isSwordHit = false;
	bool isGetSwordDirection = false;
	int swordDrawFrame = 0;
	int subSwordDrawNum[3];
	int CurrentSubSwordDrawNum = 0;
	int isSwordHitFace = 0;
	int switchSwordFrame = 1;
	int swordSheets = 5;
	int swordsrcX = 0;
	int swordAnimationFrame = 0;

	bool gameoverflag = false;

	enum {
		stand,
		walk,
		dash,
		jump,
		fall,
		attack,
		death,
	};

	int PlayerAnimeMode = 0;

	int MovieTime = 0;

	Vec2 MovieSpeed = { 0,0 };
	bool CanMove = true;
	float PulsScroll = 0;

	float GameOverTX = 0;
	float GameOverTY = 0;

public:

	Quad GetPlayerQuad()
	{
		return Quad(Player.Quad);
	}

	Vec2 GetPlayerPos()
	{
		return Vec2(Player.Pos);
	}

	void SetPlayerPos(Vec2 pos)
	{
		Player.Pos = pos;
	}

	Quad GetSwordQuad()
	{
		return Quad(Sword.Quad);
	}

	int HitStopOver() {
		int a = 0;
		if (HitStop > 0) {
			a = HitStop;
			HitStop = 0;
		}
		return a;
	}

	void Init();

	void Move();

	void NormalAttack();

	void SwordHit(Quad Target);

	Quad GetHitAttackPos() { return hitAttackPos; }

	bool GetHitSword() { return isSwordHit; }

	void PlayerHit(Quad Target);
	void PlayerHit(Circle Target);

	void PlayerHitKnockBack(Quad Target);

	bool GetisFaceRigh() { return FaceRight; }
	bool GetisFaceUp() { return FaceUp; }
	bool GetisFaceDown() { return FaceDown; }

	void Draw(Screen& screen, int stand, int walk, int dash, int jump,int fall,int attack, int death);
	void BladeDraw(Screen& screen, int mainbladeImg, int upmainbaldeImg, int downmainbladeImg, int upsubbladeImg, int downsubbladeImg, int* subbladeImg, int color, BlendMode mode);
	Vec2 Translation();

	void MovieInit() { MovieTime = 0; };
	void Movie();

	float ReturnPulsScroll() { return PulsScroll; }
	bool Returngameoverflag();

	void PauseLag();

	void GameOver(Screen& screen);
};

