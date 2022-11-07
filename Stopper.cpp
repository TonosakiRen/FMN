#include "Stopper.h"

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
