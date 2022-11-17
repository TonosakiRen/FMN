#include "main.h"
#include "Randam.h"

const char kWindowTitle[] = "FMN";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, SCREEN_WIDTH, SCREEN_HEIGHT);

	//あしをひっぱるな！！！しがみつき！！！

	Controller::SetLeftStickDeadZone(0, 14000);


	int tex = Novice::LoadTexture("white1x1.png");
	int quadRedEffectImg = Novice::LoadTexture("./Resources/Images/Effect01.png");
	int circleRedEffectImg = Novice::LoadTexture("./Resources/Images/Effect02.png");
	int circleEffectImg = Novice::LoadTexture("./Resources/Images/Effect03.png");
	int quadBlueEffectImg = Novice::LoadTexture("./Resources/Images/Effect04.png");
	int CircleBlueEffectImg = Novice::LoadTexture("./Resources/Images/Effect05.png");
	int mainaBladeImg = Novice::LoadTexture("./Resources/Images/mainblade.png");
	int upMainaBladeImg = Novice::LoadTexture("./Resources/Images/upmainblade.png");
	int downMainaBladeImg = Novice::LoadTexture("./Resources/Images/downmainblade.png");
	int upSubBladeImg = Novice::LoadTexture("./Resources/Images/upsubblade01.png");
	int downSubBladeImg = Novice::LoadTexture("./Resources/Images/downsubblade01.png");
	int subBladeImg[7];
	subBladeImg[0] = Novice::LoadTexture("./Resources/Images/sabblade01.png");
	subBladeImg[1] = Novice::LoadTexture("./Resources/Images/sabblade02.png");
	subBladeImg[2] = Novice::LoadTexture("./Resources/Images/sabblade03.png");
	subBladeImg[3] = Novice::LoadTexture("./Resources/Images/sabblade04.png");
	subBladeImg[4] = Novice::LoadTexture("./Resources/Images/sabblade05.png");
	subBladeImg[5] = Novice::LoadTexture("./Resources/Images/sabblade06.png");
	subBladeImg[6] = Novice::LoadTexture("./Resources/Images/sabblade07.png");

	int bossImg = Novice::LoadTexture("./Resources/Images/Boss/Boss.png");
	int bossheadImg = Novice::LoadTexture("./Resources/Images/Boss/Head.png");
	int bossbodyImg = Novice::LoadTexture("./Resources/Images/Boss/Body.png");
	int bosslegImg = Novice::LoadTexture("./Resources/Images/Boss/Leg.png");
	int bossrightarmImg = Novice::LoadTexture("./Resources/Images/Boss/RightArm.png");
	int bossleftarmImg = Novice::LoadTexture("./Resources/Images/Boss/LeftArm.png");
	int ziki = Novice::LoadTexture("./Resources/Images/ziki.png");
	int background = Novice::LoadTexture("./Resources/Images/background.png");
	Randam::SRAND();

	//test

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		Key::Input();
		Controller::SetState();

		///
		/// ↓更新処理ここから
		///
		screen.Scroll_update(playermain.GetPlayerQuad().LeftTop.x, 1.25);

		switch (scene)
		{
		case title:
			//タイトル処理

			if (Key::IsTrigger(DIK_R) && isFeedout == false && isFeedin == false) {
				isFeedout = true;
			}
			break;
		case stage:
			//ステージ処理

			if (stopper.Pause() == false) {
				if (stopper.HitStopUpdate() == false) {
					playermain.Move();
					if (boss.IsLife==false&&boss2.IsLife==false) {
						//第二形態のセットここで
						boss2.Set();
					}
					//bossのアップデート
					if(boss.IsLife==true) {
						boss.UpDate();
						boss.RandamMoveSelect(Randam::RAND(0, MAX_PATTERN - 1), playermain, screen);
						//当たり判定とかいれて！！！
						playermain.PlayerHit(boss.GetBossAttackQuad());
						for (int i = 0; i < 5; i++) {
							playermain.PlayerHit(boss.GetBossQuad(i));
							playermain.SwordHit(boss.GetBossQuad(i));
						}
						playermain.PlayerHit(boss.GetShockWave());
						playermain.PlayerHit(boss.GetShockWave2());
						for (int i = 0; i < kMAX_RAINSWORD; i++) {
							playermain.PlayerHit(boss.GetRainOfSwordQuad(i));
						}
						for (int i = 0; i < kMAX_CIR; i++) {
							playermain.PlayerHit(boss.GetCircleOfDeathQuad(i));
						}
						//boss自体の当たり判定
						boss.BossHit(playermain.GetHitSword());
						boss.BossHitReaction(playermain.GetSwordQuad(), playermain.GetisFaceUp(), playermain.GetisFaceDown(), playermain.GetisFaceRigh());
						
					}
					//boss2のアップデート
					if (boss2.IsLife == true) {
						boss2.UpDate();
						boss2.RandamMoveSelect(Randam::RAND(0, MAX2_PATTERN - 1), playermain, screen);
						//当たり判定とかいれて！！！
						for (int i = 0; i < 20; i++) {
							playermain.PlayerHit({ boss2.centerOfDarknessUnder.particles[i].quad.GetCenter(),boss2.centerOfDarknessUnder.particles[i].quad.GetWidth() / 2 });
							playermain.PlayerHit({ boss2.centerOfDarknessLeft.particles[i].quad.GetCenter(),boss2.centerOfDarknessLeft.particles[i].quad.GetWidth() / 2 });
							playermain.PlayerHit({ boss2.centerOfDarknessRight.particles[i].quad.GetCenter(),boss2.centerOfDarknessRight.particles[i].quad.GetWidth() / 2 });
						}

					}


					//playerのeffect
					playerEffect.Update(true, playermain.GetPlayerQuad());
					//swordのeffect
					if (playermain.GetHitSword() == true) {
						if (playermain.GetisFaceUp()) {
							playerEffectSword.minDirection = { -0.4f , 0.1f };
							playerEffectSword.maxDirection = { 0.4f , 0.9f };
						}
						else if (playermain.GetisFaceDown()) {
							playerEffectSword.minDirection = { -0.4f , -0.1f };
							playerEffectSword.maxDirection = { 0.4f , -0.9f };
						}
						else if (playermain.GetisFaceRigh()) {
							playerEffectSword.minDirection = { 0.1f,-0.4f };
							playerEffectSword.maxDirection = { 0.9f,0.4f };
						}
						else {
							playerEffectSword.minDirection = { -0.9f,-0.4f };
							playerEffectSword.maxDirection = { -0.1f,0.4f };
						}

					}
					playerEffectSword.Update(playermain.GetHitSword(), playermain.GetHitAttackPos());

					//bossのエフェクト
					enemySwordEffect.Update(boss.GetSwordAttack(), boss.GetBossBladeQuad());
					bossBodyEffect.Update(boss.IsLife, boss.GetBossQuad(boss.body));
					bossHeadEffect.Update(boss.IsLife, boss.GetBossQuad(boss.head));
					bossRightArmEffect.Update(boss.IsLife, boss.GetBossQuad(boss.rightarm));
					bossLeftArmEffect.Update(boss.IsLife, boss.GetBossQuad(boss.leftarm));
					bossLegEffect.Update(boss.IsLife, boss.GetBossQuad(boss.leg));
					
					//boss2のエフェクト
					boss2.centerOfDarknessUnder.target = Quad{ { SCREEN_WIDTH / 2 - 10,(SCREEN_HEIGHT - Floor) / 2 + 10 },10,10 }.GetCenter();
					boss2.centerOfDarknessLeft.target = Quad{ { SCREEN_WIDTH / 2 - 10,(SCREEN_HEIGHT - Floor) / 2 + 10 },10,10 }.GetCenter();
					boss2.centerOfDarknessRight.target = Quad{ { SCREEN_WIDTH / 2 - 10,(SCREEN_HEIGHT - Floor) / 2 + 10 },10,10 }.GetCenter();

					boss2.centerOfDarknessUnder.deleteQuad = { { SCREEN_WIDTH / 2 - 10,(SCREEN_HEIGHT - Floor) / 2 + 10 },10,10 };
					boss2.centerOfDarknessLeft.deleteQuad = { { SCREEN_WIDTH / 2 - 10,(SCREEN_HEIGHT - Floor) / 2 + 10 },10,10 };
					boss2.centerOfDarknessRight.deleteQuad = { { SCREEN_WIDTH / 2 - 10,(SCREEN_HEIGHT - Floor) / 2 + 10 },10,10 };

					boss2.centerOfDarknessUnder.Update( boss2.isCenterOfDarkness, { {0,-Floor},int(SCREEN_WIDTH * 1.25),30 });
					boss2.centerOfDarknessLeft.Update( boss2.isCenterOfDarkness, { {-30,SCREEN_HEIGHT - Floor},30,SCREEN_HEIGHT + Floor });
					boss2.centerOfDarknessRight.Update( boss2.isCenterOfDarkness, { {SCREEN_WIDTH * 1.25,SCREEN_HEIGHT - Floor},30,SCREEN_HEIGHT + Floor });
					
					//stageのeffect
					stageEffect.Update(true, { {0,-Floor},int (SCREEN_WIDTH * 1.5),Floor });
				
				}
			}
			

			 //stopper.HitStopMake(playermain.HitStopOver());

			if (Key::IsTrigger(DIK_O) && isFeedout == false && isFeedin == false) {
				isFeedout = true;
				isGameover = true;
			}
			if (Key::IsTrigger(DIK_C) && isFeedout == false && isFeedin == false) {
				isFeedout = true;
				isGameclear = true;
			}
			
			break;
		case stage2:



			break;
		case gameover:
			//ゲームオーバー処理
			isGameover = false;
			if (Key::IsTrigger(DIK_R) && isFeedout == false && isFeedin == false) {
				isFeedout = true;
			}
			break;
		case gameclear:
			//ゲームクリア処理
			isGameclear = false;
			if (Key::IsTrigger(DIK_R) && isFeedout == false && isFeedin == false) {
				isFeedout = true;
			}
			break;
		default:
			break;
		}
		
		

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		switch (scene)
		{
		case title:
			if (isTitleStart == false) {
				isFeedin = true;
				if (feedinT >= 1) {
					InitFeedin();
					isTitleStart = true;
				}
			}
		//title描画処理
			Novice::ScreenPrintf(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, "Press R");

			
			if (feedoutT >= 1) {
				InitFeedout();
				isTitleStart = false;
				scene = stage;
				isFeedin = true;
			}
			else {
				break;
			}
		case stage:
			if (isStageStart == false) {
				isFeedin = true;
				if (feedinT >= 1) {
					InitFeedin();
					isStageStart = true;
				}
			}
			//ステージ描画処理
			//背景
			Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, BLACK, kFillModeSolid);
			Novice::SetBlendMode(kBlendModeAdd);
			screen.DrawQuad2Normal(0 - screen.Scroll.x, 0, SCREEN_WIDTH * 1.25, SCREEN_HEIGHT, 0, 0, SCREEN_WIDTH * 1.25, SCREEN_HEIGHT, background, WHITE);
			Novice::SetBlendMode(kBlendModeNormal);

			//エフェクト描画
			playerEffect.Draw(screen, 128, quadBlueEffectImg, WHITE, kBlendModeAdd);
			enemySwordEffect.Draw(screen, 128, quadRedEffectImg, WHITE, kBlendModeAdd);
			stageEffect.Draw(screen, 128, circleEffectImg, RED, kBlendModeAdd);
			bossBodyEffect.Draw(screen, 128, circleEffectImg, RED, kBlendModeAdd);
			bossBodyEffect.Draw(screen, 128, circleEffectImg, BLACK, kBlendModeNormal);
			bossHeadEffect.Draw(screen, 128, circleEffectImg, RED, kBlendModeAdd);
			bossHeadEffect.Draw(screen, 128, circleEffectImg, BLACK, kBlendModeNormal);
			bossRightArmEffect.Draw(screen, 128, circleEffectImg, RED, kBlendModeAdd);
			bossRightArmEffect.Draw(screen, 128, circleEffectImg, BLACK, kBlendModeNormal);
			bossLeftArmEffect.Draw(screen, 128, circleEffectImg, RED, kBlendModeAdd);
			bossLeftArmEffect.Draw(screen, 128, circleEffectImg, BLACK, kBlendModeNormal);
			bossLegEffect.Draw(screen, 128, circleEffectImg, RED, kBlendModeAdd);
			bossLegEffect.Draw(screen, 128, circleEffectImg, BLACK, kBlendModeNormal);
			boss2.centerOfDarknessRight.Draw(screen, 128, circleEffectImg, RED, kBlendModeAdd);
			boss2.centerOfDarknessRight.Draw(screen, 128, circleEffectImg, BLACK, kBlendModeNormal);
			boss2.centerOfDarknessLeft.Draw(screen, 128, circleEffectImg, RED, kBlendModeAdd);
			boss2.centerOfDarknessLeft.Draw(screen, 128, circleEffectImg, BLACK, kBlendModeNormal);
			boss2.centerOfDarknessUnder.Draw(screen, 128, circleEffectImg, RED, kBlendModeNormal);
			boss2.centerOfDarknessUnder.Draw(screen, 128, circleEffectImg, BLACK, kBlendModeNormal);

			//プレイヤー描画
			playermain.Draw(screen, ziki);
			
			//ボス描画
			if (boss.IsLife == true) {

				boss.Draw(screen, bossImg, bossheadImg, bossbodyImg, bosslegImg, bossleftarmImg, bossrightarmImg);
			}
			if (boss2.IsLife == true) {
				boss2.Draw(screen);
			}

			//プレイヤーソード描画
			playermain.BladeDraw(screen, mainaBladeImg, upMainaBladeImg, downMainaBladeImg, upSubBladeImg, downSubBladeImg, subBladeImg, 0x20a8b4FF, kBlendModeAdd);
			playerEffectSword.Draw(screen, 128, circleEffectImg, 0x20a8b4FF, kBlendModeAdd);




			if (feedoutT >= 1 ) {
				InitFeedout();
				isStageStart = false;
				if (isGameover == true) {
					scene = gameover;
					isFeedin = true;
				}
				if (isGameclear == true) {
					scene = gameclear;
					isFeedin = true;
				}
			}
			else {
				break;
			}
			
		case gameover:
			if (isGameoverStart == false) {
				isFeedin = true;
				if (feedinT >= 1) {
					InitFeedin();
					isGameoverStart = true;
				}
			}
			//ゲームオーバー描画処理
			Novice::ScreenPrintf(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, "Press R");


			if (feedoutT >= 1) {
				InitFeedout();
				Init();
				isGameoverStart = false;
				scene = stage;
				isFeedin = true;
			}
			else {
				break;
			}

		case gameclear:
			if (isGameclearStart == false) {
				isFeedin = true;
				if (feedinT >= 1) {
					InitFeedin();
					isGameclearStart = true;
				}
			}
			//ゲームクリア描画

			if (feedoutT >= 1) {
				InitFeedout();
				Init();
				isGameclearStart = false;
				scene = stage;
				isFeedin = true;
			}
			else {
				break;
			}
		default:
			break;
		}
		if (isFeedin) {
			Feed::Feedin(feedinT, 0.05f, SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		if (isFeedout) {
			Feed::Feedout(feedoutT, 0.05f, SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (Key::IsTrigger(DIK_ESCAPE)) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
