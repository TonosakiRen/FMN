#include "Background.h"

void Background::Draw(Screen& screen, int bg1, int bg2, int bg3)
{

	Novice::DrawSprite(-400 - screen.Scroll.x * 0.1, 0, bg3, 1, 1, 0, WHITE);
	Novice::DrawSprite(0 - screen.Scroll.x * 0.9, 0, bg1, 1, 1, 0, WHITE);
	Novice::DrawSprite(0 - screen.Scroll.x, 0, bg2, 1, 1, 0, WHITE);


}
