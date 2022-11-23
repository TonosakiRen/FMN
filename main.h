#pragma once
#define _USE_MATH_DEFINES
#include <Novice.h>
#include <math.h>
#include "ControllerInput.h"
#include "Feed.h"
#include "Quad.h"
#include "Screen.h"
#include "Vec2.h"
#include "Key.h"
#include "PlayerMain.h"
#include "Boss.h"
#include "Boss2.h"
#include "Stopper.h"
#include "Effect2.h"
#include "Effect.h"
#include "Background.h"
#include "Tutorial.h"
#include "GameOver.h"
#include <time.h>
#include "Sound.h"
#include "GameClear.h"

Sound sound;
Screen screen;
PlayerMain playermain;
Boss boss;
Boss2 boss2;
Background background;
Tutorial tutorial;
Stopper stopper;
GameOver gameoverclass;
GameClear GameClearClass;
Effect playerEffect(30, 2, { 0.0f,0.0f }, { 0.0f,0.0f }, 30, 50, 0, 0, M_PI / 30.0f, -1.0f, 1);
Effect boss2Effect(30, 2, { 0.0f,0.0f }, { 0.0f,0.0f }, 30, 50, 0, 0, M_PI / 30.0f, -1.0f, 1);
Effect enemySwordEffect(30, 1, { 0.0f,0.0f }, { 0.0f,0.0f }, 30, 50, 0, 0, M_PI / 60.0f, -1.0f , 1);
Effect stageEffect(30, 30, { 0.0f,1.0f }, { 0.0f,1.0f }, 10, 15, 1.0f, 5.0f, 0.0f,0.0f, 1);
Effect playerEffectSword(160, 1, { 0.1f,-0.7f }, { 0.9f,0.7f },30, 40, 0.0f, 30.0f, 0.0f, -1.9f, 40);
Effect bossBodyEffect(10, 1, { 0.0f,0.0f }, { 0.0f,0.0f }, 40, 80, 0.0f, 0.0f, 0.0f, -0.8f, 1);
Effect bossHeadEffect(10, 1, { 0.0f,0.0f }, { 0.0f,0.0f }, 40, 80, 0.0f, 0.0f, 0.0f, -0.8f, 1);
Effect bossRightArmEffect(10, 1, { 0.0f,0.0f }, { 0.0f,0.0f }, 40, 80, 0.0f, 0.0f, 0.0f, -0.8f, 1);
Effect bossLeftArmEffect(10, 1, { 0.0f,0.0f }, { 0.0f,0.0f }, 40, 80, 0.0f, 0.0f, 0.0f, -0.8f, 1);
Effect bossLegEffect(10, 1, { 0.0f,0.0f }, { 0.0f,0.0f }, 40, 80, 0.0f, 0.0f, 0.0f, -0.8f, 1);
Effect5 white0(10, 1, { 500,500 }, 40, 40, 3.0f, 3.0f, 0.0f, 0.05f, 1);
Effect5 white1(10, 1, { 500,500 }, 40, 40, 3.0f, 3.0f, 0.0f, 0.05f, 1);
Effect5 white2(10, 1, { 500,500 }, 40, 40, 3.0f, 3.0f, 0.0f, 0.05f, 1);
Effect5 white3(10, 1, { 500,500 }, 40, 40, 3.0f, 3.0f, 0.0f, 0.05f, 1);
Effect5 white4(10, 1, { 500,500 }, 40, 40, 3.0f, 3.0f, 0.0f, 0.05f, 1);
Effect5 white5(10, 1, { 500,500 }, 40, 40, 3.0f, 3.0f, 0.0f, 0.05f, 1);
Effect5 white6(10, 1, { 500,500 }, 40, 40, 3.0f, 3.0f, 0.0f, 0.05f, 1);





enum Scene {
	title,
	stage,
	stage2,
	gameover,
	gameclear
};

Scene scene = title;

float feedoutT = 0;
float feedinT = 0;
bool isFeedout = false;
bool isFeedin = false;
bool isTitleStart = false;
bool isStageStart = false;
bool isGameoverStart = false;
bool isGameclearStart = false;
bool isGameover = false;
bool isGameclear = false;
bool isMovie = false;
bool isRestart = false;
bool isTitle = false;
bool isPause = false;
bool ClearFlag = false;
bool GameOverType = false;
bool Restart2 = false;

void InitFeedin() {
	feedinT = 0;
	isFeedin = false;
}
void InitFeedout() {
	feedoutT = 0;
	isFeedout = false;
}

void InitEffect() {
	for (int i = 0; i < 30; i++) {
		playerEffect.particles[i].isActive = false;
		boss2Effect.particles[i].isActive = false;
		enemySwordEffect.particles[i].isActive = false;
	}
	for (int i = 0; i < 160; i++) {
		playerEffectSword.particles[i].isActive = false;
	}
	for (int i = 0; i < 10; i++) {
		bossBodyEffect.particles[i].isActive = false;
		bossHeadEffect.particles[i].isActive = false;
		bossRightArmEffect.particles[i].isActive = false;
		bossLeftArmEffect.particles[i].isActive = false;
		bossLegEffect.particles[i].isActive = false;
		white0.particles[i].isActive = false;
		white1.particles[i].isActive = false;
		white2.particles[i].isActive = false;
		white3.particles[i].isActive = false;
		white4.particles[i].isActive = false;
		white5.particles[i].isActive = false;
		white6.particles[i].isActive = false;
	}
}
	void InitbossEffect() {
		for (int i = 0; i < 10; i++) {
			bossBodyEffect.particles[i].isActive = false;
			bossHeadEffect.particles[i].isActive = false;
			bossRightArmEffect.particles[i].isActive = false;
			bossLeftArmEffect.particles[i].isActive = false;
			bossLegEffect.particles[i].isActive = false;
			white0.particles[i].isActive = false;
			white1.particles[i].isActive = false;
			white2.particles[i].isActive = false;
			white3.particles[i].isActive = false;
			white4.particles[i].isActive = false;
			white5.particles[i].isActive = false;
			white6.particles[i].isActive = false;
		}
	}

	//BGM

	bool isTitleBGM = false;
	bool isBossBGM = false;
	bool isBoss2BGM = false;
	bool isClearBGM = false;
	bool isGameoverBGM = false;

	bool isTitleStopBGM = false;
	bool isStageStopBGM = false;
	bool isClearStopBGM = false;
	bool isGameoverStopBGM = false;

	bool switchBGM = false;
	int BGMHandle = 0;

	void BGMstop() {
		Novice::StopAudio(BGMHandle);
	}