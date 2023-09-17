#include "Boss2.h"
#include "Clamp.h"
#include "Key.h"
#include "Easing.h"
#include "Randam.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Feed.h"
#include "Boss2.h"


Boss2::Boss2() :
	centerOfDarknessLeft(30, 40, { 0,0 }, { {0,0},0,0 }, 32, 32, 6.0f, 6.0f, -40.0f, 0.0f, 1),
	centerOfDarknessRight(30, 40, { 0,0 }, { {0,0},0,0 }, 32, 32, 6.0f, 6.0f, -40.0f, 0.0f, 1),
	centerOfDarknessUnder(30, 40, { 0,0 }, { {0,0},0,0 }, 32, 32, 6.0f, 6.0f, -40.0f, 0.0f, 1),
	centerOfDarknessUnderLeft(40, 40, { 0,0 }, { {0,0},0,0 }, 32, 32, 6.0f, 6.0f, -40.0f, 0.0f, 1),
	centerOfDarknessUnderRight(40, 40, { 0,0 }, { {0,0},0,0 }, 32, 32, 6.0f, 6.0f, -40.0f, 0.0f, 1),
	swordEffect(500, 0, { 0.0f,0.0f }, { 0.0f,0.0f }, 30, 30, 0.0f, 0.0f, 0.0f, 0.1f, 1),
	chaseEffect(chaseBulletNum, 40, { 0.0f,0.0f }, { 0.0f,0.0f }, 32, 32, 10.0f, 10.0f, 40.0f, 0.0f, 1),
	TelechaseEffect(1, 0, { 0.0f,0.0f }, { 0.0f,0.0f }, 50, 50, 10.0f, 10.0f, 40.0f, 0.0f, 1)
{

	

	for (int i = 0; i < 3; i++) {
		centerNyokkiUpSrcX[i] = 0;
		centerNyokkiKeepSrcX[i] = 0;
		centerNyokkiT[i] = 0.0f;
	}

	for (int i = 0; i < swordNum; i++) {
		orbitColor[i] = RED;
		theta[i] = -(M_PI * 2.0f / swordNum) * i - 1.0f * M_PI / 180;
		isSword[i] = false;
		getFrag[i] = false;
		swordT[i] = 0.0f;
		isOrbit[i] = false;
	}
	for (int i = 0; i < chaseBulletNum; i++) {
		chaseframe[i] = 0.0f;
		isGet[i] = false;
	}

	for (int i = 0; i < rotateBulletNum; i++) {
		rotatetheta[i] = -(M_PI * 2.0f / rotateBulletNum) * i;
		isSword[i] = false;
		isRotateBullet[i] = false;
		rotateBulletT[i] = 0.0f;
	}
	for (int i = 0; i < nyokkiNum / 2; i++) {
		leftNyokkiUpSrcX[i] = 0;
		leftNyokkiKeepSrcX[i] = 0;
		rightNyokkiUpSrcX[i] = 0;
		rightNyokkiKeepSrcX[i] = 0;
		leftNyokkiT[i] = 0.0f;
		rightNyokkiT[i] = 0.0f;

	}
	for (int i = 0; i < BulletOriginNum; i++) {

		distance[i] = { 1.0f,0.0f };
		distance[i] = distance[i].Rotation(i * AsgoreTheta).Normalized();
	}
	for (int i = 0; i < allBulletNum; i++) {
		AsgoreBullet[i].t = 0.0f;
	}

	initialmoveBullet = Quad({ 0,moveradius },50, 50,0);
	initialmovemoveBullet = Quad({ 0,movemoveradius },20, 20, 0);

	for (int i = 0; i < 4; i++) {
		movetheta[i] = -(2 * M_PI / 4.0f) * i;
		moveAttackBulletFeedinT[i] = 0.0f;
		moveAttackBulletFeedoutT[i] = 0.0f;
		moveBullet[i] = initialmoveBullet;
	}

	for (int i = 0; i < 16; i++) {
		if (i < 4) {
			movemovetheta[i] = -(2 * M_PI / 4.0f) * i + 1;
		}
		else if (i < 8) {
			movemovetheta[i] = -(2 * M_PI / 4.0f) * (i - 4 + 1);
		}
		else if (i < 12) {
			movemovetheta[i] = -(2 * M_PI / 4.0f) * (i - 8 + 1);
		}
		else if (i < 16) {
			movemovetheta[i] = -(2 * M_PI / 4.0f) * (i - 12 + 1);
		}
		movemoveAttackBulletFeedinT[i] = 0.0f;
		movemoveAttackBulletFeedoutT[i] = 0.0f;
		movemoveBullet[i] = initialmovemoveBullet;
	}
}

void Boss2::Init() {

	HP = MAXHP;
	HpColor = 0x00FF44FF;//HPBar‚ÌF‰Šú‰»iƒOƒŠ[ƒ“j


	keep.rand = 0;
	keep.Time = 0;
	keep.bMove = 0;
	keep.Ease_T = 0;
	keep.FPos = 0;
	keep.theta = 0;
	keep.YMove = 0;
	IsLife = false;
	Zanflame = 2;
	for (int i = 0; i < Max_Zan; i++) {
		zanzou[i].Pos = { {9999,9999},{9999,9999},{9999,9999},{9999,9999} };
		zanzou[i].LifeTime = 0;
		zanzou[i].bSet = 0;
	}

	//ƒXƒe[ƒgŠÇ—‰Šú‰»
	hppattarn = NORMAL;
	pattarn = MIDDLE;
	//UŒ‚ƒpƒ‰ƒ[ƒ^‰Šú‰»
	CoolTime = 200;
	Action = false;
	Attack = false;
	AttackStartTime = 0;
	reload = 0;
	isBossHit = false;
	BossMotionTime = 0;
	
	//waza

	for (int i = 0; i < 30; i++) {
		centerOfDarknessLeft.particles[i].isActive = false;
		centerOfDarknessRight.particles[i].isActive = false;
		centerOfDarknessUnder.particles[i].isActive = false;
		centerOfDarknessUnderLeft.particles[i].isActive = false;
		centerOfDarknessUnderRight.particles[i].isActive = false;
	}
	for (int i = 0; i < 500; i++) {
		swordEffect.particles[i].isActive = false;
	}
	for (int i = 0; i < chaseBulletNum; i++) {
		chaseEffect.particles[i].isActive = false;
	}

	TelechaseEffect.particles[0].isActive = false;
	isCenterOfDarkness = false;

	gravityT = 0.0f;

	Action = false;
	centerOfDarknessCooltime = saveCenterOfDarknessCooltime;
	centerOfDarknessMoveT = 0.0f;
	isCenteroOfDarknessMove = true;
	isGetPos = false;
	isGetNyokkiPos = false;
	isGetcenterNyokki = false;
	centerNyokkiUpAnimationFrame = 0;
	centerNyokkiKeepAnimationFrame = 0;
	iscenterNyokkiCollision = false;
	isFeedCenterNyokki = false;
	iscenterNyokki = false;
	centerNyokkistats = Up;
	for (int i = 0; i < 3; i++) {
		centerNyokkiUpSrcX[i] = 0;
		centerNyokkiKeepSrcX[i] = 0;
		centerNyokkiT[i] = 0.0f;
	}


	radiusT = 0.0f;
	isRelease = false;
	bulletAttackCoolTime = saveBulletAttackCoolTime;
	radius = 200.0f;
	for (int i = 0; i < swordNum; i++) {
		orbitColor[i] = RED;
		theta[i] = -(M_PI * 2.0f / swordNum) * i - 1.0f * M_PI / 180;
		isSword[i] = false;
		getFrag[i] = false;
		swordT[i] = 0.0f;
		isOrbit[i] = false;
		isBulletAttack = false;
		sword[i] = { {9999,9999},0,0 };
	}
	chaseEffect.addEffectCooltime = 40;
	chaseEffect.feedSpeed = 0.0f;
	xMove = 0.0f;
	yMove = 0;
	ytheta = 0.0f;
	rotateT = 0.0f;
	isFeedrotateBullet = false;
	emitchaseEffect = true;
	undertaleFrame = saveUndertaleFrame;
	isUndertaleCollision = false;
	undertaleMoveT = 0.0f;
	for (int i = 0; i < chaseBulletNum; i++) {
		chaseframe[i] = 0.0f;
		isGet[i] = false;
	}

	for (int i = 0; i < rotateBulletNum; i++) {
		rotatetheta[i] = -(M_PI * 2.0f / rotateBulletNum) * i;
		isSword[i] = false;
		isRotateBullet[i] = false;
		rotateBulletT[i] = 0.0f;
	}
	isUndertaleAttack = false;

	dropT = 0.0f;
	isSaveBossY = false;
	isSaveBossY2 = false;
	isSaveBossY3 = false;
	isdropMove = false;
	dropMoveT = 0.0f;
	returnMoveT = 0.0f;
	isdrop = false;
	Action = false;
	isNyokki = false;
	isreturn = false;
	isGetNyokkiPos = false;
	nyokkistats = Up;
	nyokkiUpAnimationFrame = 0;
	nyokkiKeepAnimationFrame = 0;
	isNyokkiCollsion = false;
	isFeedNyokki = false;
	for (int i = 0; i < nyokkiNum / 2; i++) {
		leftNyokkiUpSrcX[i] = 0;
		leftNyokkiKeepSrcX[i] = 0;
		rightNyokkiUpSrcX[i] = 0;
		rightNyokkiKeepSrcX[i] = 0;
		leftNyokkiT[i] = 0.0f;
		rightNyokkiT[i] = 0.0f;

	}

	for (int i = 0; i < 4; i++) {
		ismoveBullet[i] = false;
		movetheta[i] = -(2 * M_PI / 4.0f) * i;
		moveBullet[i] = initialmoveBullet;
		moveAttackBulletFeedinT[i] = 0.0f;
		moveAttackBulletFeedoutT[i] = 0.0f;
	}
	for (int i = 0; i < 16; i++) {
		if (i < 4) {
			movemovetheta[i] = -(2 * M_PI / 4.0f) * i + 1;
		}
		else if (i < 8) {
			movemovetheta[i] = -(2 * M_PI / 4.0f) * (i - 4 + 1);
		}
		else if (i < 12) {
			movemovetheta[i] = -(2 * M_PI / 4.0f) * (i - 8 + 1);
		}
		else if (i < 16) {
			movemovetheta[i] = -(2 * M_PI / 4.0f) * (i - 12 + 1);
		}
		movemoveAttackBulletFeedinT[i] = 0.0f;
		movemoveAttackBulletFeedoutT[i] = 0.0f;
		movemoveBullet[i] = initialmovemoveBullet;
		ismovemoveBullet[i] = false;
	}
	issavePosMoveAttack = false;
	moveIsFeedout = false;
	ismoveMoveAttack = false;
	moveMoveAttackTx = 0.0f;
	ismovexMoveAttack = false;
	setWhich = false;

	TelechaseEffect.feedSpeed = 0;
	TelechaseEffect.particles[0].t = 0.0f;
	TelechaseEffect.particles[0].isActive = false;
	GetTeleportPos = false;
	isTeleport = false;
	TeleportTx = 0.0f;
	isTelechaseFeed = false;
	Telechaseframe[0] = 0;
	TeleisGet[0] = false;
	TeleisFeedrotateBullet = false;
	TeleportNum = 3;
	delayframe = savedelayframe;

	
		
			EmitPos = { 0.0f,SCREEN_HEIGHT - Floor };
			coolTime = 0;
			for (int i = 0; i < allBulletNum; i++) {
				AsgoreBullet[i].isBullet = false;
				AsgoreBullet[i].t = 0.0f;
			}
			emitNum = 0;
			emitActionNum = saveEmitActionNum;
			isMoveCenter = false;
			isGetAsgore = false;
			AsgoreMoveTx = 0.0f;
			AsgoreMoveTy = 0.0f;
			isAsgoreAttack = false;
			isWait = false;
			waitTime = saveWaitTime;
			isAsgoreFeed = false;
			isGetPosRetrun = false;
			AsgoreReturnTx = 0.0f;
			AsgoreReturnTy = 0.0f;
			setWhich = false;
			Action = false;
	

	//anime

	AnimeSelect = Normal;
	sheets = 4;
	SrcX = 0;
	AnimeFlame = 0;

}

