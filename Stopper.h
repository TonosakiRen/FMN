#pragma once
#include <Novice.h>
#include "Key.h"
#include "Vec2.h"
#include "ControllerInput.h"
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
		const int IMAGELINE;
		const int LINE;
		Vec2 Pos;
		Vec2 Size;
		unsigned int Color;
	};

	PauseStruct InPause = {
		-1,
		-1,
		{1920 / 2,250},
		{752,200},
		WHITE,
	};

	PauseStruct BackGame = {
		0,
		0,
		{1920 / 2,570},
		{508,80},
		WHITE,
	};

	PauseStruct Restart = {
		1,
		1,
		{1920 / 2,690},
		{352,80},
		WHITE,
	};

	PauseStruct BGM = {
		2,
		98,
		{1920 / 2,710},
		{260,80},
		WHITE,
	};

	PauseStruct SE = {
		3,
		99,
		{1920 / 2,830},
		{224,80},
		WHITE,
	};

	PauseStruct Quit = {
		4,
		3,
		{1920 / 2,930},
		{508,80},
		WHITE,
	};

	PauseStruct Title = {
		5,
		2,
		{1920 / 2,810},
		{568,80},
		WHITE,
	};

	bool stickup = false;
	bool prestickup = false;
	bool stickdown = false;
	bool prestickdown = false;

	void PauseQuadDraw(PauseStruct select, int tex);

public:

	bool canselect = true;

	bool TitileBackFlag = false;

	int HitStopTimeStart = 0;
	
	bool Pause();

	void PauseDraw(int inPause_Gra, int PauseSelect_Gra);

	void HitStopMake(int StopFlame);

	bool HitStopUpdate();

	bool ReturnRestartFlag() { return RestartFlag; }

	int ReturnBGMnum() { return BGMnum; }
	int ReturnSEnum() { return SEnum; }

	bool ReturnQuitFlag() { return QuitFlag; }

	void RestartFlaggFalse() { RestartFlag = false;};
	void isPauseFalse() { isPause = false; };

};

