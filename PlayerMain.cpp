#include "PlayerMain.h"
#include <Novice.h>
#include "Clamp.h"

void PlayerMain::Move()
{
	

	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	Speed.x = 0;

	if (keys[DIK_D] != 0 && keys[DIK_A] == 0) {
		Speed.x = 8;
	}
	if (keys[DIK_A] != 0 && keys[DIK_D] == 0) {
		Speed.x = -8;
	}

	if (keys[DIK_W] != 0) {
		if (CanJump == true && preKeys[DIK_W] == 0) {
			JumpFlag = true;
		}
	}
	else {
		JumpFlag = false;
	}

	if (JumpFlag == true) {
		Speed.y -= 3.5;
	}

	if (Speed.y <= -8) {
		JumpFlag = false;
	}

	Speed.y += 0.5;

	Speed.y = Clamp::clamp(Speed.y, -8,100);

	Pos.x += Speed.x ;
	Pos.y += Speed.y * G;

	Pos.y = Clamp::clamp(Pos.y, 0,FLOOR - HitBoxWide.y / 2);

	if (Pos.y >= FLOOR - HitBoxWide.y / 2) {
		Speed.y = 0;
		CanJump = true;
	}
	else {
		CanJump = false;
	}
	
}

void PlayerMain::Draw(int texture)
{
	Novice::DrawQuad(
		Pos.x - HitBoxWide.x / 2, Pos.y - HitBoxWide.y / 2,
		Pos.x + HitBoxWide.x / 2, Pos.y - HitBoxWide.y / 2,
		Pos.x - HitBoxWide.x / 2, Pos.y + HitBoxWide.y / 2,
		Pos.x + HitBoxWide.x / 2, Pos.y + HitBoxWide.y / 2,
		0, 0, 1, 1, texture, WHITE);

	Novice::DrawLine(0,FLOOR,1280,FLOOR,RED);

	Novice::ScreenPrintf(0, 0, "%d", preKeys[DIK_W]);
}
