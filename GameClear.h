#pragma once
#include"Screen.h"
#include"Vec2.h"
#include"Quad.h"
#include "Collision.h"

class GameClear
{
private:

	int Time;

	bool TitleDrawFlag = false;

	struct GameClearStruct {
		const int IMAGELINE;
		Vec2 Pos;
		Vec2 Size;
		unsigned int Color;
	};

	GameClearStruct GameClearText = {
		-1,
		{1920 / 2,200},
		{1208,224},
		WHITE,
	};

	GameClearStruct TitleBack = {
		5,
		{1920 / 2,950},
		{568,80},
		WHITE,
	};


	void GameClearQuadDraw(GameClearStruct select, int tex);

public:

	bool TitleFlag = false;

	void Update();

	void Draw(Screen& screen, int Ending_Gra, int gamecleargra);

};