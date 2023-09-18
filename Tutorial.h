#pragma once
#include"Screen.h"
#include"Vec2.h"
#include"Quad.h"
#include "Collision.h"
#include <Novice.h>
#include "Sound.h"
#include "ControllerInput.h"
#include "Key.h"
class Tutorial
{
private:
	Sound sound;
	struct LetJumpStruct {
		Vec2 Pos;
		Vec2 ColSize;
		Quad ColQuad;
		Vec2 ImageSize;
		Quad ImageQuad;
		int srcX;
		int Anime;
		bool isGet;
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
		bool isSet;
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

	/*LetJumpStruct LetJump = {
		{550,68},
		{64,64},
		{ { LetJump.Pos.x - LetJump.ColSize.x / 2 , LetJump.Pos.y + LetJump.ColSize.y / 2},
		int(LetJump.ColSize.x),int(LetJump.ColSize.y) },
		{168,168},
		{ { LetJump.Pos.x - LetJump.ImageSize.x / 2 , LetJump.Pos.y + LetJump.ImageSize.y / 2},
		int(LetJump.ImageSize.x),int(LetJump.ImageSize.y) },
		0,
		1,
	};*/

	LetJumpStruct LetJump[2];
	LetAttackStruct LetAttack[2];

	LetDashStruct LetDash = {
		{1920,320 / 2 - 80},
		{72,320},
		{ { LetDash.Pos.x - LetDash.ColSize.x / 2 , LetDash.Pos.y + LetDash.ColSize.y / 2},
		int(LetDash.ColSize.x),int(LetDash.ColSize.y) },
		{120,368},
		{ { LetDash.Pos.x - LetDash.ImageSize.x / 2 , LetDash.Pos.y + LetDash.ImageSize.y / 2},
		int(LetDash.ImageSize.x),int(LetDash.ImageSize.y) },
		0,
		0,
	};

	struct TutorialImageStruct {
		Vec2 Pos;
		Vec2 Size;
		Quad Quad;
		int sheets;
		int SrcX;
		int Anime;
		int Alpha;
	};

	TutorialImageStruct type1 = {
		{1040,465},
		{880,660},
		{ { type1.Pos.x - type1.Size.x / 2 , type1.Pos.y + type1.Size.y / 2},
		int(type1.Size.x),int(type1.Size.y) },
		2,
		0,
		1,
		255,
	};

	TutorialImageStruct type2 = {
		{1040,465},
		{880,660},
		{ { type2.Pos.x - type2.Size.x / 2 , type2.Pos.y + type2.Size.y / 2},
		int(type2.Size.x),int(type2.Size.y) },
		2,
		0,
		1,
		255,
	};

	TutorialImageStruct type3 = {
		{1040,465},
		{880,660},
		{ { type3.Pos.x - type3.Size.x / 2 , type3.Pos.y + type3.Size.y / 2},
		int(type3.Size.x),int(type3.Size.y) },
		2,
		0,
		1,
		255,
	};


	TutorialImageStruct type4 = {
		{1040,465},
		{880,660},
		{ { type4.Pos.x - type4.Size.x / 2 , type4.Pos.y + type4.Size.y / 2},
		int(type4.Size.x),int(type4.Size.y) },
		1,
		0,
		1,
		255,
	};

	TutorialImageStruct Back = {
		{1040,465},
		{880,660},
		{ { Back.Pos.x - Back.Size.x / 2 , Back.Pos.y + Back.Size.y / 2},
		int(Back.Size.x),int(Back.Size.y) },
		1,
		0,
		1,
		255,
	};

	bool LetAttackFlag = false;
	bool LetDashFlag = false;

	int tutorialNum = 0;
	int dashCount = 0;
	int attackCount = 0;
public:

	Tutorial();

	void Init();

	void Update(float PlayerX);

	void Draw(Screen& screen,int gra1,int gra2,int gra3,int gra4, int graB,int LetJumpGra,int LetAttackGra,int LetDashGra);

	void PlayDrawEx(int gra,int type);

	void HitLetAttack(Quad Target);

	void HitCoin(Quad Target);

	bool PlayerGoNext(float PlayerPosX);

	Quad GetLetAttackQuad(int num) { return LetAttack[num].ColQuad; };

	Quad GetLetJumpQuad(int num) { return LetJump[num].ColQuad; };

	Quad GetLetDashQuad() { return LetDash.ColQuad; };

};

