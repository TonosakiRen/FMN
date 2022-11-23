#pragma once
#include"Screen.h"
#include"Vec2.h"
#include"Quad.h"
#include "Collision.h"

class GameClear
{
private:

	int Time = 0;

	bool TitleDrawFlag = false;
	bool RestartTimeFlag = false;
	bool pargectflag = false;

	int RestartCountNum = 0;
	int DrawNum = 0;

	int Ealpha = 0;

	struct GameClearStruct {
		const int IMAGELINE;
		Vec2 Pos;
		Vec2 Size;
		unsigned int Color;
	};

	GameClearStruct GameClearText = {
		-1,
		{1920 / 2,400},
		{1208,224},
		WHITE,
	};

	GameClearStruct RestartCount = {
	    7,
	{1920 / 2 - 100,840},
	{580,80},
	WHITE,
	};

	GameClearStruct Num = {
	99,
	{1920 / 2 + 300,840},
	{68,64},
	WHITE,
	};

	GameClearStruct Num10 = {
	99,
	{1920 / 2 + 300 - 40,840},
	{68,64},
	WHITE,
	};

	GameClearStruct E = {
	999,
	{1920 / 2,540},
	{640,480},
	WHITE,
	};

	GameClearStruct Parfect = {
	8,
	{1920 / 2,300},
	{284,80},
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
	void Init();

	bool TitleFlag = false;

	void Update(int restartcount);

	void Draw(Screen& screen, int numgra,int Ending_Gra, int gamecleargra, int e);

	
};