#include "Sound.h"

void Sound::BGM(Bgm *bgm,float Volume,const char* fileName) {

	if (bgm->load == false) {
		bgm->load = true;
		bgm->Sound = Novice::LoadAudio(fileName);
	}

	if (Novice::IsPlayingAudio(bgm->Handle) == 0 || bgm->Handle == -1) {
		bgm->Handle = Novice::PlayAudio(bgm->Sound, 1, Volume);
	}

}

void Sound::BGM(Bgm* bgm, const char* fileName) {

	if (bgm->load == false) {
		bgm->load = true;
		bgm->Sound = Novice::LoadAudio(fileName);
	}

	if (Novice::IsPlayingAudio(bgm->Handle) == 0 || bgm->Handle == -1) {
		bgm->Handle = Novice::PlayAudio(bgm->Sound, 1, 0.3f);
	}

}

void Sound::BGMStop(Bgm* bgm) {
	
	Novice::StopAudio(bgm->Handle);
}

void Sound::SoundEffect(const char* fileName) {

	bool Load = false;
	int Handle = -1;
	int Sound;
	if (Load == false) {
		Load = true;
		Sound = Novice::LoadAudio(fileName);
	}

	if (Novice::IsPlayingAudio(Handle) == 0 || Handle == -1) {
		Handle = Novice::PlayAudio(Sound, 0, 0.2f);
	}

}

void Sound::SoundEffect(float volume,const char* fileName) {

	bool Load = false;
	int Handle = -1;
	int Sound;
	if (Load == false) {
		Load = true;
		Sound = Novice::LoadAudio(fileName);
	}

	if (Novice::IsPlayingAudio(Handle) == 0 || Handle == -1) {
		Handle = Novice::PlayAudio(Sound, 0, volume);
	}

}