void Boss2::BossHit(bool Hit)
{
	isBossHit = false;
	if (Hit == true) {
		isBossHit = true;

	}
}

void Boss2::RandamMoveSelect(int rand, PlayerMain& player, Screen& screen)
{
	/*Novice::ScreenPrintf(1000, 0, "Cooltime::%d", CoolTime);
	Novice::ScreenPrintf(1000, 20, "Action_Boss::%d", Action);
	Novice::ScreenPrintf(1000, 40, "Movearray::%d", MoveArray);
	Novice::ScreenPrintf(1000, 60, "MovePattarn::%d", MovePattern[MoveArray]);
	Novice::ScreenPrintf(1000, 80, "boss:state:%d", pattarn);
	Novice::ScreenPrintf(1000, 200, "boss:hpstate:%d", hppattarn);
	Novice::ScreenPrintf(1000, 220, "boss:keep_bmove:%d", keep.bMove);

	Novice::ScreenPrintf(Pos.x, Pos.y - 200 + SCREEN_HEIGHT, "HP:%d", HP);*/

	if (CoolTime <= 0 && Action == false) {
		if (keep.bMove == false) {
			MoveArray = rand;

			if (MovePattern[MoveArray] == FMoveArray) {
				//Novice::ScreenPrintf(1000, 100, "Reload:%d", reload);

				if (reload == 0) {

					Action = true;


				}
				if (reload == 1) {
					MovePattern[MoveArray] = ReloadMove(FMoveArray);
				}
			}
			else {

				Action = true;


			}
		}
		DirectionGet(player);
		/*keep.Init();*/

	}
	else if (CoolTime >0 && Action == false ) {
		CoolTime--;
		State(player);
		reload = Randam::RAND(0, 1);
		RandMoveSet();
		DirectionGet(player);

	}
	//‹Z’Ç‰Á‚·‚é‚Æ‚«Action=false‚ÍÁ‚·‚±‚Æ
	if (Action == false) {
		KeepUpWaitBack(player);

	}

	if (Action == true&&keep.bMove==false) {
		switch (hppattarn)
		{

		case NORMAL:
			CoolTime = 60;

			switch (pattarn) {
			case NEAR_1:
			{
				if (MovePattern[MoveArray] == array.NormalAttack) {
					//’ÊíUŒ‚‚ÌƒR[ƒh‚Í‚±‚±
					//UndertaleAttack(player);
					//Teleportation(player);
					MoveAttack(player);
					FMoveArray = array.NormalAttack; 
					
				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%‚ÌUŒ‚
					UndertaleAttack(player);
					FMoveArray = array.AttackFunction01;
					

				}
				if (MovePattern[MoveArray] == array.AttackFunction02) {
					//5%‚ÌUŒ‚
					//UndertaleAttack(player);
					nyokkiAttack(player);
					FMoveArray = array.AttackFunction02;
					
					
				}
				if (MovePattern[MoveArray] == array.AttackFunction03) {
					//5%‚ÌUŒ‚
					/*Teleportation(player);
					FMoveArray = array.AttackFunction03;*/
					Action = false;
					CoolTime = 0;

				}
				if (MovePattern[MoveArray] == array.AttackFunction04) {
					//5%‚ÌUŒ‚
					/*Teleportation(player);
					FMoveArray = array.AttackFunction04;*/
				
					Action = false;
					CoolTime = 0;

				}
				if (MovePattern[MoveArray] == array.AttackFunction05) {
					//5%‚ÌUŒ‚
					//Teleportation(player);
					BulletAttack(player);
					FMoveArray = array.AttackFunction05;
					
					

				}
				if (MovePattern[MoveArray] == 0) {

					Action = false;
				}
				//ŠÖ”‚ÌI‚í‚è‚ÉAction=false‚ÆŠÖ”“à‚Åg‚Á‚½•Ï”‚Ì‰Šú‰»‚ğ‚µ‚ë‚¨‚¨‚¨‚¨‚¨‚¨‚¨
				//ŠÖ”‚È‚¢‚Æ‚±‚É‚ÍAction=false‚ğ“ü‚ê‚é‚±‚ÆB
				break;
			}
			case MIDDLE:
			{
				if (MovePattern[MoveArray] == array.NormalAttack) {
					//’ÊíUŒ‚‚ÌƒR[ƒh‚Í‚±‚±
					MoveAttack(player);
					//Teleportation(player);
					FMoveArray = array.NormalAttack;
				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%‚ÌUŒ‚
					UndertaleAttack(player);
					//Action = false;
					FMoveArray = array.AttackFunction01;

				}
				if (MovePattern[MoveArray] == array.AttackFunction02) {
					//5%‚ÌUŒ‚
					/*UndertaleAttack(player);
					FMoveArray = array.AttackFunction02;*/
					//Action = false;
					
					Action = false;
					CoolTime = 0;
				}
				if (MovePattern[MoveArray] == array.AttackFunction03) {
					//5%‚ÌUŒ‚
					AsgoreAttack(player);					
					FMoveArray = array.AttackFunction03;
				}
				if (MovePattern[MoveArray] == array.AttackFunction04) {
					//5%‚ÌUŒ‚
					/*AsgoreAttack(player);
					
					FMoveArray = array.AttackFunction04;*/
					Action = false;
					CoolTime = 0;
				}
				if (MovePattern[MoveArray] == array.AttackFunction05) {
					//5%‚ÌUŒ‚
					//AsgoreAttack(player);
					BulletAttack(player);
					FMoveArray = array.AttackFunction05;
					/*Action = false;
					CoolTime = 0;*/
				}
				if (MovePattern[MoveArray] == 0) {
					Action = false;
				}
				//ŠÖ”‚ÌI‚í‚è‚ÉAction=false‚ÆŠÖ”“à‚Åg‚Á‚½•Ï”‚Ì‰Šú‰»‚ğ‚µ‚ë‚¨‚¨‚¨‚¨‚¨‚¨‚¨
				//ŠÖ”‚È‚¢‚Æ‚±‚É‚ÍAction=false‚ğ“ü‚ê‚é‚±‚ÆB
				break;
			}
			case FAR_1:
			{
				if (MovePattern[MoveArray] == array.NormalAttack) {
					//’ÊíUŒ‚‚ÌƒR[ƒh‚Í‚±‚±
					
					BulletAttack(player);
					//nyokkiAttack(player);
					FMoveArray = array.NormalAttack;

				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%‚ÌUŒ‚
					//BulletAttack(player);
					UndertaleAttack(player);
					FMoveArray = array.AttackFunction01;
				}
				if (MovePattern[MoveArray] == array.AttackFunction02) {
					//5%‚ÌUŒ‚
					//BulletAttack(player);
					nyokkiAttack(player);
					FMoveArray = array.AttackFunction02;
				}
				if (MovePattern[MoveArray] == array.AttackFunction03) {
					//5%‚ÌUŒ‚
					/*BulletAttack(player);
					FMoveArray = array.AttackFunction03;*/
					Action = false;
					CoolTime = 0;
				}
				if (MovePattern[MoveArray] == array.AttackFunction04) {
					//5%‚ÌUŒ‚
					/*BulletAttack(player);
					FMoveArray = array.AttackFunction04;*/
					Action = false;
					CoolTime = 0;
					//CoolTime = 0;
				}
				if (MovePattern[MoveArray] == array.AttackFunction05) {
					//5%‚ÌUŒ‚
					/*BulletAttack(player);
					FMoveArray = array.AttackFunction05;*/
					Action = false;
					CoolTime = 0;
					
				}
				if (MovePattern[MoveArray] == 0) {
					Action = false;
				}
				//ŠÖ”‚ÌI‚í‚è‚ÉAction=false‚ÆŠÖ”“à‚Åg‚Á‚½•Ï”‚Ì‰Šú‰»‚ğ‚µ‚ë‚¨‚¨‚¨‚¨‚¨‚¨‚¨
				//ŠÖ”‚È‚¢‚Æ‚±‚É‚ÍAction=false‚ğ“ü‚ê‚é‚±‚ÆB
				break;
			}
			}
			break;

		case THREEQUARTERS:
			CoolTime = 40;

			switch (pattarn) {
			case NEAR_1:
			{
				if (MovePattern[MoveArray] == array.NormalAttack) {
					//’ÊíUŒ‚‚ÌƒR[ƒh‚Í‚±‚±
					//Teleportation(player);
					nyokkiAttack(player);
					FMoveArray = array.NormalAttack;
				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%‚ÌUŒ‚
					MoveAttack(player);
					FMoveArray = array.AttackFunction01;

				}
				if (MovePattern[MoveArray] == array.AttackFunction02) {
					//5%‚ÌUŒ‚
					UndertaleAttack(player);
					FMoveArray = array.AttackFunction02;
					
				}
				if (MovePattern[MoveArray] == array.AttackFunction03) {
					//5%‚ÌUŒ‚
					Action = false;
					CoolTime = 0;
					//FMoveArray = array.AttackFunction03;


				}
				if (MovePattern[MoveArray] == array.AttackFunction04) {
					//5%‚ÌUŒ‚
					
					Teleportation(player);
					FMoveArray = array.AttackFunction04;
					/*CoolTime = 0;
					Action = false;*/

				}
				if (MovePattern[MoveArray] == array.AttackFunction05) {
					//5%‚ÌUŒ‚
					CenterOfDarknessAttack(player);
					FMoveArray = array.AttackFunction05;

					

				}
				if (MovePattern[MoveArray] == 0) {

					Action = false;
				}
				//ŠÖ”‚ÌI‚í‚è‚ÉAction=false‚ÆŠÖ”“à‚Åg‚Á‚½•Ï”‚Ì‰Šú‰»‚ğ‚µ‚ë‚¨‚¨‚¨‚¨‚¨‚¨‚¨
				//ŠÖ”‚È‚¢‚Æ‚±‚É‚ÍAction=false‚ğ“ü‚ê‚é‚±‚ÆB
				break;
			}
			case MIDDLE:
			{
				if (MovePattern[MoveArray] == array.NormalAttack) {
					//’ÊíUŒ‚‚ÌƒR[ƒh‚Í‚±‚±
					nyokkiAttack(player);
					FMoveArray = array.NormalAttack;
				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%‚ÌUŒ‚
					MoveAttack(player);
					/*Action = false;*/
					FMoveArray = array.AttackFunction01;

				}
				if (MovePattern[MoveArray] == array.AttackFunction02) {
					//5%‚ÌUŒ‚
					UndertaleAttack(player);
					/*Action = false;*/
					FMoveArray = array.AttackFunction02;
					

				}
				if (MovePattern[MoveArray] == array.AttackFunction03) {
					//5%‚ÌUŒ‚
					/*Action = false;*/
					AsgoreAttack(player);
					FMoveArray = array.AttackFunction03;
				}
				if (MovePattern[MoveArray] == array.AttackFunction04) {
					//5%‚ÌUŒ‚
					
					Action = false;
					CoolTime = 0;
					//FMoveArray = array.AttackFunction04;
				}
				if (MovePattern[MoveArray] == array.AttackFunction05) {
					//5%‚ÌUŒ‚
					
					Action = false;
					CoolTime = 0;
					//FMoveArray = array.AttackFunction05;
				}
				if (MovePattern[MoveArray] == 0) {
					Action = false;
				}
				//ŠÖ”‚ÌI‚í‚è‚ÉAction=false‚ÆŠÖ”“à‚Åg‚Á‚½•Ï”‚Ì‰Šú‰»‚ğ‚µ‚ë‚¨‚¨‚¨‚¨‚¨‚¨‚¨
				//ŠÖ”‚È‚¢‚Æ‚±‚É‚ÍAction=false‚ğ“ü‚ê‚é‚±‚ÆB
				break;
			}
			case FAR_1:
			{
				if (MovePattern[MoveArray] == array.NormalAttack) {
					//’ÊíUŒ‚‚ÌƒR[ƒh‚Í‚±‚±
					/*Action = false;*/
					BulletAttack(player);
					FMoveArray = array.NormalAttack;

				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%‚ÌUŒ‚
					Action = false;
					CoolTime = 0;
					//FMoveArray = array.AttackFunction01;
				}
				if (MovePattern[MoveArray] == array.AttackFunction02) {
					//5%‚ÌUŒ‚
					UndertaleAttack(player);
					FMoveArray = array.AttackFunction02;
					//CoolTime = 20;
				}
				if (MovePattern[MoveArray] == array.AttackFunction03) {
					//5%‚ÌUŒ‚
					AsgoreAttack(player);
					FMoveArray = array.AttackFunction03;
				}
				if (MovePattern[MoveArray] == array.AttackFunction04) {
					//5%‚ÌUŒ‚
					Action = false;
					CoolTime = 0;
					//FMoveArray = array.AttackFunction04;
				}
				if (MovePattern[MoveArray] == array.AttackFunction05) {
					//5%‚ÌUŒ‚
					CenterOfDarknessAttack(player);
					FMoveArray = array.AttackFunction05;
				}
				if (MovePattern[MoveArray] == 0) {
					Action = false;
				}
				//ŠÖ”‚ÌI‚í‚è‚ÉAction=false‚ÆŠÖ”“à‚Åg‚Á‚½•Ï”‚Ì‰Šú‰»‚ğ‚µ‚ë‚¨‚¨‚¨‚¨‚¨‚¨‚¨
				//ŠÖ”‚È‚¢‚Æ‚±‚É‚ÍAction=false‚ğ“ü‚ê‚é‚±‚ÆB
				break;
			}
			}
			break;

		case HALF:
			CoolTime = 20;
			switch (pattarn) {
			case NEAR_1:
			{
				if (MovePattern[MoveArray] == array.NormalAttack) {
					//’ÊíUŒ‚‚ÌƒR[ƒh‚Í‚±‚±
					Teleportation(player);
					
					FMoveArray = array.NormalAttack;
				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%‚ÌUŒ‚
					nyokkiAttack(player);
					
					FMoveArray = array.AttackFunction01;
					
				}
				if (MovePattern[MoveArray] == array.AttackFunction02) {
					//5%‚ÌUŒ‚
					CenterOfDarknessAttack(player);
					
					FMoveArray = array.AttackFunction02;
					/*Action = false;*/

				}
				if (MovePattern[MoveArray] == array.AttackFunction03) {
					//5%‚ÌUŒ‚
					BulletAttack(player);
					
					FMoveArray = array.AttackFunction03;
				}
				if (MovePattern[MoveArray] == array.AttackFunction04) {
					//5%‚ÌUŒ‚
					
					Action = false;
					CoolTime = 0;
					//FMoveArray = array.AttackFunction04;
					//CoolTime = 20;
				}
				if (MovePattern[MoveArray] == array.AttackFunction05) {
					//5%‚ÌUŒ‚
					UndertaleAttack(player);
					Action = false;
					CoolTime = 0;
					//FMoveArray = array.AttackFunction05;
				}
				if (MovePattern[MoveArray] == 0) {
					Action = false;
				}
				//ŠÖ”‚ÌI‚í‚è‚ÉAction=false‚ÆŠÖ”“à‚Åg‚Á‚½•Ï”‚Ì‰Šú‰»‚ğ‚µ‚ë‚¨‚¨‚¨‚¨‚¨‚¨‚¨
				//ŠÖ”‚È‚¢‚Æ‚±‚É‚ÍAction=false‚ğ“ü‚ê‚é‚±‚ÆB
				break;
			}
			case MIDDLE:
			{
				if (MovePattern[MoveArray] == array.NormalAttack) {
					//’ÊíUŒ‚‚ÌƒR[ƒh‚Í‚±‚±
					Teleportation(player);
					
					FMoveArray = array.NormalAttack;
				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%‚ÌUŒ‚
					Action = false;
					CoolTime = 0;
					//FMoveArray = array.AttackFunction01;
				}
				if (MovePattern[MoveArray] == array.AttackFunction02) {
					//5%‚ÌUŒ‚
					CenterOfDarknessAttack(player);
					
					FMoveArray = array.AttackFunction02;
				}
				if (MovePattern[MoveArray] == array.AttackFunction03) {
					//5%‚ÌUŒ‚
					BulletAttack(player);
					
					FMoveArray = array.AttackFunction03;
				}
				if (MovePattern[MoveArray] == array.AttackFunction04) {
					//5%‚ÌUŒ‚
					AsgoreAttack(player);
					FMoveArray = array.AttackFunction04;
				}
				if (MovePattern[MoveArray] == array.AttackFunction05) {
					//5%‚ÌUŒ‚
					Action = false;
					FMoveArray = array.AttackFunction05;
				}
				if (MovePattern[MoveArray] == 0) {
					Action = false;
				}
				//ŠÖ”‚ÌI‚í‚è‚ÉAction=false‚ÆŠÖ”“à‚Åg‚Á‚½•Ï”‚Ì‰Šú‰»‚ğ‚µ‚ë‚¨‚¨‚¨‚¨‚¨‚¨‚¨
				//ŠÖ”‚È‚¢‚Æ‚±‚É‚ÍAction=false‚ğ“ü‚ê‚é‚±‚ÆB
				break;
			}
			case FAR_1:
			{
				if (MovePattern[MoveArray] == array.NormalAttack) {
					//’ÊíUŒ‚‚ÌƒR[ƒh‚Í‚±‚±
					Teleportation(player);
					
					FMoveArray = array.NormalAttack;

				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%‚ÌUŒ‚
					Action = false;
					CoolTime = 0;
					//FMoveArray = array.AttackFunction01;
					
				}
				if (MovePattern[MoveArray] == array.AttackFunction02) {
					//5%‚ÌUŒ‚
					CenterOfDarknessAttack(player);
					
					FMoveArray = array.AttackFunction02;
					
				}
				if (MovePattern[MoveArray] == array.AttackFunction03) {
					//5%‚ÌUŒ‚
					Action = false;
					CoolTime = 0;
					//FMoveArray = array.AttackFunction03;
					//Action = false;

				}
				if (MovePattern[MoveArray] == array.AttackFunction04) {
					//5%‚ÌUŒ‚
					AsgoreAttack(player);
					
					FMoveArray = array.AttackFunction04;
				}
				if (MovePattern[MoveArray] == array.AttackFunction05) {
					//5%‚ÌUŒ‚
					UndertaleAttack(player);
					
					FMoveArray = array.AttackFunction05;
				}
				if (MovePattern[MoveArray] == 0) {
					Action = false;
				}
				//ŠÖ”‚ÌI‚í‚è‚ÉAction=false‚ÆŠÖ”“à‚Åg‚Á‚½•Ï”‚Ì‰Šú‰»‚ğ‚µ‚ë‚¨‚¨‚¨‚¨‚¨‚¨‚¨
				//ŠÖ”‚È‚¢‚Æ‚±‚É‚ÍAction=false‚ğ“ü‚ê‚é‚±‚ÆB
				break;
			}
			}
			break;


		}
	}
}

