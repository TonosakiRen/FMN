#pragma once
#include<Novice.h>
#include "Vec2.h"
#include "Clamp.h"
#include "Quad.h"
#include"Screen.h"


class Boss {
	Vec2 Pos;
	Quad Quad_Pos;
	Vec2 Size;
	Vec2 LeftTop;
	Vec2 RightTop;
	Vec2 LeftBottom;
	Vec2 RightBottom;

	int AnimeFlame=9;
	int SrcX;

	float testnum = 9.0f;

public:
	Boss();
	void Set();
	void Draw(Screen& screen);

	void testfunc();
	
	Quad Get();

	float testget();
};
