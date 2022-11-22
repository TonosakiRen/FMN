#include "Boss2.h"
#include "Clamp.h"
#include "Key.h"
#include "Easing.h"
#include "Randam.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Feed.h"

Boss2::Boss2() :
	centerOfDarknessLeft(30, 30, { 0,0 }, { {0,0},0,0 }, 30, 40, 6.0f, 6.0f, 0.0f, 0.0f, 1),
	centerOfDarknessRight(30, 30, { 0,0 }, { {0,0},0,0 }, 30, 40, 6.0f, 6.0f, 0.0f, 0.0f, 1),
	centerOfDarknessUnder(30, 30, { 0,0 }, { {0,0},0,0 }, 30, 40, 6.0f, 6.0f, 0.0f, 0.0f, 3),
	swordEffect(500, 0, { 0.0f,0.0f }, { 0.0f,0.0f }, 30, 30, 0.0f, 0.0f, 0.0f, 0.1f, 1),
	chaseEffect(chaseBulletNum, 100, { 0.0f,0.0f }, { 0.0f,0.0f }, 30, 30, 10.0f, 10.0f, 0.0f, 0.0f, 1),
	TelechaseEffect(1, 0, { 0.0f,0.0f }, { 0.0f,0.0f }, 50, 50, 10.0f, 10.0f, 0.0f, 0.0f, 1)
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

	HP = 1200;
	HpColor = 0x00FF44FF;//HPBar‚ÌF‰Šú‰»iƒOƒŠ[ƒ“j


	keep.rand = 0;
	keep.Time = 0;
	keep.bMove = 0;
	keep.Ease_T = 0;
	keep.FPos = 0;
	keep.theta = 0;
	keep.YMove = 0;
	IsLife = false;
	Zanflame = 0;

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
	}

	chaseEffect.feedSpeed = 0.0f;
	xMove = 0.0f;
	yMove = 0;
	ytheta = 0.0f;
	rotateT = 0.0f;
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
	
}

