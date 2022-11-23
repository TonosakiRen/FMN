#include "Feed.h"

void Feed::Feedin(float& t, float feedspeed, int width, int height) {
	t += feedspeed;
	t = Clamp::clamp(t, 0.0f, 1.0f);
	int color = 0x00000000 | static_cast<int>((1.0f - t) * 0xFF + t * 0x00);
	Novice::DrawBox(0, 0, width, height, 0, color, kFillModeSolid);
}

void Feed::FeedHalfin(float& t, float feedspeed, int width, int height) {
	t += feedspeed;
	t = Clamp::clamp(t, 0.0f, 0.9f);
	int color = 0x00000000 | static_cast<int>((1.0f - t) * 0xFF + t * 0x00);
	Novice::DrawBox(0, 0, width, height, 0, color, kFillModeSolid);
}

void Feed::Feedout(float& t, float feedspeed, int width, int height) {
	t += feedspeed;
	t = Clamp::clamp(t, 0.0f, 1.0f);
	int color = 0x00000000 | static_cast<int>((1.0f - t) * 0x00 + t * 0xFF);
	Novice::DrawBox(0, 0, width, height, 0, color, kFillModeSolid);
}

void Feed::FeedHalfout(float& t, float feedspeed, int width, int height) {
	t += feedspeed;
	t = Clamp::clamp(t, 0.0f, 0.9f);
	int color = 0x00000000 | static_cast<int>((1.0f - t) * 0x00 + t * 0xFF);
	Novice::DrawBox(0, 0, width, height, 0, color, kFillModeSolid);
}

unsigned int Feed::Feedin(float& t, float feedspeed, unsigned  int color) {
	color = color & 0xFFFFFF00;
	t += feedspeed;
	t = Clamp::clamp(t, 0.0f, 1.0f);
	unsigned int tmp = color | static_cast<int>((1.0f - t) * 0x00 + t * 0xFF);
	return{ tmp };
}

unsigned int Feed::Feedout(float& t, float feedspeed, unsigned int color) {
	color = color & 0xFFFFFF00;
	t += feedspeed;
	t = Clamp::clamp(t, 0.0f, 1.0f);
	unsigned int tmp = color | static_cast<int>((1.0f - t) * 0xFF + t * 0x00);
	return{ tmp };
}

unsigned int Feed::Feedout2(float t, float feedspeed, unsigned int color) {
	color = color & 0xFFFFFF00;
	t = Clamp::clamp(t, 0.0f, 1.0f);
	unsigned int tmp = color | static_cast<int>((1.0f - t) * 0xFF + t * 0x00);
	return{ tmp };
}