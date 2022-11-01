#pragma once
#include "Vec2.h"

class PlayerMain
{

	Vec2 Pos = {100,100};
	Vec2 Speed = { 0,0 };
	Vec2 OtherSpeed = {0,0};
	Vec2 HitBoxWide = { 32,48 };
	const float G = 9.8;
	bool JumpFlag = false;
	bool PreJumpKey = false;
	bool CanJump = false;

	const int FLOOR = 620;

public:
	void Move();

	void Draw(int texture);
};