void Boss2::RandMoveSet()
{


	for (int i = 0; i < MAX2_PATTERN; i++) {
		if (0 <= i && i <= 9) {
			MovePattern[i] = array.AttackFunction01;

		}
		else
			if (9 <= i && i <= 19) {
				MovePattern[i] = array.AttackFunction02;

			}
			else
				if (19 <= i && i <= 29) {
					MovePattern[i] = array.AttackFunction03;

				}
				else
					if (29 <= i && i <= 39) {
						MovePattern[i] = array.AttackFunction04;

					}
					else
						if (39 <= i && i <= 49) {
							MovePattern[i] = array.AttackFunction05;

						}
						else
							if (MovePattern[i] == 0) {
								MovePattern[i] = array.NormalAttack;

							}
	}


}

int Boss2::ReloadMove(int Movearry)
{
	int rand = Randam::RAND(0, 5);
	if (rand == 0) {
		if (MoveArray == array.NormalAttack) {
			rand = Randam::RAND(0, 5);
		}
		else { return array.NormalAttack; }
	}
	if (rand == 1) {
		if (MoveArray == array.AttackFunction01) {
			rand = Randam::RAND(0, 5);
		}
		else { return array.AttackFunction01; }
	}
	if (rand == 2) {
		if (MoveArray == array.AttackFunction02) {
			rand = Randam::RAND(0, 5);
		}
		else { return array.AttackFunction02; }
	}
	if (rand == 3) {
		if (MoveArray == array.AttackFunction03) {
			rand = Randam::RAND(0, 5);
		}
		else { return array.AttackFunction03; }
	}
	if (rand == 4) {
		if (MoveArray == array.AttackFunction04) {
			rand = Randam::RAND(0, 5);
		}
		else { return array.AttackFunction04; }
	}
	if (rand == 5) {
		if (MoveArray == array.AttackFunction05) {
			rand = Randam::RAND(0, 5);
		}
		else { return array.AttackFunction05; }
	}
}

