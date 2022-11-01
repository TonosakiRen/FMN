#pragma once
#include "Vec2.h"


class PlayerMain
{
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vec2 Pos = {100,100};
	Vec2 Speed = { 0,0 };
	Vec2 HitBoxWide = { 32,48 };
	const int G = 3;
	bool JumpFlag = false;
	bool CanJump = false;

	const int FLOOR = 620;

public:
	void Move();

	void Draw(int texture);
};

