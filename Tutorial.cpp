#include "Tutorial.h"
#include "Key.h"
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
	/*if (Key::IsPressed(DIK_G)) {
		type3.Pos.y += 4;
	}
	if (Key::IsPressed(DIK_B)) {
		type3.Pos.y -= 4;
	}
	if (Key::IsPressed(DIK_V)) {
		type3.Pos.x -= 4;
	}
	if (Key::IsPressed(DIK_N)) {
		type3.Pos.x += 4;
	}

	type3.Quad = { { type3.Pos.x - type3.Size.x / 2 , type3.Pos.y + type3.Size.y / 2},
		int(type3.Size.x),int(type3.Size.y) };*/


	for (int i = 0; i < 2; i++) {
		LetAttack[i].ColQuad = { { LetAttack[i].Pos.x - LetAttack[i].ColSize.x / 2 , LetAttack[i].Pos.y + LetAttack[i].ColSize.y / 2},
		int(LetAttack[i].ColSize.x),int(LetAttack[i].ColSize.y) };

		LetAttack[i].ImageQuad = { { LetAttack[i].Pos.x - LetAttack[i].ImageSize.x / 2 , LetAttack[i].Pos.y + LetAttack[i].ImageSize.y / 2},
		int(LetAttack[i].ImageSize.x),int(LetAttack[i].ImageSize.y) };
	}
}

void Tutorial::Draw(Screen& screen, int gra1, int gra2, int gra3)
{
	screen.DrawQuad2Renban(LetJump.ColQuad, LetJump.srcX,0, 1,1,1,1,LetJump.Anime,0,WHITE,false);

	for (int i = 0; i < 2; i++) {
		screen.DrawQuad2Renban(LetAttack[i].ColQuad, LetAttack[i].srcX, 0, 1, 1, 1, 1, LetAttack[i].Anime, 0, WHITE, false);
	}

	screen.DrawQuad2Renban(LetDash.ColQuad, LetDash.srcX, 0, 1, 1, 1, 1, LetDash.Anime, 0, WHITE, false);

	screen.DrawQuad2Renban(type1.Quad, type1.SrcX, 0, type1.Size.x, type1.Size.y, type1.sheets, 30, type1.Anime, gra1, WHITE, false);

	screen.DrawQuad2Renban(type2.Quad, type2.SrcX, 0, type2.Size.x, type2.Size.y, type2.sheets, 30, type2.Anime, gra2, WHITE, false);

	screen.DrawQuad2Renban(type3.Quad, type3.SrcX, 0, type3.Size.x, type3.Size.y, type3.sheets, 30, type3.Anime, gra3, WHITE, false);
}

void Tutorial::PlayDrawEx(int gra, int type)
{
	Novice::DrawQuad(0, 952, 1920, 952, 0, 1080, 1920, 1080, 0, 128 * type, 1920, 128, gra, WHITE);
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