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

void Sound::SoundEffect(Effect* effect, const char* fileName) {

	if (effect->load == false) {
		effect->load = true;
		effect->Sound = Novice::LoadAudio(fileName);
	}

	if (Novice::IsPlayingAudio(effect->Handle) == 0 || effect->Handle == -1) {
		effect->Handle = Novice::PlayAudio(effect->Sound, 0, 0.4f);
	}
}

void Sound::SoundEffect(Effect* effect, float volume,const char* fileName) {

	
	if (effect->load == false) {
		effect->load = true;
		effect->Sound = Novice::LoadAudio(fileName);
	}

	
		effect->Handle = Novice::PlayAudio(effect->Sound, 0, volume);
	

}
