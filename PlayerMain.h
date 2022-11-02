#pragma once
#include "Vec2.h"
#include <Novice.h>
#include "Clamp.h"
#include "ControllerInput.h"
#include "Key.h"
#include "Screen.h"
class PlayerMain
{

	Vec2 Pos = {100,500};
	Vec2 Speed = { 0,0 };
	Vec2 OtherSpeed = {0,0};
	Vec2 HitBoxWide = { 32,48 };
	const float G = 9.8;
	int JumpTime = 0;
	float JumpPower = 2;
	bool JumpFlag = false;
	bool PreJumpKey = false;
	bool CanJump = false;

	const int FLOOR = 0;

public:
	void Move();

	void Draw(Screen& screen,int texture);
};

