#include "Boss2.h"
#include "Clamp.h"
#include "Key.h"
#include "Easing.h"
#include "Randam.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Feed.h"

Boss2::Boss2() :
	centerOfDarknessLeft(20, 20, { 0,0 }, { {0,0},0,0 }, 30, 40, 6.0f, 6.0f, 0.0f, 0.0f, 1),
	centerOfDarknessRight(20, 20, { 0,0 }, { {0,0},0,0 }, 30, 40, 6.0f, 6.0f, 0.0f, 0.0f, 1),
	centerOfDarknessUnder(150, 20, { 0,0 }, { {0,0},0,0 }, 30, 40, 6.0f, 6.0f, 0.0f, 0.0f, 2),
	swordEffect(500, 0, { 0.0f,0.0f }, { 0.0f,0.0f }, 30, 30, 0.0f, 0.0f, 0.0f, 0.1f, 1),
	chaseEffect(chaseBulletNum, 100, { 0.0f,0.0f }, { 0.0f,0.0f }, 30, 30, 10.0f, 10.0f, 0.0f, 0.0f, 1)
{
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
			case MIDDLE:
			{
				if (MovePattern[MoveArray] == array.NormalAttack) {
					//’ÊíUŒ‚‚ÌƒR[ƒh‚Í‚±‚±
					Undertale(player);
					FMoveArray = array.NormalAttack;
				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%‚ÌUŒ‚
					CenterOfDarknessAttack(player);
					//Action = false;
					FMoveArray = array.AttackFunction01;

				}
				if (MovePattern[MoveArray] == array.AttackFunction02) {
					//5%‚ÌUŒ‚
					CenterOfDarknessAttack(player);
					FMoveArray = array.AttackFunction02;
					//Action = false;
					

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
					
					FMoveArray = array.AttackFunction04;
					Action = false;
					//CoolTime = 0;
				}
				if (MovePattern[MoveArray] == array.AttackFunction05) {
					//5%‚ÌUŒ‚
					
					FMoveArray = array.AttackFunction05;
					Action = false;
					
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
			isCenterOfDarkness = true;
		}
		else if (centerOfDarknessCooltime >= 0) {
			isCenterOfDarkness = false;
		}
		else {
			Action = false;
			centerOfDarknessCooltime = saveCenterOfDarknessCooltime;
			centerOfDarknessMoveT = 0.0f;
			isCenteroOfDarknessMove = true;
			isGetPos = false;
		}
	}
	
}


void Boss2::BulletAttack(PlayerMain& player) {

	keep.theta += M_PI / 60;
	keep.YMove = sinf(keep.theta) * 1;
	Pos.y += keep.YMove;
	bulletAttackCoolTime--;
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
		}
		Action = false;
	}
}

void Boss2::Undertale(PlayerMain& player) {
	keep.theta += M_PI / 60;
	keep.YMove = sinf(keep.theta) * 1;
	Pos.y += keep.YMove;
	undertaleFrame--;
	if (undertaleFrame <= 120 && undertaleFrame > 0.0f) {
		chaseEffect.feedSpeed = 0.01;
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

			Action = false;
		}
	
}

void Boss2::UpDate()
{




	Pos.y = Clamp::clamp(Pos.y, Size.y / 2, 10000);
	Pos.x = Clamp::clamp(Pos.x, Size.x / 2, (1920 * 1.25) - Size.x / 2);
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
		if (0 <= keep.rand && keep.rand <= 50) {
			/*Vec2 vel = (player.Translation() - Pos).Normalized();
			Pos.x += vel.x * 10;*/
			Pos.x = Easing::easing(keep.Ease_T, keep.FPos, keep.FPos + 500, 0.01, Easing::easeInBack);
			if (keep.Ease_T == 1) {
				keep.bMove = false;
			}
		}
		if (51 <= keep.rand && keep.rand <= 100) {
			/*Vec2 vel = (player.Translation() - Pos).Normalized();
			Pos.x -= vel.x * 10;*/
			Pos.x = Easing::easing(keep.Ease_T, keep.FPos, keep.FPos - 500, 0.01, Easing::easeInBack);
			if (keep.Ease_T == 1) {
				keep.bMove = false;
			}
		}
		/*if (41 <= keep.rand && keep.rand <= 100) {
			keep.Ease_T += 0.01f;
			if (keep.Ease_T == 1) {
				keep.bMove = false;
			}
		}*/
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
