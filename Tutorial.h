#pragma once
#include"Screen.h"
#include"Vec2.h"
#include"Quad.h"
#include "Collision.h"


class Tutorial
{
private:

	struct LetJumpStruct {
		Vec2 Pos;
		Vec2 ColSize;
		Quad ColQuad;
		Vec2 ImageSize;
		Quad ImageQuad;
		int srcX;
		int Anime;
	};

	struct LetAttackStruct {
		Vec2 Pos;
		Vec2 ColSize;
		Quad ColQuad;
		Vec2 ImageSize;
		Quad ImageQuad;
		int srcX;
		int Anime;
		bool isHit;
	};

	struct LetDashStruct {
		Vec2 Pos;
		Vec2 ColSize;
		Quad ColQuad;
		Vec2 ImageSize;
		Quad ImageQuad;
		int srcX;
		int Anime;
	};

	LetJumpStruct LetJump = {
		{550,68},
		{136,136},
		{ { LetJump.Pos.x - LetJump.ColSize.x / 2 , LetJump.Pos.y + LetJump.ColSize.y / 2},
		int(LetJump.ColSize.x),int(LetJump.ColSize.y) },
		{48,48},
		{ { LetJump.Pos.x - LetJump.ImageSize.x / 2 , LetJump.Pos.y + LetJump.ImageSize.y / 2},
		int(LetJump.ImageSize.x),int(LetJump.ImageSize.y) },
		0,
		0,
	};

	LetAttackStruct LetAttack[2];

	LetDashStruct LetDash = {
		{1920,320 / 2},
		{72,320},
		{ { LetDash.Pos.x - LetDash.ColSize.x / 2 , LetDash.Pos.y + LetDash.ColSize.y / 2},
		int(LetDash.ColSize.x),int(LetDash.ColSize.y) },
		{48,48},
		{ { LetDash.Pos.x - LetDash.ImageSize.x / 2 , LetDash.Pos.y + LetDash.ImageSize.y / 2},
		int(LetDash.ImageSize.x),int(LetDash.ImageSize.y) },
		0,
		0,
	};

public:

	Tutorial();

	void Update();

	void Draw(Screen& screen);

	void HitLetAttack(Quad Target);

	bool PlayerGoNext(float PlayerPosX);

	Quad GetLetAttackQuad(int num) { return LetAttack[num].ColQuad; };

};

