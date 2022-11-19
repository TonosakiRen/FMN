#include "Background.h"

void Background::Draw(Screen& screen, int bg1, int bg2, int bg3, int bg5, int bg6, int bg7)
{

	Novice::DrawSprite(-400 - screen.Scroll.x * 0.02, -160 + screen.Scroll.y * 0.02, bg3, 1, 1, 0, WHITE);
	//Novice::DrawSprite(0 - screen.Scroll.x * 0.9, 760 + screen.Scroll.y * 0.5, bg5, 1, 1, 0, WHITE);
	Novice::DrawSprite(0 - screen.Scroll.x * 0.8, 540 + screen.Scroll.y * 0.31, bg7, 1, 1, 0, WHITE);
	Novice::DrawSprite(0 - screen.Scroll.x * 0.8, 444 + screen.Scroll.y * 0.41, bg6, 1, 1, 0, WHITE);
	Novice::DrawSprite(0 - screen.Scroll.x * 0.8, 436 + screen.Scroll.y * 0.5, bg1, 1, 1, 0, WHITE);
	Novice::DrawSprite(0 - screen.Scroll.x * 0.9, 872 + screen.Scroll.y * 0.8, bg5, 1, 1, 0, WHITE);
	Novice::DrawSprite(0 - screen.Scroll.x, 880 + screen.Scroll.y * 1.01, bg2, 1, 1, 0, WHITE);


}