void Boss2::CenterOfDarknessAttack(PlayerMain& player) {
	keep.theta += M_PI / 60;
	keep.YMove = sinf(keep.theta) * 1;
	Pos.y += keep.YMove;
	if (isCenteroOfDarknessMove == true) {
		if (isGetPos == false) {
			saveBoss2x = Pos.x;
			savePlayerx = player.GetPlayerQuad().GetCenter().x;
			isGetPos = true;
		}
		Pos.x = Easing::easing(centerOfDarknessMoveT, saveBoss2x, savePlayerx, 0.01f, Easing::easeInOutQuint);
		if (centerOfDarknessMoveT >= 1.0f) {
			isCenteroOfDarknessMove = false;
		}
	}
	else {
		AnimeSelect = Charge;
		--centerOfDarknessCooltime;
		Vec2 playertoboss = (Pos - player.GetPlayerQuad().GetCenter()).Normalized() * gravityPower * (1.0 - gravityT);
		player.SetPlayerPos({ player.GetPlayerPos().x + playertoboss.x, player.GetPlayerPos().y });
		if (centerOfDarknessCooltime >= 250) {//‚à‚Æ‚à‚Æ150
			
			
			if (isGetNyokkiPos == false) {
				for (int i = 0; i < 3; i++) {
					
					centerNyokki[i] = { {(Pos.x - 54.0f - centerNyokkispace - centerNyokkiWidth + (centerNyokkispace + centerNyokkiWidth) * i) * 1.0f ,centerNyokkiHeight * 1.0f},centerNyokkiWidth, centerNyokkiHeight};
				}
				isGetNyokkiPos = true;
				iscenterNyokki = true;
			}

			if (centerNyokkistats == Up) {
				centerNyokkiUpAnimationFrame++;
			}

			if (centerNyokkiUpAnimationFrame >= centerNyokkiSwitchAnimationFrame * centerNyokkiUpSheets) {
				centerNyokkistats = Keep;
				iscenterNyokkiCollision = true;

			}
			if (centerNyokkistats == Keep) {
				sound.SoundEffect(sound.jisin, 1.0f, "./Resources/sounds/jisin.mp3", true);

				centerNyokkiKeepAnimationFrame++;
			}
			
			isCenterOfDarkness = true;
		}
		else if (centerOfDarknessCooltime >= 0) {
			gravityT += 0.01;
			gravityT = Clamp::clamp(gravityT, 0.0f, 1.0f);
			isFeedCenterNyokki = true;
			iscenterNyokkiCollision = false;
			isCenterOfDarkness = false;
			if (centerNyokkiT[0] >= 1.0f) {
				iscenterNyokki = false;
				Novice::StopAudio(sound.jisin.Handle);

			}
		}
		else {
			gravityT = 0.0f;
			Action = false;
			CoolTime = 220;
			centerOfDarknessCooltime = saveCenterOfDarknessCooltime;
			centerOfDarknessMoveT = 0.0f;
			isCenteroOfDarknessMove = true;
			isGetPos = false;
			isGetNyokkiPos = false;
			isGetcenterNyokki = false;
			centerNyokkiUpAnimationFrame = 0;
			centerNyokkiKeepAnimationFrame = 0;
			iscenterNyokkiCollision = false;
			isFeedCenterNyokki = false;
			iscenterNyokki = false;
			centerNyokkistats = Up;
			for (int i = 0; i < 3; i++) {
				centerNyokkiUpSrcX[i] = 0;
				centerNyokkiKeepSrcX[i] = 0;
				centerNyokkiT[i] = 0.0f;
			}
			AnimeSelect = Normal;
		}
	}
	
}

