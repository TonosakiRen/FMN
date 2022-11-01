#include "PlayerMain.h"
#include <Novice.h>
#include "Clamp.h"
#include "ControllerInput.h"
//#include "Key.h"

void PlayerMain::Move()
{
	

	Speed.x = 0;

	if (Controller::IsStickDirection(0,Controller::lsdRIGHT)) {
		Speed.x = 8;
	}
	if (Controller::IsStickDirection(0, Controller::lsdLEFT)) {
		Speed.x = -8;
	}

	if (Controller::IsPressedButton(0,Controller::bA) == 1) {
		if (CanJump == true && PreJumpKey == 1) {
			JumpFlag = true;
		}
	}

	if(Controller::IsReleaseButton(0, Controller::bA) == 1) {
		JumpFlag = false;
	}

	if (JumpFlag == true) {
		JumpTime++;
	}

	Speed.y = -0.7 * JumpTime;

	/*switch (JumpTime)
	{
	case 0:
		Speed.y = 0;
		break;
	case 1:
		Speed.y = -1.4;
		break;
	case 2:
		Speed.y = -1.6;
		break;
	case 3:
		Speed.y = -2;
		break;
	case 4:
		Speed.y = -2.4;
		break;
	case 5:
		Speed.y = -2.8;
		break;
	default:
		Speed.y = -3.2;
		break;
	}*/

	Speed.y = Clamp::clamp(Speed.y, -4.2, 0);
	
	OtherSpeed.y += 0.2;

	Pos.x += Speed.x ;
	Pos.y += (Speed.y + OtherSpeed.y )* G;

	Pos.y = Clamp::clamp(Pos.y, 0,FLOOR - HitBoxWide.y / 2);

	if (Pos.y >= FLOOR - HitBoxWide.y / 2) {
		Speed.y = 0;
		OtherSpeed.y = 0;
		JumpTime = 0;
		CanJump = true;
	}
	else {
		CanJump = false;
	}
	
	PreJumpKey = Controller::IsPressedButton(0, Controller::bA);

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

	Novice::ScreenPrintf(0, 0, "%d", JumpFlag);
	Novice::ScreenPrintf(0, 20, "%d", Controller::IsReleaseButton(0, Controller::bA));
	
}
