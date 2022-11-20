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
#include <time.h>

Screen screen;
PlayerMain playermain;
Boss boss;
Boss2 boss2;
Background background;
Tutorial tutorial;
Stopper stopper;
Effect playerEffect(30, 2, { 0.0f,0.0f }, { 0.0f,0.0f }, 30, 50, 0, 0, M_PI / 30.0f, -1.0f, 1);
Effect enemySwordEffect(30, 1, { 0.0f,0.0f }, { 0.0f,0.0f }, 30, 50, 0, 0, M_PI / 60.0f, -1.0f , 1);
Effect stageEffect(30, 30, { 0.0f,1.0f }, { 0.0f,1.0f }, 10, 15, 1.0f, 5.0f, 0.0f,0.0f, 1);
Effect playerEffectSword(160, 1, { 0.1f,-0.7f }, { 0.9f,0.7f },30, 40, 0.0f, 30.0f, 0.0f, -1.9f, 40);
Effect bossBodyEffect(10, 1, { 0.0f,0.0f }, { 0.0f,0.0f }, 40, 80, 0.0f, 0.0f, 0.0f, -0.8f, 1);
Effect bossHeadEffect(10, 1, { 0.0f,0.0f }, { 0.0f,0.0f }, 40, 80, 0.0f, 0.0f, 0.0f, -0.8f, 1);
Effect bossRightArmEffect(10, 1, { 0.0f,0.0f }, { 0.0f,0.0f }, 40, 80, 0.0f, 0.0f, 0.0f, -0.8f, 1);
Effect bossLeftArmEffect(10, 1, { 0.0f,0.0f }, { 0.0f,0.0f }, 40, 80, 0.0f, 0.0f, 0.0f, -0.8f, 1);
Effect bossLegEffect(15, 1, { 0.0f,0.0f }, { 0.0f,0.0f }, 40, 80, 0.0f, 0.0f, 0.0f, -0.8f, 1);


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

void InitFeedin() {
	feedinT = 0;
	isFeedin = false;
}
void InitFeedout() {
	feedoutT = 0;
	isFeedout = false;
}

void Init() {

}