void Boss2::BulletAttack(PlayerMain& player) {
	AnimeSelect = BulletAttack2;
	keep.theta += M_PI / 60;
	keep.YMove = sinf(keep.theta) * 1;
	Pos.y += keep.YMove;
	if (bulletAttackCoolTime == 2000) {
	}
	bulletAttackCoolTime--;
	isBulletAttack = true;
	
	for (int i = 0; i < swordNum; i++) {
		//theta‚ğ‰ÁZ
		if (isRelease == false) {
			theta[i] += M_PI / 70.0f;
			initialSword = { Pos,30,30,0 };
		}
		//theta‚ª0ˆÈã‚É‚È‚Á‚½‚çoŒ»‚³‚¹‚é
		if (theta[i] >= 0 && isSword[i] == false) {
			isSword[i] = true;
			
		}
		
	
		if (theta[swordNum - 1] <= 0) {
			
				sound.SoundEffect(sound.Bulletattack, 0.03f, "./Resources/sounds/bulletattackgo.wav", true);

		}
		
			
		if (isRelease == false) {
			sword[i] = initialSword.Rotate(initialSword, radius, theta[i]);
		}

		
	}

	if (theta[swordNum - 1] >= 0) {
		if (isRelease == false) {
			radius = Easing::easing(radiusT, 200, 100, 0.02f, Easing::easeInOutQuint);
		}
			
	}
	
	
	if (radiusT >= 1.0f) {
		if (isRelease == false) {

			sound.SoundEffect(sound.Bulletattackgo, 0.4f, "./Resources/sounds/bulletattack.wav", false);
		}
		isRelease = true;
	}

	for (int i = 0; i < swordNum; i++) {
		if(isRelease == true ) {//ÅŠú‚Ì’e‚Ìtheta‚ª0ˆÈã‚É‚È‚Á‚½‚ç
			
				
				
				bulletAttackCoolTime--;
				sword[i] = initialSword.Rotate(initialSword, radius, theta[i]);
				if (swordT[i] < 1.0f && isOrbit[i] == false) {
					orbitColor[i] = Feed::Feedin(swordT[i], 0.05f, orbitColor[i]);
					AnimeSelect = BulletAttack1;
				}
				if (swordT[i] >= 1.0f && isOrbit[i] == false) {
					isOrbit[i] = true;
					swordT[i] = 0.0f;
				}
				if (isOrbit[i] == true) {
					AnimeSelect = BossNormal_gra;
					orbitColor[i] = Feed::Feedout(swordT[i], 0.05f, orbitColor[i]);
				}
				//•úo‚µ‚ÄÅ‰‚ÌƒtƒŒ[ƒ€‚¾‚¯
				if (getFrag[i] == false) {
					swordT[i] = 0.0f;
					effectSword[i] = sword[i];
					effectSword[i].LeftBottom = sword[i].Rotate(sword[i], mostRadius, theta[i]).LeftBottom;
					effectSword[i].RightBottom = sword[i].Rotate(sword[i], mostRadius, theta[i]).RightBottom;
					getFrag[i] = true;
				}
				
				swordEffect.Update(true, sword[i]);
			
		}
	}
	
	if (bulletAttackCoolTime <= 0) {
		radiusT = 0.0f;
		isRelease = false;
		bulletAttackCoolTime = saveBulletAttackCoolTime;
		radius = 200.0f;
		for (int i = 0; i < swordNum; i++) {
			orbitColor[i] = RED;
			theta[i] = -(M_PI * 2.0f / swordNum ) * i - 1.0f * M_PI / 180;
			isSword[i] = false;
			getFrag[i] = false;
			swordT[i] = 0.0f;
			isOrbit[i] = false;
			isBulletAttack = false;
			sword[i] = { {9999,9999},0,0 };
		}
		Action = false;
		AnimeSelect = Normal;
	}
}

void Boss2::UndertaleAttack(PlayerMain& player) {
	keep.theta += M_PI / 60;
	keep.YMove = sinf(keep.theta) * 1;
	Pos.y += keep.YMove;
	isUndertaleAttack = true;
	undertaleFrame--;
	AnimeSelect = Charge;
	if (undertaleFrame <= 180 && undertaleFrame > 0) {//‚à‚Æ120
		chaseEffect.feedSpeed = 0.03;
		isUndertaleCollision = true;
		isFeedrotateBullet = true;
		emitchaseEffect = false;
	}

	if (rotatetheta[0] >= 0 && isRotateBullet[0] == false) {
		saveUndertalePos = Pos;
		initialRotateBullet = { {player.GetPlayerPos().x,player.GetPlayerPos().y + upCircleY},30,30,0 };
 		savePlayerPos = { player.GetPlayerPos().x,player.GetPlayerPos().y + upCircleY };
	}
	else {
		if (xMove >= wideMostMove && xSpeed) {
			xSpeed = -xSpeed;
		}
		if (xMove <= -100 && xSpeed <= 0) {
			xSpeed = -xSpeed;
		}

		xMove += xSpeed;
		ytheta += ythetaSpeed;
		yMove = sinf(ytheta) * 30;
		initialRotateBullet = { {savePlayerPos.x + xMove, savePlayerPos.y + yMove},30,30,0 };
	}
	
	if (undertaleMoveT < 1.0f) {
		if (savePlayerPos.x <= 1200) {
			Pos.x = Easing::easing(undertaleMoveT, saveUndertalePos.x, initialRotateBullet.GetCenter().x + 700.0f, 0.02, Easing::easeInOutQuart);
		}
		else {
			Pos.x = Easing::easing(undertaleMoveT, saveUndertalePos.x, initialRotateBullet.GetCenter().x - 700.0f, 0.02, Easing::easeInOutQuart);

		}
	}
		
	

	for (int i = 0; i < rotateBulletNum; i++) {
		rotatetheta[i] += rotatethetaSpeed;
		if (rotatetheta[i] >= 0 && isRotateBullet[i] == false) {
				isRotateBullet[i] = true;
		}

		if (isRotateBullet[i] == true) {
			if (isRotateBullet2[i] == false) {
				sound.SoundEffect(sound.under, 0.1f, "./Resources/sounds/under.wav", false);
				isRotateBullet2[i] = true;
			}
			//‰ñ“]
			rotateBullet[i] = initialRotateBullet.Rotate(initialRotateBullet, bulletRadius, rotatetheta[i]);
		}
		if (rotateBulletT[i] >= 1.0f) {
			isRotateBullet[i] = false;
			AnimeSelect = Normal;
		}
	}
	if (undertaleFrame <= 570) {
		chaseEffect.Update(emitchaseEffect, { Pos,30,30 });
		for (int i = 0; i < chaseBulletNum; i++) {
			chaseframe[i]--;
			if (isGet[i] == false && chaseEffect.particles[i].isActive == true) {
				chaseframe[i]--;
				if (isGet[i] == false && chaseEffect.particles[i].isActive == true) {
					chaseVec[i] = player.GetPlayerPos() - chaseEffect.particles[i].quad.GetCenter();
					sound.SoundEffect(sound.underdan, 0.5f, "./Resources/sounds/underdan.wav", false);
					isGet[i] = true;
				}
			}

			if (chaseEffect.particles[i].isActive == true) {
				if (chaseframe[i] <= 0) {
					playerToEffect[i] = player.GetPlayerPos() - chaseEffect.particles[i].quad.GetCenter();
					leftVec[i] = chaseVec[i].Rotation(chaseTheta);
					rightVec[i] = chaseVec[i].Rotation(-chaseTheta);

					float rightCross = rightVec[i].Cross(playerToEffect[i]);
					float leftCross = leftVec[i].Cross(playerToEffect[i]);

					if (rightCross >= 0.0f && leftCross <= 0.0f) {
						chaseVec[i] = playerToEffect[i];
					}

					if (rightCross <= 0.0f && leftCross >= 0.0f) {
						if (-rightCross > leftCross) {
							chaseVec[i] = rightVec[i];
						}
						else {
							chaseVec[i] = leftVec[i];
						}
					}

					if (rightCross > 0.0f && leftCross > 0.0f) {
						chaseVec[i] = leftVec[i];
					}

					if (rightCross < 0.0f && leftCross < 0.0f) {
						chaseVec[i] = rightVec[i];
					}

					chaseEffect.particles[i].maxDirection = chaseVec[i];
					chaseEffect.particles[i].minDirection = chaseVec[i];
					chaseframe[i] = savechaseframe;
				}
			}
		}
	}

		if (undertaleFrame <= 0) {
			chaseEffect.feedSpeed = 0.0f;
			chaseEffect.addEffectCooltime = 40;
			xMove = 0.0f;
			yMove = 0;
			ytheta = 0.0f;
			rotateT = 0.0f;
			undertaleMoveT = 0.0f;
			isFeedrotateBullet = false;
			emitchaseEffect = true;
			undertaleFrame = saveUndertaleFrame;
			isUndertaleCollision = false;
			for (int i = 0; i < chaseBulletNum; i++) {
				chaseframe[i] = 0.0f;
				isGet[i] = false;
			}

			for (int i = 0; i < rotateBulletNum; i++) {
				rotatetheta[i] = -(M_PI * 2.0f / rotateBulletNum) * i;
				isSword[i] = false;
				isRotateBullet[i] = false;
				isRotateBullet2[i] = false;
				rotateBulletT[i] = 0.0f;
			}
			isUndertaleAttack =false;
			
			Action = false;
			CoolTime = 150;
		}
	
}