void Boss2::RandamMoveSelect(int rand, PlayerMain& player, Screen& screen)
{
	Novice::ScreenPrintf(1000, 0, "Cooltime::%d", CoolTime);
	Novice::ScreenPrintf(1000, 20, "Action_Boss::%d", Action);
	Novice::ScreenPrintf(1000, 40, "Movearray::%d", MoveArray);
	Novice::ScreenPrintf(1000, 60, "MovePattarn::%d", MovePattern[MoveArray]);
	Novice::ScreenPrintf(1000, 80, "boss:state:%d", pattarn);
	Novice::ScreenPrintf(1000, 200, "boss:hpstate:%d", hppattarn);
	Novice::ScreenPrintf(1000, 220, "boss:keep_bmove:%d", keep.bMove);

	Novice::ScreenPrintf(Pos.x, Pos.y - 200 + SCREEN_HEIGHT, "HP:%d", HP);

	if (CoolTime <= 0 && Action == false) {
		if (keep.bMove == false) {
			MoveArray = rand;

			if (MovePattern[MoveArray] == FMoveArray) {
				Novice::ScreenPrintf(1000, 100, "Reload:%d", reload);

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
					Teleportation(player);
					FMoveArray = array.NormalAttack; 
					
				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%‚ÌUŒ‚
					UndertaleAttack(player);
					FMoveArray = array.AttackFunction01;
					

				}
				if (MovePattern[MoveArray] == array.AttackFunction02) {
					//5%‚ÌUŒ‚
					UndertaleAttack(player);
					FMoveArray = array.AttackFunction02;
					
					
				}
				if (MovePattern[MoveArray] == array.AttackFunction03) {
					//5%‚ÌUŒ‚
					Teleportation(player);
					FMoveArray = array.AttackFunction03;


				}
				if (MovePattern[MoveArray] == array.AttackFunction04) {
					//5%‚ÌUŒ‚
					Teleportation(player);
					FMoveArray = array.AttackFunction04;
				
					

				}
				if (MovePattern[MoveArray] == array.AttackFunction05) {
					//5%‚ÌUŒ‚
					Teleportation(player);
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
					Teleportation(player);
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
					UndertaleAttack(player);
					FMoveArray = array.AttackFunction02;
					//Action = false;
					

				}
				if (MovePattern[MoveArray] == array.AttackFunction03) {
					//5%‚ÌUŒ‚
					UndertaleAttack(player);
					
					FMoveArray = array.AttackFunction03;
				}
				if (MovePattern[MoveArray] == array.AttackFunction04) {
					//5%‚ÌUŒ‚
					AsgoreAttack(player);
					
					FMoveArray = array.AttackFunction04;
				}
				if (MovePattern[MoveArray] == array.AttackFunction05) {
					//5%‚ÌUŒ‚
					AsgoreAttack(player);
					
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
					
					BulletAttack(player);
					FMoveArray = array.NormalAttack;

				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%‚ÌUŒ‚
					BulletAttack(player);
					
					FMoveArray = array.AttackFunction01;
				}
				if (MovePattern[MoveArray] == array.AttackFunction02) {
					//5%‚ÌUŒ‚
					BulletAttack(player);
					
					FMoveArray = array.AttackFunction02;
				}
				if (MovePattern[MoveArray] == array.AttackFunction03) {
					//5%‚ÌUŒ‚
					BulletAttack(player);
					FMoveArray = array.AttackFunction03;
					
				}
				if (MovePattern[MoveArray] == array.AttackFunction04) {
					//5%‚ÌUŒ‚
					BulletAttack(player);
					FMoveArray = array.AttackFunction04;
					
					//CoolTime = 0;
				}
				if (MovePattern[MoveArray] == array.AttackFunction05) {
					//5%‚ÌUŒ‚
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
			}
			break;

		case THREEQUARTERS:
			CoolTime = 50;

			switch (pattarn) {
			case NEAR_1:
			{
				if (MovePattern[MoveArray] == array.NormalAttack) {
					//’ÊíUŒ‚‚ÌƒR[ƒh‚Í‚±‚±
					Action = false;

					FMoveArray = array.NormalAttack;
				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%‚ÌUŒ‚
					Action = false;
					FMoveArray = array.AttackFunction01;

				}
				if (MovePattern[MoveArray] == array.AttackFunction02) {
					//5%‚ÌUŒ‚

					FMoveArray = array.AttackFunction02;
					Action = false;
				}
				if (MovePattern[MoveArray] == array.AttackFunction03) {
					//5%‚ÌUŒ‚
					Action = false;
					FMoveArray = array.AttackFunction03;


				}
				if (MovePattern[MoveArray] == array.AttackFunction04) {
					//5%‚ÌUŒ‚
					
					FMoveArray = array.AttackFunction04;

					//CoolTime = 0;
					Action = false;

				}
				if (MovePattern[MoveArray] == array.AttackFunction05) {
					//5%‚ÌUŒ‚
				
					FMoveArray = array.AttackFunction05;

					Action = false;
					//CoolTime = 0;

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
					Action = false;
					FMoveArray = array.NormalAttack;
				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%‚ÌUŒ‚
					Action = false;
					FMoveArray = array.AttackFunction01;

				}
				if (MovePattern[MoveArray] == array.AttackFunction02) {
					//5%‚ÌUŒ‚
					Action = false;
					FMoveArray = array.AttackFunction02;
					

				}
				if (MovePattern[MoveArray] == array.AttackFunction03) {
					//5%‚ÌUŒ‚
					Action = false;
					
					FMoveArray = array.AttackFunction03;
				}
				if (MovePattern[MoveArray] == array.AttackFunction04) {
					//5%‚ÌUŒ‚
					
					Action = false;
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
					Action = false;
					FMoveArray = array.NormalAttack;

				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%‚ÌUŒ‚
					Action = false;
					FMoveArray = array.AttackFunction01;
				}
				if (MovePattern[MoveArray] == array.AttackFunction02) {
					//5%‚ÌUŒ‚
					Action = false;
					/*Action = false;*/
					FMoveArray = array.AttackFunction02;
					//CoolTime = 20;
				}
				if (MovePattern[MoveArray] == array.AttackFunction03) {
					//5%‚ÌUŒ‚
					Action = false;
					FMoveArray = array.AttackFunction03;
				}
				if (MovePattern[MoveArray] == array.AttackFunction04) {
					//5%‚ÌUŒ‚
					Action = false;
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
			}
			break;

		case HALF:
			CoolTime = 5;
			switch (pattarn) {
			case NEAR_1:
			{
				if (MovePattern[MoveArray] == array.NormalAttack) {
					//’ÊíUŒ‚‚ÌƒR[ƒh‚Í‚±‚±
					Action = false;
					FMoveArray = array.NormalAttack;
				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%‚ÌUŒ‚
					Action = false;
					FMoveArray = array.AttackFunction01;
					
				}
				if (MovePattern[MoveArray] == array.AttackFunction02) {
					//5%‚ÌUŒ‚
					Action = false;
					FMoveArray = array.AttackFunction02;
					/*Action = false;*/

				}
				if (MovePattern[MoveArray] == array.AttackFunction03) {
					//5%‚ÌUŒ‚
					Action = false;
					FMoveArray = array.AttackFunction03;
				}
				if (MovePattern[MoveArray] == array.AttackFunction04) {
					//5%‚ÌUŒ‚
					
					Action = false;
					FMoveArray = array.AttackFunction04;
					//CoolTime = 20;
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
			case MIDDLE:
			{
				if (MovePattern[MoveArray] == array.NormalAttack) {
					//’ÊíUŒ‚‚ÌƒR[ƒh‚Í‚±‚±
					Action = false;
					FMoveArray = array.NormalAttack;
				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%‚ÌUŒ‚
					Action = false;
					FMoveArray = array.AttackFunction01;
				}
				if (MovePattern[MoveArray] == array.AttackFunction02) {
					//5%‚ÌUŒ‚
					Action = false;
					FMoveArray = array.AttackFunction02;
				}
				if (MovePattern[MoveArray] == array.AttackFunction03) {
					//5%‚ÌUŒ‚
					Action = false;
					FMoveArray = array.AttackFunction03;
				}
				if (MovePattern[MoveArray] == array.AttackFunction04) {
					//5%‚ÌUŒ‚
					Action = false;
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
					Action = false;
					FMoveArray = array.NormalAttack;

				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%‚ÌUŒ‚
					Action = false;
					FMoveArray = array.AttackFunction01;
					
				}
				if (MovePattern[MoveArray] == array.AttackFunction02) {
					//5%‚ÌUŒ‚
					Action = false;
					FMoveArray = array.AttackFunction02;
					
				}
				if (MovePattern[MoveArray] == array.AttackFunction03) {
					//5%‚ÌUŒ‚
					
					FMoveArray = array.AttackFunction03;
					Action = false;

				}
				if (MovePattern[MoveArray] == array.AttackFunction04) {
					//5%‚ÌUŒ‚
					Action = false;
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

void Boss2::Zanzou()
{
	Zanflame++;
	if (Zanflame > 100) Zanflame = 1;
	for (int i = 0; i < Max_Zan; i++) {
		if (Zanflame % 2 == 0&&zanzou[i].bSet==false) {

			zanzou[i].Pos = Quad_Pos;
			zanzou[i].LifeTime = 3;
			zanzou[i].bSet = true;
			break;

		}
		if (zanzou[i].bSet == true) {
			zanzou[i].LifeTime --;
			if (zanzou[i].LifeTime == 0) {
				zanzou[i].bSet = false;
			}
		}
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
		--centerOfDarknessCooltime;
		Vec2 playertoboss = (Pos - player.GetPlayerQuad().GetCenter()).Normalized() * gravityPower;
		player.SetPlayerPos({ player.GetPlayerPos().x + playertoboss.x, player.GetPlayerPos().y });

		if (centerOfDarknessCooltime >= 200) {
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
				centerNyokkiKeepAnimationFrame++;
			}
			
			isCenterOfDarkness = true;
		}
		else if (centerOfDarknessCooltime >= 0) {
			isFeedCenterNyokki = true;
			iscenterNyokkiCollision = false;
			isCenterOfDarkness = false;
			if (centerNyokkiT[0] >= 1.0f) {
				iscenterNyokki = false;
			}
		}
		else {
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
		}
	}
	
}


void Boss2::BulletAttack(PlayerMain& player) {

	keep.theta += M_PI / 60;
	keep.YMove = sinf(keep.theta) * 1;
	Pos.y += keep.YMove;
	bulletAttackCoolTime--;
	isBulletAttack = true;
	for (int i = 0; i < swordNum; i++) {
		//theta‚ğ‰ÁZ
		if (theta[swordNum - 1] <= 0) {
			theta[i] += M_PI / 80.0f;
			initialSword = { Pos,30,30, };
		}
		//theta‚ª0ˆÈã‚É‚È‚Á‚½‚çoŒ»‚³‚¹‚é
		if (theta[i] >= 0 && isSword[i] == false) {
			isSword[i] = true;
		}
		if (theta[swordNum - 1] <= 0) {
			if (isSword[i] == true) {
				//‰ñ“]
				sword[i] = initialSword.Rotate(initialSword, radius, theta[i]);
			}

		}
		else {
			isRelease = true;
		}
	}
	for (int i = 0; i < swordNum; i++) {
		if(isRelease == true) {//ÅŠú‚Ì’e‚Ìtheta‚ª0ˆÈã‚É‚È‚Á‚½‚ç
			
				
				radius += 1;
				bulletAttackCoolTime--;
				sword[i] = initialSword.Rotate(initialSword, radius, theta[i]);
				if (swordT[i] < 1.0f && isOrbit[i] == false) {
					orbitColor[i] = Feed::Feedin(swordT[i], 0.05f, orbitColor[i]);
				}
				if (swordT[i] >= 1.0f && isOrbit[i] == false) {
					isOrbit[i] = true;
					swordT[i] = 0.0f;
				}
				if (isOrbit[i] == true) {
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
		}
		Action = false;
	}
}

void Boss2::UndertaleAttack(PlayerMain& player) {
	keep.theta += M_PI / 60;
	keep.YMove = sinf(keep.theta) * 1;
	Pos.y += keep.YMove;
	isUndertaleAttack = true;
	undertaleFrame--;
	if (undertaleFrame <= 120 && undertaleFrame > 0.0f) {
		chaseEffect.feedSpeed = 0.01;
		isUndertaleCollision = true;
		isFeedrotateBullet = true;
		emitchaseEffect = false;
	}

	if (rotatetheta[0] >= 0 && isRotateBullet[0] == false) {
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
	for (int i = 0; i < rotateBulletNum; i++) {
		rotatetheta[i] += rotatethetaSpeed;
		if (rotatetheta[i] >= 0 && isRotateBullet[i] == false) {
				isRotateBullet[i] = true;
		}

		if (isRotateBullet[i] == true) {
			//‰ñ“]
			rotateBullet[i] = initialRotateBullet.Rotate(initialRotateBullet, bulletRadius, rotatetheta[i]);
		}
		if (rotateBulletT[i] >= 1.0f) {
			isRotateBullet[i] = false;
		}
	}
	if (undertaleFrame <= 940) {
		chaseEffect.Update(emitchaseEffect, { Pos,30,30 });
		for (int i = 0; i < chaseBulletNum; i++) {
			chaseframe[i]--;
			if (isGet[i] == false && chaseEffect.particles[i].isActive == true) {
				chaseframe[i]--;
				if (isGet[i] == false && chaseEffect.particles[i].isActive == true) {
					chaseVec[i] = player.GetPlayerPos() - chaseEffect.particles[i].quad.GetCenter();
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
			xMove = 0.0f;
			yMove = 0;
			ytheta = 0.0f;
			rotateT = 0.0f;
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
				rotateBulletT[i] = 0.0f;
			}
			isUndertaleAttack =false;
			Action = false;
		}
	
}

void Boss2::nyokkiAttack(PlayerMain& player) {
	if (isdropMove == false) {
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
		Pos.y  = Easing::easing(dropT, saveBossY2, underPos, dropSpeed, Easing::easeInOutQuint);
		if (dropT >= 1.0f) {
			isdrop = false;
			isNyokki = true;
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
			allSpeed = { 2.0f,-1.0f };
		}
		else {
			EmitPos = { 2400.0f - 240,SCREEN_HEIGHT - Floor };
			distanceSpeed = -6.0f;
			allSpeed = { -2.0f,-1.0f };
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
			Pos.x = Easing::easing(AsgoreReturnTx, savePosreturn.x, 1200.0f, 0.01f, Easing::easeInOutQuint);
			Pos.y = Easing::easing(AsgoreReturnTy, savePosreturn.y, savePosAsgore.y, 0.01f, Easing::easeInOutQuint);
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
			moveAttackSpeed = 4.0f;
			iswhichlr = false;
		}
		else {
			LastPosx = 300.0f;
			startPosx = 2100.0f;
			moveAttackSpeed = -4.0f;
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
					movemovetheta[i] += movemovethetaSpeed;
					movemoveBullet[i] = initialmovemoveBullet.Rotate(initialmovemoveBullet, movemovetheta[i]) + moveBullet[0].GetCenter();
				}
			}
			else if (i < 8) {
				if (ismoveBullet[1] == true) {
					movemovetheta[i] += movemovethetaSpeed;
					movemoveBullet[i] = initialmovemoveBullet.Rotate(initialmovemoveBullet, movemovetheta[i]) + moveBullet[1].GetCenter();
				}
			}
			else if (i < 12) {
				if (ismoveBullet[2] == true) {
					movemovetheta[i] += movemovethetaSpeed;
					movemoveBullet[i] = initialmovemoveBullet.Rotate(initialmovemoveBullet, movemovetheta[i]) + moveBullet[2].GetCenter();
				}
			}
			else if (i < 16) {
				if (ismoveBullet[3] == true) {
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
	}

}

void Boss2::Teleportation(PlayerMain& player) {
	keep.theta += M_PI / 60;
	keep.YMove = sinf(keep.theta) * 1;
	Pos.y += keep.YMove;
	if (GetTeleportPos == false) {
		int num = Randam::RAND(0, 4);
		if (num == 0) {
			TeleportPos = { player.GetPlayerPos().x - 600.0f,Pos.y };
		}
		if (num == 1) {
			TeleportPos = { player.GetPlayerPos().x - 300.0f,Pos.y };
		}
		if (num == 2) {
			TeleportPos = { player.GetPlayerPos().x - 0.0f,Pos.y };
		}
		if (num == 3) {
			TeleportPos = { player.GetPlayerPos().x + 300.0f,Pos.y };
		}
		if (num == 4) {
			TeleportPos = { player.GetPlayerPos().x + 600.0f,Pos.y };
		}
		TeleSavePos = Pos;
		GetTeleportPos = true;
	}
	if (isTeleport == false) {
		Pos.x = Easing::easing(TeleportTx, TeleSavePos.x, TeleportPos.x, 0.1f, Easing::easeInOutQuint);
		
		if (TeleportTx >= 1.0f) {
			isTeleport = true;
		}
	}
	if (isTeleport == true) {
		TelechaseEffect.Update(isTeleport, { Pos,30,30 });
		for (int i = 0; i < 1; i++) {
			Telechaseframe[0]--;
			
			if (TeleisGet[0] == false && TelechaseEffect.particles[0].isActive == true) {
				Telechaseframe[0]--;
				if (TeleisGet[0] == false && TelechaseEffect.particles[0].isActive == true) {
					TelechaseVec[0] = player.GetPlayerPos() - TelechaseEffect.particles[0].quad.GetCenter();
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
					Telechaseframe[0] = savechaseframe;
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
				Telechaseframe[0] = 0;
				TeleisGet[0] = false;
				TeleisFeedrotateBullet = false;
				TeleportNum--;
			}
		}
	}
	if (TeleportNum <= 0) {
		TeleportNum = 3;
		Action = false;
	}
	
}

void Boss2::UpDate()
{




	Pos.y = Clamp::clamp(Pos.y, Size.y / 2, 10000);
	Pos.x = Clamp::clamp(Pos.x, Size.x / 2+200, (1920 * 1.25) - Size.x / 2-200);
	Zanzou();
	Quad_Pos.Quad::Quad(Pos, Size.x, Size.y, 0);



	//UŒ‚‚ğ“–‚Ä‚ç‚ê‚½‚Ìˆ—
	if (isBossHit == true) {
		HP -= 25;
	};
}



void Boss2::Set()
{
	Size = { 120,192 };
	Pos = { 1000,500 };
	Quad_Pos.Quad::Quad(Pos, Size.x, Size.y, 0);
	IsLife = true;
}

void Boss2::Draw(Screen& screen)
{
	if (load == 0) {
		load = 1;
		Boss_gra = Novice::LoadTexture("./Resources/images/Boss2/Boss2.png");
	}
	//screen.DrawEllipse(Pos.x, Pos.y, 50,50,0, RED, kFillModeSolid);
	for (int i = 0; i < Max_Zan; i++)
	{
		screen.DrawQuad2(zanzou[i].Pos, 0, 0, 120, 192, Boss_gra, 0x00FFFF66);

	};
	screen.DrawQuad2(Quad_Pos, 0, 0, 120, 192, Boss_gra, WHITE);
	//screen.DrawQuad2Renban(Quad_Pos,)

	
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
			HpColor = 0xFFFF00FF;
			if (HP < HalfHP) {
				hppattarn = HALF;
				HpColor = 0xFF4400FF;

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
			Pos.x = Easing::easing(keep.Ease_T, keep.FPos, keep.FPos + 700, 0.02, Easing::easeInBack);
			if (keep.Ease_T == 1) {
				keep.bMove = false;
			}
		}
		if (41 <= keep.rand && keep.rand <= 80) {
			/*Vec2 vel = (player.Translation() - Pos).Normalized();
			Pos.x -= vel.x * 10;*/
			Pos.x = Easing::easing(keep.Ease_T, keep.FPos, keep.FPos - 700, 0.02, Easing::easeInBack);
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
