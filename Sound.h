#pragma once
#include <Novice.h>

class Sound {
public:


	struct Bgm {
		int Sound;
		int Handle=-1;
		bool load=false;
	};
	Bgm StageBgm;
	Bgm StageBgm2;
	Bgm GameOver;
	Bgm GameClear;
	Bgm Title;

	void BGM(Bgm *bgm,const char* fileName);
	void BGMStop(Bgm *bgm);
	void GameOverBGM(const char* fileName);

	void SoundEffect(const char* filename);
	
};