void Boss2::nyokkiAttack(PlayerMain& player) {
	if (isdropMove == false) {
		AnimeSelect = Nyokki1;
		if (isSaveBossY == false) {
			saveBossY = Pos.y;
			isSaveBossY = true;
		}
		Pos.y = Easing::easing(dropMoveT,saveBossY, saveBossY + upDropMove,upSpeed,Easing::easeInOutQuart);
		if (dropMoveT >= 1.0f) {
			isdropMove = true;
		}
	}
	if (isSaveBossY2 == false && isdropMove == true) {
		saveBossY2 = Pos.y;
		isSaveBossY2 = true;
		isdrop = true;
	}
	if (isdrop == true) {
		AnimeSelect = Nyokki2;
		Pos.y  = Easing::easing(dropT, saveBossY2, underPos, dropSpeed, Easing::easeInOutQuint);
		if (dropT >= 0.4f) {
			isNyokki = true;
		}
		
		if (dropT >= 1.0f) {
			
			isdrop = false;
			AnimeSelect = Nyokki3;
		}
		if (dropT > 0.6f) {
			if (isdrop == true) {
				sound.SoundEffect(sound.tatsumaki, 1.0f, "./Resources/sounds/JumpAttack.mp3", true);
			}
			
		}
	}
	if (isNyokki == true ) {
		//nyokkiˆ—
		

		if (isGetNyokkiPos == false) {
			for (int i = 0; i < nyokkiNum / 2; i++) {
				leftNyokki[i].Quad = Quad({ Pos.x - 54 - nyokkiWidth - i * nyokkiWidth - i * space , nyokkiHeight * 1.0f }, nyokkiWidth, nyokkiHeight);
				rightNyokki[i].Quad = Quad({ Pos.x + 54 + i * nyokkiWidth + i * space , nyokkiHeight * 1.0f }, nyokkiWidth, nyokkiHeight);
			}
			isNyokki = true;
			isGetNyokkiPos = true;
		}
		if (nyokkistats == Up) {
			nyokkiUpAnimationFrame++;
		}

		if (nyokkiUpAnimationFrame >= nyokkiSwitchAnimationFrame * nyokkiUpSheets) {
			nyokkistats = Keep;
			isNyokkiCollsion = true;

		}
		if (nyokkistats == Keep) {
			nyokkiKeepAnimationFrame++;
		}
		if (nyokkiKeepAnimationFrame >= 20) {
			isFeedNyokki = true;
			isNyokkiCollsion = false;
		}
		if (leftNyokkiT[nyokkiNum / 2 - 1] >= 1.0f) {
			isreturn = true;
			isNyokki = false;
		}
		
	}

	if (isNyokki == false && isreturn == true) {
		if (isSaveBossY3 == false) {
			saveUnderBossY = Pos.y;
			isSaveBossY3 = true;
		}
		AnimeSelect = Normal;
		Pos.y = Easing::easing(returnMoveT, saveUnderBossY, saveBossY, upSpeed, Easing::easeInOutQuint);
		if (returnMoveT >= 1.0f) {
			dropT = 0.0f;
			isSaveBossY = false;
			isSaveBossY2 = false;
			isSaveBossY3 = false;
			isdropMove = false;
			dropMoveT = 0.0f;
			returnMoveT = 0.0f;
			isdrop = false;
			Action = false;
			isNyokki = false;
			isreturn = false;
			isGetNyokkiPos = false;
			nyokkistats = Up;
			nyokkiUpAnimationFrame = 0;
			nyokkiKeepAnimationFrame = 0;
			isNyokkiCollsion = false;
			isFeedNyokki = false;
			for (int i = 0; i < nyokkiNum / 2; i++) {
				leftNyokkiUpSrcX[i] = 0;
				leftNyokkiKeepSrcX[i] = 0;
				rightNyokkiUpSrcX[i] = 0;
				rightNyokkiKeepSrcX[i] = 0;
				leftNyokkiT[i] = 0.0f;
				rightNyokkiT[i] = 0.0f;
				
			}
		}
	}

}

void Boss2::AsgoreAttack(PlayerMain& player) {
	keep.theta += M_PI / 60;
	keep.YMove = sinf(keep.theta) * 1;
	Pos.y += keep.YMove;
	if (setWhich == false) {
		if (player.GetPlayerQuad().GetCenter().x <= 1200) {
			EmitPos = { 240.0f,SCREEN_HEIGHT - Floor };
			distanceSpeed = 6.0f;
			allSpeed = { 4.0f,-2.0f };
		}
		else {
			EmitPos = { 2400.0f - 240,SCREEN_HEIGHT - Floor };
			distanceSpeed = -6.0f;
			allSpeed = { -4.0f,-2.0f };
		}
		setWhich = true;
	}

	if (isMoveCenter == false) {
		if (isGetAsgore == false) {
			savePosAsgore = Pos;
			isGetAsgore = true;
		}
		Pos.x = Easing::easing(AsgoreMoveTx, savePosAsgore.x, EmitPos.x , 0.01f, Easing::easeInOutQuint);
		Pos.y = Easing::easing(AsgoreMoveTy, savePosAsgore.y, EmitPos.y - 192 / 2, 0.01f, Easing::easeInOutQuint);
	}
	if (AsgoreMoveTx >= 1.0f) {
		isMoveCenter = true;
		isAsgoreAttack = true;
	}
	if (isAsgoreAttack == true) {
		sound.SoundEffect(sound.asgore, 0.6f, "./Resources/sounds/asgore.wav", true);
		AnimeSelect = Charge;
		coolTime--;
		EmitPos.x += distanceSpeed;
		if (emitActionNum >= 0) {
			if (coolTime <= 0) {
				for (int i = 0; i < BulletOriginNum; i++) {
					AsgoreBullet[emitNum].quad = { EmitPos,Asgorewidth,Asgorewidth };
					AsgoreBullet[emitNum].isBullet = true;
					AsgoreBullet[emitNum].distance = distance[i];
					emitNum++;
				}
				coolTime = EmitCoolTime;
				emitActionNum--;
			}
		}
		for (int i = 0; i < emitNum; i++) {
			AsgoreBullet[i].quad = AsgoreBullet[i].quad + AsgoreBullet[i].distance * distanceSpeed;
			AsgoreBullet[i].quad = AsgoreBullet[i].quad + allSpeed;
			if (AsgoreBullet[i].quad.GetCenter().y >= SCREEN_HEIGHT - Floor + Asgorewidth || AsgoreBullet[i].quad.GetCenter().y <= -Asgorewidth - Floor || AsgoreBullet[i].quad.GetCenter().x <= -Asgorewidth || AsgoreBullet[i].quad.GetCenter().x >= 2400 + Asgorewidth) {
				AsgoreBullet[i].isBullet = false;
			}
		}
		if (emitActionNum <= 0) {
			if (isGetPosRetrun == false) {
				savePosreturn = Pos;
				isGetPosRetrun = true;
			}
			Pos.x = Easing::easing(AsgoreReturnTx, savePosreturn.x, 1200.0f, 0.02f, Easing::easeInOutQuint);
			Pos.y = Easing::easing(AsgoreReturnTy, savePosreturn.y, savePosAsgore.y, 0.02f, Easing::easeInOutQuint);
			isWait = true;
		}
		else {
			Pos.x = EmitPos.x;
		}
		if (isWait == true) {
			waitTime--;
		}
		if (waitTime <= 0) {
			isAsgoreFeed = true;
		}
		if (isAsgoreFeed) {
			for (int i = 0; i < emitNum; i++) {
				if (AsgoreBullet[i].t >= 1.0f) {
					EmitPos = { 0.0f,SCREEN_HEIGHT - Floor };
					coolTime = 0;
					for (int i = 0; i < emitNum; i++) {
						AsgoreBullet[i].isBullet = false;
						AsgoreBullet[i].t = 0.0f;
					}
					emitNum = 0;
					emitActionNum = saveEmitActionNum;
					isMoveCenter = false;
					isGetAsgore = false;
					AsgoreMoveTx = 0.0f;
					AsgoreMoveTy = 0.0f;
					isAsgoreAttack = false;
					isWait = false;
					waitTime = saveWaitTime;
					isAsgoreFeed = false;
					isGetPosRetrun = false;
					AsgoreReturnTx = 0.0f;
					AsgoreReturnTy = 0.0f;
					setWhich = false;
					Action = false;
					CoolTime = 150;
					AnimeSelect = Normal;
					break;
				}
			}
		}			
		
	}
}

