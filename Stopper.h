#pragma once
#include <Novice.h>
#include "Key.h"

class Stopper
{
private:

	bool isPause = false;

	bool isHitStop = false;
	int HitStopTime = 0;

	

public:

	int HitStopTimeStart = 0;


	
	bool Pause();

	void PauseDraw();

	void HitStopMake(int StopFlame);

	bool HitStopUpdate();

};

