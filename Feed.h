#pragma once
#include <Novice.h>
#include "Clamp.h"
namespace Feed {
	void Feedin(float& t, float feedspeed, int width, int height);
	void FeedHalfin(float& t, float feedspeed, int width, int height);
	void Feedout(float& t, float feedspeed, int width, int height);
	void FeedHalfout(float& t, float feedspeed, int width, int height);

	unsigned int Feedin(float& t, float feedspeed, unsigned  int color);
	unsigned int Feedout(float& t, float feedspeed, unsigned  int color);
}
