#include "Stopper.h"
#include "Screen.h"

bool Stopper::Pause()
{
	if (Key::IsTrigger(DIK_P)) {
		if (isPause == true) {
			isPause = false;
		}
		else {
			isPause = true;
		}
	}
	return isPause;
}



void Stopper::HitStopMake(int StopFlame)
{	
	if (StopFlame > 0) {
		isHitStop = true;
		HitStopTime = StopFlame;
	}
}

bool Stopper::HitStopUpdate()
{
	
	if (HitStopTime > 0) {
		HitStopTime--;
	}
	else {
		isHitStop = false;
	}

	return isHitStop;

}

void Stopper::PauseDraw()
{
	if (isPause == true) {
		Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0x4400007F, kFillModeSolid);
	}
}