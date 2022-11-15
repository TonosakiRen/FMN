#include "Boss2.h"
#include "Clamp.h"
#include "Key.h"
#include "Easing.h"
#include "Randam.h"



void Boss2::RandamMoveSelect(int rand, PlayerMain& player, Screen& screen)
{
	Novice::ScreenPrintf(1000, 0, "Cooltime::%d", CoolTime);
	Novice::ScreenPrintf(1000, 20, "Action_Boss::%d", Action);
	Novice::ScreenPrintf(1000, 40, "Movearray::%d", MoveArray);
	Novice::ScreenPrintf(1000, 60, "MovePattarn::%d", MovePattern[MoveArray]);
	Novice::ScreenPrintf(1000, 80, "boss:state:%d", pattarn);
	Novice::ScreenPrintf(1000, 200, "boss:hpstate:%d", hppattarn);

	Novice::ScreenPrintf(Pos.x, Pos.y - 200 + SCREEN_HEIGHT, "HP:%d", HP);


	if (CoolTime == 0 && Action == false) {
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
		DirectionGet(player);
	}
	else if (CoolTime != 0 && Action == false) {
		CoolTime--;
		State(player);
		reload = Randam::RAND(0, 1);
		KeepUpWaitBack(player);
		RandMoveSet();
		DirectionGet(player);

	}

	

	if (Action == true) {

		switch (hppattarn)
		{

		case NORMAL:
			CoolTime = 50;

			switch (pattarn) {
			case NEAR_1:
			{
				if (MovePattern[MoveArray] == array.NormalAttack) {
					//’ÊíUŒ‚‚ÌƒR[ƒh‚Í‚±‚±
					
					FMoveArray = array.NormalAttack; 
					Action = false;
				}
				if (MovePattern[MoveArray] == array.AttackFunction01) {
					//5%‚ÌUŒ‚
					
					FMoveArray = array.AttackFunction01;
					Action = false;

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
				
					Action = false;

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



Boss2::Boss2()
{

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
	screen.DrawQuad2(Quad_Pos, 0, 0, 120, 192, Boss_gra, WHITE);
	//screen.DrawQuad2Renban(Quad_Pos,)
}

void Boss2::UpDate()
{

	Quad_Pos.Quad::Quad(Pos, Size.x, Size.y, 0);
	
	

	Pos.y = Clamp::clamp(Pos.y, Size.y / 2, 10000);
	Pos.x = Clamp::clamp(Pos.x, Size.x / 2, (1920 * 1.25) - Size.x / 2);


	//UŒ‚‚ğ“–‚Ä‚ç‚ê‚½‚Ìˆ—
	if (isBossHit == true) {
		HP -= 25;
	};
}

void Boss2::State(PlayerMain& player)
{
}

void Boss2::KeepUP(PlayerMain& player)
{
}

void Boss2::KeepUpWaitBack(PlayerMain& player)
{
}

void Boss2::DirectionGet(PlayerMain& player)
{
}
