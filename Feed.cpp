#include "Feed.h"

void Feed::Feedin(float& t, float feedspeed, int width,int height) {
	t += feedspeed;
	t = Clamp::clamp(t, 0, 1);
	int color = 0x00000000 | static_cast<int>((1.0f - t) * 0xFF + t * 0x00);
	Novice::DrawBox(0, 0, width, height, 0, color, kFillModeSolid);
}

void Feed::FeedHalfin(float& t, float feedspeed, int width, int height) {
	t += feedspeed;
	t = Clamp::clamp(t, 0, 0.9);
	int color = 0x00000000 | static_cast<int>((1.0f - t) * 0xFF + t * 0x00);
	Novice::DrawBox(0, 0, width, height, 0, color, kFillModeSolid);
}

void Feed::Feedout(float& t, float feedspeed, int width, int height) {
	t += feedspeed;
	t = Clamp::clamp(t, 0, 1);
	int color = 0x00000000 | static_cast<int>((1.0f - t) * 0x00 + t * 0xFF);
	Novice::DrawBox(0, 0, width, height, 0, color, kFillModeSolid);
}

void Feed::FeedHalfout(float& t, float feedspeed, int width, int height) {
	t += feedspeed;
	t = Clamp::clamp(t, 0, 0.9);
	int color = 0x00000000 | static_cast<int>((1.0f - t) * 0x00 + t * 0xFF);
	Novice::DrawBox(0, 0, width, height, 0, color, kFillModeSolid);
}

int Feed::Feedin(float& t, float feedspeed , int& color) {
	t += feedspeed;
	t = Clamp::clamp(t, 0, 1);
	int tmp = color | static_cast<int>((1.0f - t) * 0xFF + t * 0x00);
	return{ tmp };
}

int Feed::Feedout(float& t, float feedspeed, int& color) {
	t += feedspeed;
	t = Clamp::clamp(t, 0, 1);
	int tmp = color | static_cast<int>((1.0f - t) * 0x00 + t * 0xFF);
	return{ tmp };
}