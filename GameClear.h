#pragma once
#include"Screen.h"
#include"Vec2.h"
#include"Quad.h"
#include "Collision.h"

class GameClear
{
private:

	int Selected = 0;

	struct GameClearStruct {
		const int IMAGELINE;
		Vec2 Pos;
		Vec2 Size;
		unsigned int Color;
	};

	GameClearStruct Restart = {
		1,
		{1920 / 2,830},
		{352,80},
		WHITE,
	};

	GameClearStruct Quit = {
		4,
		{1920 / 2,950},
		{508,80},
		WHITE,
	};


	void GameClearQuadDraw(GameClearStruct select, int tex);

public:


	void Update();

	void Draw(Screen& screen, int Ending_Gra);

};