void Boss2::MoveAttack(PlayerMain& player) {
	keep.theta += M_PI / 60;
	keep.YMove = sinf(keep.theta) * 1;
	Pos.y += keep.YMove;
	if (setWhich == false) {
		if (player.GetPlayerQuad().GetCenter().x <= 1200) {
			LastPosx = 2100.0f;
			startPosx = 300.0f;
 			moveAttackSpeed = 5.0f;
			iswhichlr = false;
		}
		else {
			LastPosx = 300.0f;
			startPosx = 2100.0f;
			moveAttackSpeed = -5.0f;
			iswhichlr = true;
		}
		setWhich = true;
	}
	if (issavePosMoveAttack == false) {
		savePosMoveAttack = Pos;
		issavePosMoveAttack = true;
	}
	if (ismoveMoveAttack == false) {
		Pos.x = Easing::easing(moveMoveAttackTx, savePosMoveAttack.x, startPosx, 0.01f, Easing::easeInOutQuint);
		if (moveMoveAttackTx >= 1.0f) {
			ismoveMoveAttack = true;
		}
	}
	if (ismoveMoveAttack == true) {
		AnimeSelect = Charge;

		if (ismovexMoveAttack == false) {
			Pos.x += moveAttackSpeed;
		}
		for (int i = 0; i < 4; i++) {
			
			movetheta[i] += movethetaSpeed;
			moveBullet[i] = initialmoveBullet.Rotate(initialmoveBullet, movetheta[i]) + Pos;
			if (movetheta[i] >= 0.0f) {
				ismoveBullet[i] = true;
			}
			
		}
		for (int i = 0; i < 16; i++) {
			
			if (i < 4) {
				if (ismoveBullet[0] == true) {
					if (ismoveBullet2[0] == false) {
						sound.SoundEffect(sound.moveattack, 0.5f, "./Resources/sounds/moveattack.wav",false);
						ismoveBullet2[0] = true;
					}
					movemovetheta[i] += movemovethetaSpeed;
					movemoveBullet[i] = initialmovemoveBullet.Rotate(initialmovemoveBullet, movemovetheta[i]) + moveBullet[0].GetCenter();
				}
			}
			else if (i < 8) {
				if (ismoveBullet[1] == true) {
					if (ismoveBullet2[1] == false) {
						sound.SoundEffect(sound.moveattack, 0.5f, "./Resources/sounds/moveattack.wav", false);
						ismoveBullet2[1] = true;
					}
					movemovetheta[i] += movemovethetaSpeed;
					movemoveBullet[i] = initialmovemoveBullet.Rotate(initialmovemoveBullet, movemovetheta[i]) + moveBullet[1].GetCenter();
				}
			}
			else if (i < 12) {
				if (ismoveBullet[2] == true) {
					if (ismoveBullet2[2] == false) {
						sound.SoundEffect(sound.moveattack, 0.5f, "./Resources/sounds/moveattack.wav", false);
						ismoveBullet2[2] = true;
					}
					movemovetheta[i] += movemovethetaSpeed;
					movemoveBullet[i] = initialmovemoveBullet.Rotate(initialmovemoveBullet, movemovetheta[i]) + moveBullet[2].GetCenter();
				}
			}
			else if (i < 16) {
				if (ismoveBullet[3] == true) {
					if (ismoveBullet2[3] == false) {
						sound.SoundEffect(sound.moveattack, 0.5f, "./Resources/sounds/moveattack.wav", false);
						ismoveBullet2[3] = true;
					}
					movemovetheta[i] += movemovethetaSpeed;
					movemoveBullet[i] = initialmovemoveBullet.Rotate(initialmovemoveBullet, movemovetheta[i]) + moveBullet[3].GetCenter();
				}
			}

			if (movemovetheta[i] >= 0.0f) {
				ismovemoveBullet[i] = true;
			}
		}
	}
	if (Pos.x <= LastPosx && iswhichlr == true) {
		ismovexMoveAttack = true;
		moveIsFeedout = true;
	}
	if (Pos.x >= LastPosx && iswhichlr == false) {
		ismovexMoveAttack = true;
		moveIsFeedout = true;
	}
	if (moveAttackBulletFeedoutT[0] >= 1.0f) {
		for (int i = 0; i < 4; i++) {
			ismoveBullet[i] = false;
			ismoveBullet2[i] = false;
			movetheta[i] = -(2 * M_PI / 4.0f) * i;
			moveBullet[i] = initialmoveBullet;
			moveAttackBulletFeedinT[i] = 0.0f;
			moveAttackBulletFeedoutT[i] = 0.0f;
		}
		for (int i = 0; i < 16; i++) {
			if (i < 4) {
				movemovetheta[i] = -(2 * M_PI / 4.0f) * i + 1;
			}
			else if (i < 8) {
				movemovetheta[i] = -(2 * M_PI / 4.0f) * (i - 4 + 1);
			}
			else if (i < 12) {
				movemovetheta[i] = -(2 * M_PI / 4.0f) * (i - 8 + 1);
			}
			else if (i < 16) {
				movemovetheta[i] = -(2 * M_PI / 4.0f) * (i - 12 + 1);
			}
			movemoveAttackBulletFeedinT[i] = 0.0f;
			movemoveAttackBulletFeedoutT[i] = 0.0f;
			movemoveBullet[i] = initialmovemoveBullet;
			ismovemoveBullet[i] = false;
		}
		issavePosMoveAttack = false;
		moveIsFeedout = false;
		ismoveMoveAttack = false;
		moveMoveAttackTx = 0.0f;
		ismovexMoveAttack = false;
		setWhich = false;
		Action = false;
		AnimeSelect = Normal;
	}

}

void Boss2::Teleportation(PlayerMain& player) {
	keep.theta += M_PI / 60;
	keep.YMove = sinf(keep.theta) * 1;
	Pos.y += keep.YMove;
	if (GetTeleportPos == false) {
		int num = Randam::RAND(0, 3);
		if (num == 0) {
			TeleportPos = { player.GetPlayerPos().x - 600.0f,Pos.y };
		}
		if (num == 1) {
			TeleportPos = { player.GetPlayerPos().x - 600.0f,Pos.y };
		}
		if (num == 2) {
			TeleportPos = { player.GetPlayerPos().x + 600.0f,Pos.y };
		}
		if (num == 3) {
			TeleportPos = { player.GetPlayerPos().x + 600.0f,Pos.y };
		}
		TeleSavePos = Pos;
		GetTeleportPos = true;
	}
	if (isTeleport == false) {
		Pos.x = Easing::easing(TeleportTx, TeleSavePos.x, TeleportPos.x, 0.1f, Easing::easeInOutQuint);
		
		if (TeleportTx >= 1.0f) {
			sound.SoundEffect(sound.telepo, 0.6f, "./Resources/sounds/telepo.wav",false);
			isTeleport = true;
		}
	}
	if (isTeleport == true) {
		
		TelechaseEffect.Update(isTeleport, { Pos,30,30 });
		for (int i = 0; i < 1; i++) {
			
			
			if (TeleisGet[0] == false && TelechaseEffect.particles[0].isActive == true) {
				
				if (TeleisGet[0] == false && TelechaseEffect.particles[0].isActive == true) {
					TelechaseVec[0] = player.GetPlayerPos() - TelechaseEffect.particles[0].quad.GetCenter();
					sound.SoundEffect(sound.telepodan, 0.6f, "./Resources/sounds/telopodan.wav", false);

					TeleisGet[0] = true;
				}
			}
			if (TelechaseEffect.particles[0].isActive == true) {
				TeleChaceFrame--;
				if (chaseframe[0] <= 0) {
					TeleplayerToEffect[0] = player.GetPlayerPos() - TelechaseEffect.particles[i].quad.GetCenter();
					TeleleftVec[0] = TelechaseVec[0].Rotation(TelechaseTheta);
					TelerightVec[0] = TelechaseVec[0].Rotation(-TelechaseTheta);

						float rightCross = TelerightVec[0].Cross(TeleplayerToEffect[0]);
						float leftCross = TeleleftVec[0].Cross(TeleplayerToEffect[0]);

						if (rightCross >= 0.0f && leftCross <= 0.0f) {
							TelechaseVec[0] = TeleplayerToEffect[0];
						}

						if (rightCross <= 0.0f && leftCross >= 0.0f) {
							if (-rightCross > leftCross) {
								TelechaseVec[0] = TelerightVec[0];
							}
							else {
								TelechaseVec[0] = TeleleftVec[0];
							}
						}

						if (rightCross > 0.0f && leftCross > 0.0f) {
							TelechaseVec[0] = TeleleftVec[0];
						}

						if (rightCross < 0.0f && leftCross < 0.0f) {
							TelechaseVec[0] = TelerightVec[0];
						}

						TelechaseEffect.particles[0].maxDirection = TelechaseVec[0];
						TelechaseEffect.particles[0].minDirection = TelechaseVec[0];
						
					}
				}
				if (TeleChaceFrame <= 0) {
					TelechaseEffect.feedSpeed = 0.1;
					isTelechaseFeed = true;
					TeleChaceFrame = 120;
				}
				if (TelechaseEffect.particles[0].t >= 1.0f) {
					TelechaseEffect.feedSpeed = 0;
					TelechaseEffect.particles[0].t = 0.0f;
					TelechaseEffect.particles[0].isActive = false;
					GetTeleportPos = false;
					isTeleport = false;
					TeleportTx = 0.0f;
					isTelechaseFeed = false;
					
					TeleisGet[0] = false;
					TeleisFeedrotateBullet = false;
					TeleportNum--;
				}
			}
		
	}
	if (TeleportNum <= 0) {
		delayframe = savedelayframe;
		TeleportNum = 3;
		CoolTime = 120;
		Action = false;
	}
	
}

