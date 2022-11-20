#pragma once
#include <Novice.h>
#include "Key.h"
#include "Vec2.h"

class Stopper
{
private:

	bool isPause = false;

	bool isHitStop = false;
	int HitStopTime = 0;

	int Selected = 0;

	bool RestartFlag = false;
	int BGMnum = false;
	int SEnum = false;
	bool QuitFlag = false;

	struct PauseStruct {
		const int LINE;
		Vec2 Pos;
		Vec2 Size;
		unsigned int Color;
	};

	PauseStruct InPause = {
		-1,
		{1920 / 2,250},
		{752,200},
		WHITE,
	};

	PauseStruct BackGame = {
		0,
		{1920 / 2,470},
		{508,80},
		WHITE,
	};

	PauseStruct Restart = {
		1,
		{1920 / 2,590},
		{352,80},
		WHITE,
	};

	PauseStruct BGM = {
		2,
		{1920 / 2,710},
		{260,80},
		WHITE,
	};

	PauseStruct SE = {
		3,
		{1920 / 2,830},
		{224,80},
		WHITE,
	};

	PauseStruct Quit = {
		4,
		{1920 / 2,950},
		{508,80},
		WHITE,
	};



	void PauseQuadDraw(PauseStruct select, int tex);

public:

	int HitStopTimeStart = 0;
	
	bool Pause();

	void PauseDraw(int inPause_Gra, int PauseSelect_Gra);

	void HitStopMake(int StopFlame);

	bool HitStopUpdate();

	bool ReturnRestartFlag() { return RestartFlag; }

	int ReturnBGMnum() { return BGMnum; }
	int ReturnSEnum() { return SEnum; }

	bool ReturnQuitFlag() { return QuitFlag; }

};

