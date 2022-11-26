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
		{ 160,160 },
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

void Tutorial::Init() {
	LetAttackFlag = false;
	LetDashFlag = false;
	type2.Alpha = 0;
	type3.Alpha = 0;
}

void Tutorial::Update(float PlayerX)
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

	if (PlayerX > 600) {
		LetAttackFlag = true;
	}
	if (PlayerX > 1600) {
		LetDashFlag = true;
	}


	for (int i = 0; i < 2; i++) {
		LetAttack[i].ColQuad = { { LetAttack[i].Pos.x - LetAttack[i].ColSize.x / 2 , LetAttack[i].Pos.y + LetAttack[i].ColSize.y / 2},
		int(LetAttack[i].ColSize.x),int(LetAttack[i].ColSize.y) };

		LetAttack[i].ImageQuad = { { LetAttack[i].Pos.x - LetAttack[i].ImageSize.x / 2 , LetAttack[i].Pos.y + LetAttack[i].ImageSize.y / 2},
		int(LetAttack[i].ImageSize.x),int(LetAttack[i].ImageSize.y) };
	}

	if (LetAttackFlag == true) {
		if (type2.Alpha < 255) {
			type2.Alpha += 2;
		}
		if (type2.Alpha >= 255) {
			type2.Alpha = 255;
		}
	}

	if (LetDashFlag == true) {
		if (type3.Alpha < 255) {
			type3.Alpha += 2;
		}
		if (type3.Alpha >= 255) {
			type3.Alpha = 255;
		}
	}
}

void Tutorial::Draw(Screen& screen, int gra1, int gra2, int gra3,int LetJumpGra, int LetAttackGra, int LetDashGra)
{
	//screen.DrawQuad2Renban(LetJump.ColQuad, LetJump.srcX,0, 1,1,1,1,LetJump.Anime,0,WHITE,false);
	screen.DrawQuad2Renban(LetJump.ImageQuad, LetJump.srcX, 0, LetJump.ImageSize.x, LetJump.ImageSize.y, 4, 5, LetJump.Anime, LetJumpGra, WHITE, false);

	for (int i = 0; i < 2; i++) {
		//screen.DrawQuad2Renban(LetAttack[i].ColQuad, LetAttack[i].srcX, 0, 1, 1, 1, 1, LetAttack[i].Anime, 0, WHITE, false);
		screen.DrawQuad2Renban(LetAttack[i].ImageQuad, LetAttack[i].srcX, 0, LetAttack[i].ImageSize.x, LetAttack[i].ImageSize.y, 1, 1, LetAttack[i].Anime, LetAttackGra, WHITE, false);

	}

	//screen.DrawQuad2Renban(LetDash.ColQuad, LetDash.srcX, 0, 1, 1, 1, 1, LetDash.Anime, 0, WHITE, false);
	screen.DrawQuad2Renban(LetDash.ImageQuad, LetDash.srcX, 0, LetDash.ImageSize.x, LetDash.ImageSize.y, 4, 5, LetDash.Anime, LetDashGra, WHITE, false);



	screen.DrawQuad2Renban(type1.Quad, type1.SrcX, 0, type1.Size.x, type1.Size.y, type1.sheets, 30, type1.Anime, gra1, WHITE, false);

	screen.DrawQuad2Renban(type2.Quad, type2.SrcX, 0, type2.Size.x, type2.Size.y, type2.sheets, 30, type2.Anime, gra2, 0xFFFFFF00 + type2.Alpha, false);

	screen.DrawQuad2Renban(type3.Quad, type3.SrcX, 0, type3.Size.x, type3.Size.y, type3.sheets, 30, type3.Anime, gra3, 0xFFFFFF00 + type3.Alpha, false);

	//Novice::ScreenPrintf(700, 700, "%0.1f", a);
}

void Tutorial::PlayDrawEx(int gra, int type)
{
	Novice::DrawQuad(0, 952, 1920, 952, 0, 1080, 1920, 1080, 0, 128 * type, 1920, 128, gra, WHITE);
}

void Tutorial::HitLetAttack(Quad Target)
{
	for (int i = 0; i < 2; i++){
		if (Collision::QuadToQuad(Target, LetAttack[i].ColQuad)) {
			/*LetAttack[i].Pos.x += 30;*/
			sound.SoundEffect(sound.playerattackhit, 0.4f, "./Resources/sounds/PlayerAttackHit.wav", false);
		}
	}
}

bool Tutorial::PlayerGoNext(float PlayerPosX) {

	if (PlayerPosX > 2320) {
		return true;
	}
	return false;
}