#pragma once
#include <Novice.h>

class Sound {
public:


	struct Bgm {
		int Sound;
		int Handle=-1;
		bool load=false;
	};
	struct Effect {
		int Sound;
		int Handle = -1;
		bool load = false;
	};
	Bgm StageBgm;
	Bgm StageBgm2;
	Bgm GameOver;
	Bgm GameClear;
	Bgm Title;

	Bgm Rotate;

	Effect swing1;
	Effect swing2;
	Effect swing3;
	Effect rotate;
	Effect jumpstart;
	Effect jumpattack;
	Effect circledeath;

	Effect playerattack;
	Effect playerattackhit;
	Effect playerjump;


	void BGM(Bgm *bgm,const char* fileName);
	void BGM(Bgm* bgm, float Volume, const char* fileName);
	void BGMStop(Bgm *bgm);
	

	void SoundEffect(Effect *effect,const char* filename);

	void SoundEffect(Effect *effect, float volume, const char* fileName);
	
};