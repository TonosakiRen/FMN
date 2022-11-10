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
#include "Stopper.h"
#include "Effect.h"


Screen screen;
PlayerMain playermain;
Boss boss;
Stopper stopper;
Effect effect01(100, 1, { 0.0f,0.0f }, { 0.0f,0.0f }, 30, 50, 0, 0, M_PI / 30.0f, -1.0f , 1);
Effect effect02(100, 1, { 0.0f,0.0f }, { 0.0f,0.0f }, 30, 50, 0, 0, M_PI / 60.0f, -1.0f , 1);
Effect effect03(30, 30, { 0.0f,1.0f }, { 0.0f,1.0f }, 10, 15, 1.0f, 5.0f, 0.0f,0.0f, 1);
Effect effect04(160, 1, { 0.1f,-0.7f }, { 0.9f,0.7f },30, 50, 10.0f, 15.0f, 0.0f, -0.4f, 40);
Effect bossBodyEffect(50, 1, { 0.0f,0.0f }, { 0.0f,0.0f }, 40, 80, 0.0f, 0.0f, 0.0f, -0.6f, 1);
Effect bossHeadEffect(50, 1, { 0.0f,0.0f }, { 0.0f,0.0f }, 40, 80, 0.0f, 0.0f, 0.0f, -0.6f, 1);
Effect bossRightArmEffect(50, 1, { 0.0f,0.0f }, { 0.0f,0.0f }, 40, 80, 0.0f, 0.0f, 0.0f, -0.6f, 1);
Effect bossLeftArmEffect(50, 1, { 0.0f,0.0f }, { 0.0f,0.0f }, 40, 80, 0.0f, 0.0f, 0.0f, -0.6f, 1);
Effect bossLegEffect(50, 1, { 0.0f,0.0f }, { 0.0f,0.0f }, 40, 80, 0.0f, 0.0f, 0.0f, -0.6f, 1);