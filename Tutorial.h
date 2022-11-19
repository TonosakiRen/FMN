#pragma once
#include"Screen.h"
#include"Vec2.h"
#include"Quad.h"



class Tutorial
{
private:

	struct LetJumpStruct {
		Vec2 Pos;
		Vec2 ColSize;
		Quad ColQuad;
		Vec2 ImageSize;
		Quad ImageQuad;
	};

	LetJumpStruct LetJump = {
		{0,32},
		{64,64},
		{ { LetJump.Pos.x - LetJump.ColSize.x / 2 , LetJump.Pos.y + LetJump.ColSize.y / 2},
		int(LetJump.ColSize.x),int(LetJump.ColSize.y) },
		{48,48},
		{ { LetJump.Pos.x - LetJump.ImageSize.x / 2 , LetJump.Pos.y + LetJump.ImageSize.y / 2},
		int(LetJump.ImageSize.x),int(LetJump.ImageSize.y) },
	};

public:

	void Update();

	void Draw(Screen& screen);

};

