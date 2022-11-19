#include "Tutorial.h"

Tutorial::Tutorial()
{
	for (int i = 0; i < 2; i++) {
		LetAttack[i] = {
		{1920, 320 / 2},
		{ 160,160 },
		{ { LetAttack[i].Pos.x - LetAttack[i].ColSize.x / 2 , LetAttack[i].Pos.y + LetAttack[i].ColSize.y / 2},
		int(LetAttack[i].ColSize.x),int(LetAttack[i].ColSize.y) },
		{ 48,48 },
		{ { LetAttack[i].Pos.x - LetAttack[i].ImageSize.x / 2 , LetAttack[i].Pos.y + LetAttack[i].ImageSize.y / 2},
		int(LetAttack[i].ImageSize.x),int(LetAttack[i].ImageSize.y) },
			0,
			0,
			false
		};
	}

	LetAttack[0].Pos = { 1100,LetAttack[0].ColSize.y / 2 };
	LetAttack[1].Pos = { 1500,300 };

	for (int i = 0; i < 2; i++) {
		LetAttack[i].ColQuad = { { LetAttack[i].Pos.x - LetAttack[i].ColSize.x / 2 , LetAttack[i].Pos.y + LetAttack[i].ColSize.y / 2},
		int(LetAttack[i].ColSize.x),int(LetAttack[i].ColSize.y) };

		LetAttack[i].ImageQuad = { { LetAttack[i].Pos.x - LetAttack[i].ImageSize.x / 2 , LetAttack[i].Pos.y + LetAttack[i].ImageSize.y / 2},
		int(LetAttack[i].ImageSize.x),int(LetAttack[i].ImageSize.y) };
	}
}

void Tutorial::Update()
{



	for (int i = 0; i < 2; i++) {
		LetAttack[i].ColQuad = { { LetAttack[i].Pos.x - LetAttack[i].ColSize.x / 2 , LetAttack[i].Pos.y + LetAttack[i].ColSize.y / 2},
		int(LetAttack[i].ColSize.x),int(LetAttack[i].ColSize.y) };

		LetAttack[i].ImageQuad = { { LetAttack[i].Pos.x - LetAttack[i].ImageSize.x / 2 , LetAttack[i].Pos.y + LetAttack[i].ImageSize.y / 2},
		int(LetAttack[i].ImageSize.x),int(LetAttack[i].ImageSize.y) };
	}
}

void Tutorial::Draw(Screen& screen)
{
	screen.DrawQuad2Renban(LetJump.ColQuad, LetJump.srcX,0, 1,1,1,1,LetJump.Anime,0,WHITE,false);

	for (int i = 0; i < 2; i++) {
		screen.DrawQuad2Renban(LetAttack[i].ColQuad, LetAttack[i].srcX, 0, 1, 1, 1, 1, LetAttack[i].Anime, 0, WHITE, false);
	}

	screen.DrawQuad2Renban(LetDash.ColQuad, LetDash.srcX, 0, 1, 1, 1, 1, LetDash.Anime, 0, WHITE, false);

}

void Tutorial::HitLetAttack(Quad Target)
{
	for (int i = 0; i < 2; i++){
		if (Collision::QuadToQuad(Target, LetAttack[i].ColQuad)) {
			LetAttack[i].Pos.x += 30;
		}
	}
}

bool Tutorial::PlayerGoNext(float PlayerPosX) {

	if (PlayerPosX > 2320) {
		return true;
	}
	return false;
}