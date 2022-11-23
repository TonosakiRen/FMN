#pragma once
#include"Screen.h"
#include"Vec2.h"
#include"Quad.h"
#include "Collision.h"
#include"Sound.h"
class GameOver
{
private:
	Sound sound;
	int Selected = 0;

	struct GameOverStruct {
		const int IMAGELINE;
		const int LINE;
		Vec2 Pos;
		Vec2 Size;
		unsigned int Color;
	};

	GameOverStruct Restart = {
		1,
		0,
		{1920 / 2,830},
		{352,80},
		WHITE,
	};

	GameOverStruct Quit = {
		4,
		1,
		{1920 / 2,950},
		{508,80},
		WHITE,
	};

	bool stickup = false;
	bool prestickup = false;
	bool stickdown = false;
	bool prestickdown = false;

	void GameOverQuadDraw(GameOverStruct select, int tex);

public:
	
	bool canselect = false;
	bool isDraw = false;

	bool RestartFlag = false;
	bool QuitFlag = false;

	void Update();

	void Draw(Screen& screen, int PauseSelect_Gra);

};