void Boss2::UpDate()
{




	Pos.y = Clamp::clamp(Pos.y, Size.y / 2, 10000);
	Pos.x = Clamp::clamp(Pos.x, Size.x / 2+200, (1920 * 1.25) - Size.x / 2-200);
	Quad_Pos.Quad::Quad(Pos, Size.x, Size.y, 0);
	//Novice::ScreenPrintf(500, 500, "HP:%d", HP);


	//UŒ‚‚ğ“–‚Ä‚ç‚ê‚½‚Ìˆ—
	if (isBossHit == true) {
		HP -= bossAttackHP;
		sound.SoundEffect(sound.playerattackhit,0.4f, "./Resources/sounds/PlayerAttackHit.wav");
		if (HP <= 0) {
			HP = 0;
			IsLife = false;
			BossDeathFlag = true;
			isGameClear = true;
		}
	};
	if (HP < ThreeQuarterHP) {
		
		HpColor = 0xFFFF00FF;
		if (HP < HalfHP) {
			
			HpColor = 0xFF4400FF;

		}
	}

	if (isRelease == true) {
		radius += 27;
	}
	
}

void Boss2::Set()
{
	Size = { 64,160 };
	Pos = { 1000,500 };
	Quad_Pos.Quad::Quad(Pos, Size.x, Size.y, 0);
	ImageSize = { 120,196 };
	ImageQuad.Quad::Quad(Pos, ImageSize.x, ImageSize.y, 0);
	IsLife = true;
}

void Boss2::Zanzou()
{
	Zanflame++;
	if (Zanflame > 100) Zanflame = 1;
	for (int i = 0; i < Max_Zan; i++) {
		if (Zanflame % 2 == 0 && zanzou[i].bSet == false) {

			zanzou[i].Pos = ImageQuad;
			zanzou[i].Gra = Boss_gra;
			zanzou[i].Size = ImageSize;
			zanzou[i].SrcX = SrcX;
			zanzou[i].LifeTime = 3;
			zanzou[i].bSet = true;
			break;

		}
		if (zanzou[i].bSet == true) {
			zanzou[i].LifeTime--;
			if (zanzou[i].LifeTime == 0) {
				zanzou[i].bSet = false;
			}
		}
	}
}

void Boss2::LoadGra()
{

	if (load == 0) {
		load = 1;
		Boss2HpBar_gra = Novice::LoadTexture("./Resources/images/Boss2HpBar.png");
		BossNormal_gra = Novice::LoadTexture("./Resources/images/Boss2/Boss2.png");
		BossNyokki1_gra = Novice::LoadTexture("./Resources/images/Boss2/Nyokki1.png");
		BossNyokki2_gra = Novice::LoadTexture("./Resources/images/Boss2/Nyokki2.png");
		BossNyokki3_gra = Novice::LoadTexture("./Resources/images/Boss2/Nyokki3.png");
		BossCharge_gra = Novice::LoadTexture("./Resources/images/Boss2/Charge.png");
		BossBulletAttack1_gra = Novice::LoadTexture("./Resources/images/Boss2/BulletAttack1.png");
		BossBulletAttack2_gra = Novice::LoadTexture("./Resources/images/Boss2/BulletAttack2.png");

		Boss_gra = BossNormal_gra;
	}
}

void Boss2::Animation()
{

	int PreSheets = 0;
	if (SrcX != 0) {
		PreSheets = SrcX / ImageSize.x;
	}

	switch (AnimeSelect)
	{
	case Normal:
		ImageSize = { 120,196 };
		ImageQuad.Quad::Quad(Pos, ImageSize.x, ImageSize.y, 0);
		Boss_gra = BossNormal_gra;
		break;
	case Nyokki1:
		ImageSize = { 88,200 };
		ImageQuad.Quad::Quad(Pos, ImageSize.x, ImageSize.y, 0);
		Boss_gra = BossNyokki1_gra;
		break;
	case Nyokki2:
		ImageSize = { 120,200 };
		ImageQuad.Quad::Quad(Pos, ImageSize.x, ImageSize.y, 0);
		Boss_gra = BossNyokki2_gra;
		break;
	case Nyokki3:
		ImageSize = { 120,200 };
		ImageQuad.Quad::Quad(Pos, ImageSize.x, ImageSize.y, 0);
		Boss_gra = BossNyokki3_gra;
		break;
	case Charge:
		ImageSize = { 88,184 };
		ImageQuad.Quad::Quad(Pos, ImageSize.x, ImageSize.y, 0);
		Boss_gra = BossCharge_gra;
		break;
	case BulletAttack1:
		ImageSize = { 168,184 };
		ImageQuad.Quad::Quad(Pos, ImageSize.x, ImageSize.y, 0);
		Boss_gra = BossBulletAttack1_gra;
		break;
	case BulletAttack2:
		ImageSize = { 84,148};
		ImageQuad.Quad::Quad(Pos, ImageSize.x, ImageSize.y, 0);
		Boss_gra = BossBulletAttack2_gra;
		break;
	}

	if (Bosspregra != AnimeSelect) {
		SrcX = PreSheets * ImageSize.x;
	}

	Bosspregra = AnimeSelect;
	
	Zanzou();
}

void Boss2::Draw(Screen& screen)
{
	float tmp = HP/1800.0f;
	//screen.DrawEllipse(Pos.x, Pos.y, 50,50,0, RED, kFillModeSolid);
	for (int i = 0; i < Max_Zan; i++)
	{
		screen.DrawQuad2Renban(zanzou[i].Pos, zanzou[i].SrcX, 0, zanzou[i].Size.x, zanzou[i].Size.y, zanzou[i].sheets,99, zanzou[i].AnimeFlame, zanzou[i].Gra, 0x00FFFF66,false);

	};
	screen.DrawQuad2Renban(ImageQuad, SrcX, 0, ImageSize.x, ImageSize.y, sheets, 8, AnimeFlame, Boss_gra, WHITE, false);
	//screen.DrawQuad2Renban(Quad_Pos, colSrcX, 0, 1, 1, 1,6, colanime, 0, 0xFFFFFF22,false);
	//screen.DrawQuad2Renban(Quad_Pos,)
	Novice::DrawBox(456, 20, 1020*tmp, 54, 0, HpColor, kFillModeSolid);
	Novice::DrawSprite(350, 0, Boss2HpBar_gra, 1, 1, 0, WHITE);
	//Novice::ScreenPrintf(500, 500, "HP::%d", HP);
}



void Boss2::State(PlayerMain& player)
{
	Vec2 Distance = Pos - player.Translation();
	if (Action == false) {
		if (Distance.Length() < 300) {
			pattarn = NEAR_1;
		}
		else
			if (Distance.Length() < 800) {
				pattarn = MIDDLE;
			}
			else {
				pattarn = FAR_1;
			}
		if (HP < ThreeQuarterHP) {
			hppattarn = THREEQUARTERS;
			
			if (HP < HalfHP) {
				hppattarn = HALF;
				

			}
		}
		else {
			hppattarn = NORMAL;
		}
	}
}

void Boss2::KeepUP(PlayerMain& player)
{
}

void Boss2::KeepUpWaitBack(PlayerMain& player)
{
	if (keep.Time != 0) {
		keep.theta += M_PI / 60;
		keep.YMove = sinf(keep.theta) * 1;
		Pos.y += keep.YMove;
	}
	if (keep.bMove == false) {
		keep.Time++;
	}
	if (keep.Time == 5&& keep.bMove == false) {
		keep.rand = Randam::RAND(0, 100);
		if (keep.rand <= 50 && Pos.x >= 1200) {
			keep.rand = Randam::RAND(25, 100);
		}else if(keep.rand >= 50 && Pos.x <= 1200) {
			keep.rand = Randam::RAND(0, 75);
		}
		if (Pos.x >= 2000) {
			keep.rand = 70;
		}
		if (Pos.x <= 400) {
			keep.rand = 20;
		}
		keep.FPos = Pos.x;
		DirectionGet(player);
		keep.Ease_T = 0;
		keep.Time = 0;
		keep.bMove = true;
	}
	if (keep.bMove == true) {
		if (0 <= keep.rand && keep.rand <= 40) {
			/*Vec2 vel = (player.Translation() - Pos).Normalized();
			Pos.x += vel.x * 10;*/
			Pos.x = Easing::easing(keep.Ease_T, keep.FPos, keep.FPos + 700, 0.01, Easing::easeInBack);
			if (keep.Ease_T == 1) {
				keep.bMove = false;
			}
		}
		if (41 <= keep.rand && keep.rand <= 80) {
			/*Vec2 vel = (player.Translation() - Pos).Normalized();
			Pos.x -= vel.x * 10;*/
			Pos.x = Easing::easing(keep.Ease_T, keep.FPos, keep.FPos - 700, 0.01, Easing::easeInBack);
			if (keep.Ease_T == 1) {
				keep.bMove = false;
			}
		}
		if (81 <= keep.rand && keep.rand <= 100) {
			
				keep.bMove = false;
			
		}
	}
}

void Boss2::DirectionGet(PlayerMain& player)
{
	//ƒvƒŒƒCƒ„[‚ÌˆÊ’u‚É‚æ‚Á‚Äƒ}ƒCƒiƒX‚©ƒvƒ‰ƒX‚©‚í‚©‚éŠÖ‰H”‚¤‚·‚¤‚·i‘ƒ
	if (player.Translation().x <= Pos.x) {
		Direction = -1;
	}
	else Direction = 1;
}

void Boss2::PosLink(float posx)
{
	Pos.x = posx;
}
