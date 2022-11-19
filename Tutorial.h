#pragma once
#include"Screen.h"
#include"Vec2.h"
#include"Quad.h"



class Tutorial
{
private:

	struct LetJumpStruct {
		Vec2 ColSize;
		Quad ColQuad;
		Vec2 ImageSize;
		Quad ImageQuad;
		Vec2 Pos;
	};

	LetJumpStruct LetJump = {
		{64,64},



	};

public:

	void Update();

	void Draw();

};

