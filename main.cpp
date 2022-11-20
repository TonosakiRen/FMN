#include "main.h"
#include "Randam.h"

const char kWindowTitle[] = "FMN";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, SCREEN_WIDTH, SCREEN_HEIGHT);

	//頑張ったな！！！しがみつき！！！

	Controller::SetLeftStickDeadZone(0, 14000);

	clock_t offset;
	offset = clock();
	int FPS = 0;

	int tex = Novice::LoadTexture("white1x1.png");
	int quadRedEffectImg = Novice::LoadTexture("./Resources/Images/Effect01n.png");
	int circleRedEffectImg = Novice::LoadTexture("./Resources/Images/Effect02n.png");
	int circleEffectImg = Novice::LoadTexture("./Resources/Images/Effect03.png");
	int quadBlueEffectImg = Novice::LoadTexture("./Resources/Images/Effect04n.png");
	int CircleBlueEffectImg = Novice::LoadTexture("./Resources/Images/Effect05n.png");
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

	int deadbossbodyImg = Novice::LoadTexture("./Resources/Images/BossDead/Body.png");
	int deadbossrightarmImg = Novice::LoadTexture("./Resources/Images/BossDead/RightArm.png");
	int deadbossleftarmImg = Novice::LoadTexture("./Resources/Images/BossDead/LeftArm.png");

	int playerstand_gra = Novice::LoadTexture("./Resources/Images/Player/PlayerStand.png");
	int playerwalk_gra = Novice::LoadTexture("./Resources/Images/Player/PlayerWalk.png");
	int playerdash_gra = Novice::LoadTexture("./Resources/Images/Player/PlayerDash.png");
	int playerjump_gra = Novice::LoadTexture("./Resources/Images/Player/PlayerJump.png");
	int playerfall_gra = Novice::LoadTexture("./Resources/Images/Player/PlayerFall.png");
	int playerattack_gra = Novice::LoadTexture("./Resources/Images/Player/PlayerAttack.png");

	int bg1_gra = Novice::LoadTexture("./Resources/images/Background/Background1.png"); //bg = background
	int bg2_gra = Novice::LoadTexture("./Resources/images/Background/Background2.png");
	int bg3_gra = Novice::LoadTexture("./Resources/images/Background/Background3.png");
	int bg5_gra = Novice::LoadTexture("./Resources/images/Background/Background5.png");
	int bg6_gra = Novice::LoadTexture("./Resources/images/Background/Background6.png");
	int bg7_gra = Novice::LoadTexture("./Resources/images/Background/Background7.png");

	int orbitImg = Novice::LoadTexture("./Resources/Images/kidou.png");

	int uptorunedo = Novice::LoadTexture("./Resources/Images/Boss2/Uptorune-do.png");
	int keeptorunedo = Novice::LoadTexture("./Resources/Images/Boss2/keeptorune-do.png");

	//int background = Novice::LoadTexture("./Resources/Images/background.png");
	Randam::SRAND();

	//test

	//tutorial.unko();

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
		

		screen.Scroll_update(playermain.GetPlayerQuad().LeftTop.x + playermain.ReturnPulsScroll(), playermain.GetPlayerQuad().LeftTop.y, 1.25);
		
		switch (scene)
		{
		case title:
			//タイトル処理

			if (tutorial.PlayerGoNext(playermain.GetPlayerPos().x)) {
				isFeedout = true;
			}

			if (Key::IsTrigger(DIK_R) && isFeedout == false && isFeedin == false) {
				isFeedout = true;
			}

			if (isTitleStart == false) {
				isFeedin = true;
				if (feedinT >= 1) {
					InitFeedin();
					isTitleStart = true;
				}
			}

			if (feedoutT >= 1) {
				playermain.Init();
				InitFeedout();
				isTitleStart = false;
				scene = stage;
				isFeedin = true;
				//isMovie = true;
			}

			playermain.Move();

			//tutorial.HitLetAttack(playermain.GetSwordQuad());

			for (int i = 0; i < 2; i++) {
				playermain.SwordHit(tutorial.GetLetAttackQuad(i));
			}

			tutorial.Update();

			break;
		case stage:
			//ステージ処理
			//if(boss.IsLife==false&&boss2.IsLife==false)

			if (isMovie == true) {
				playermain.Movie();
				boss.Movie();
			}
			
			if (stopper.Pause() == false) {
				screen.Pause(false);
				if (stopper.HitStopUpdate() == false) {
					playermain.Move();
					if (boss.IsLife==false&&boss2.IsLife==false) {
						//第二形態のセットここで
						boss2.Set();
					}
					//bossのアップデート
					if(boss.IsLife==true) {

						///デバック用
						//boss.IsLife = false;
						///デバック用

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
							if (boss2.centerOfDarknessUnder.particles[i].isActive == true) {
								playermain.PlayerHit({ boss2.centerOfDarknessUnder.particles[i].quad.GetCenter(),boss2.centerOfDarknessUnder.particles[i].quad.GetWidth() / 2 });
								playermain.PlayerHit({ boss2.centerOfDarknessLeft.particles[i].quad.GetCenter(),boss2.centerOfDarknessLeft.particles[i].quad.GetWidth() / 2 });
								playermain.PlayerHit({ boss2.centerOfDarknessRight.particles[i].quad.GetCenter(),boss2.centerOfDarknessRight.particles[i].quad.GetWidth() / 2 });
							}
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
					if (boss.IsLife) {
						enemySwordEffect.Update(boss.GetSwordAttack(), boss.GetBossBladeQuad());
					}
					else {
						enemySwordEffect.Update(false, boss.GetBossBladeQuad());
					}

					if (boss.RedBlackEffectFlag()) {
						bossBodyEffect.Update(boss.IsLife, boss.GetBossQuad(boss.body));
						bossHeadEffect.Update(boss.IsLife, boss.GetBossQuad(boss.head));
						bossRightArmEffect.Update(boss.IsLife, boss.GetBossQuad(boss.rightarm));
						bossLeftArmEffect.Update(boss.IsLife, boss.GetBossQuad(boss.leftarm));
						bossLegEffect.Update(boss.IsLife, boss.GetBossQuad(boss.leg));
					}
					
					//boss2のエフェクト
					boss2.centerOfDarknessUnder.target = boss2.GetBossQuad().GetCenter();
					boss2.centerOfDarknessLeft.target = boss2.GetBossQuad().GetCenter();
					boss2.centerOfDarknessRight.target = boss2.GetBossQuad().GetCenter();

					boss2.centerOfDarknessUnder.deleteQuad = boss2.GetBossQuad();
					boss2.centerOfDarknessLeft.deleteQuad = boss2.GetBossQuad();
					boss2.centerOfDarknessRight.deleteQuad = boss2.GetBossQuad();

					boss2.centerOfDarknessUnder.Update( boss2.isCenterOfDarkness, { {0,-Floor},int(SCREEN_WIDTH * 1.25),30 });
					boss2.centerOfDarknessLeft.Update( boss2.isCenterOfDarkness, { {-30,SCREEN_HEIGHT - Floor},30,SCREEN_HEIGHT + Floor });
					boss2.centerOfDarknessRight.Update( boss2.isCenterOfDarkness, { {SCREEN_WIDTH * 1.25,SCREEN_HEIGHT - Floor},30,SCREEN_HEIGHT + Floor });
					
					//stageのeffect
					if (boss.RedBlackEffectFlag()) {
						stageEffect.Update(true, { {0,-Floor},int(SCREEN_WIDTH * 1.5),Floor });
					}
				
				}
			}
			else {
			screen.Pause(true);
			}
			

			 stopper.HitStopMake(playermain.HitStopOver());

			if (Key::IsTrigger(DIK_O) && isFeedout == false && isFeedin == false) {
				isFeedout = true;
				isGameover = true;
				boss.Init();
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
		
		
		
		FPS++;
		if (FPS >= 60) FPS = 0;

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		switch (scene)
		{
		case title:
			
		//title描画処理1
			background.Draw(screen, bg1_gra, bg2_gra, bg3_gra, bg5_gra, bg6_gra, bg7_gra);


			//Novice::ScreenPrintf(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, "Press R");

			tutorial.Draw(screen);
			
			
			playermain.Draw(screen, playerstand_gra, playerwalk_gra, playerdash_gra, playerjump_gra, playerfall_gra, playerattack_gra);

			break;
		case stage:
			if (isStageStart == false) {
				isFeedin = true;
				if (feedinT >= 1) {
					InitFeedin();
					isStageStart = true;
				}
				
			}
			//ステージ描画処理
			//背景d

			background.Draw(screen, bg1_gra, bg2_gra, bg3_gra,bg5_gra,bg6_gra, bg7_gra);

			//Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, BLACK, kFillModeSolid);
			//Novice::SetBlendMode(kBlendModeAdd);
			//screen.DrawQuad2Normal(0 - screen.Scroll.x, 0, SCREEN_WIDTH * 1.25, SCREEN_HEIGHT, 0, 0, SCREEN_WIDTH * 1.25, SCREEN_HEIGHT, background, WHITE);
			//Novice::SetBlendMode(kBlendModeNormal);

			//エフェクト描画
			playerEffect.Draw(screen, 128, quadBlueEffectImg, WHITE, kBlendModeAdd);
			enemySwordEffect.Draw(screen, 128, quadRedEffectImg, WHITE, kBlendModeAdd);
			if (boss.RedBlackEffectFlag()) {
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
			}
			boss2.centerOfDarknessRight.Draw(screen, 128, circleEffectImg, RED, kBlendModeAdd);
			boss2.centerOfDarknessRight.Draw(screen, 128, circleEffectImg, BLACK, kBlendModeNormal);
			boss2.centerOfDarknessLeft.Draw(screen, 128, circleEffectImg, RED, kBlendModeAdd);
			boss2.centerOfDarknessLeft.Draw(screen, 128, circleEffectImg, BLACK, kBlendModeNormal);
			boss2.centerOfDarknessUnder.Draw(screen, 128, circleEffectImg, RED, kBlendModeNormal);
			boss2.centerOfDarknessUnder.Draw(screen, 128, circleEffectImg, BLACK, kBlendModeNormal);
			boss2.chaseEffect.Draw(screen, 128, circleRedEffectImg, WHITE);
			//プレイヤー描画
			playermain.Draw(screen, playerstand_gra, playerwalk_gra, playerdash_gra, playerjump_gra, playerfall_gra,playerattack_gra);
			
			//ボス描画
			if (boss.IsLife == true) {

				boss.Draw(screen, bossImg, bossheadImg, bossbodyImg, bosslegImg, bossleftarmImg, bossrightarmImg, deadbossbodyImg,deadbossleftarmImg, deadbossrightarmImg);
			}
			if (boss2.IsLife == true) {
				boss2.Draw(screen);
			}

			//BulletAttack
			boss2.swordEffect.Draw(screen, 128, circleEffectImg, RED, kBlendModeAdd);
			for (int i = 0; i < swordNum; i++) {

				if (boss2.isRelease == true && boss2.swordT[i] >= 0.0f) {

					/*screen.DrawQuad2(boss2.effectSword[i], 0, 0, 128, 128, orbitImg, boss2.orbitColor[i]);*/
				}
				if (boss2.isSword[i] == true) {
					screen.DrawQuad2(boss2.sword[i], 0, 0, 128, 128, quadRedEffectImg, WHITE);
				}
			}

			//rotatebullet
			for (int i = 0; i < rotateBulletNum; i++) {
				if (boss2.isRotateBullet[i] == true && boss2.isFeedrotateBullet == false) {
					screen.DrawQuad2(boss2.rotateBullet[i], 0, 0, 128, 128, quadRedEffectImg, WHITE);
				}
				if (boss2.isRotateBullet[i] == true && boss2.isFeedrotateBullet == true) {
					screen.DrawQuad2(boss2.rotateBullet[i], 0, 0, 128, 128, quadRedEffectImg, Feed::Feedout(boss2.rotateBulletT[i], 0.01f, WHITE));
				}
			}

			//nyokkiAttack
			if (boss2.isNyokki == true) {
				for (int i = 0; i < nyokkiNum/2; i++) {
					if (boss2.nyokkistats == boss2.Up) {
						screen.DrawQuad2Renban(boss2.leftNyokki[i].Quad, boss2.leftNyokkiUpSrcX[i], 0, 108, 890, boss2.nyokkiUpSheets, boss2.nyokkiSwitchAnimationFrame, boss2.nyokkiUpAnimationFrame,uptorunedo,WHITE,false );
						if (screen.isPause == false) {
							boss2.nyokkiUpAnimationFrame--;
						}
						screen.DrawQuad2Renban(boss2.rightNyokki[i].Quad, boss2.rightNyokkiUpSrcX[i], 0, 108, 890, boss2.nyokkiUpSheets, boss2.nyokkiSwitchAnimationFrame, boss2.nyokkiUpAnimationFrame, uptorunedo, WHITE, false);
						if (screen.isPause == false) {
							boss2.nyokkiUpAnimationFrame--;
						}
					}
					if (boss2.nyokkistats == boss2.Keep) {
						if (boss2.isFeedNyokki == false) {
							screen.DrawQuad2Renban(boss2.leftNyokki[i].Quad, boss2.leftNyokkiKeepSrcX[i], 0, 108, 890, boss2.nyokkiKeepSheets, boss2.nyokkiSwitchAnimationFrame, boss2.nyokkiKeepAnimationFrame, keeptorunedo, WHITE, false);
							if (screen.isPause == false) {
								boss2.nyokkiKeepAnimationFrame--;
							}
							screen.DrawQuad2Renban(boss2.rightNyokki[i].Quad, boss2.rightNyokkiKeepSrcX[i], 0, 108, 890, boss2.nyokkiKeepSheets, boss2.nyokkiSwitchAnimationFrame, boss2.nyokkiKeepAnimationFrame, keeptorunedo, WHITE, false);
							if (screen.isPause == false) {
								boss2.nyokkiKeepAnimationFrame--;
							}
						}
						if (boss2.isFeedNyokki == true) {
							screen.DrawQuad2Renban(boss2.leftNyokki[i].Quad, boss2.leftNyokkiKeepSrcX[i], 0, 108, 890, boss2.nyokkiKeepSheets, boss2.nyokkiSwitchAnimationFrame, boss2.nyokkiKeepAnimationFrame, keeptorunedo, Feed::Feedout(boss2.leftNyokkiT[i],0.01f,WHITE), false);
							if (screen.isPause == false) {
								boss2.nyokkiKeepAnimationFrame--;
							}
							screen.DrawQuad2Renban(boss2.rightNyokki[i].Quad, boss2.rightNyokkiKeepSrcX[i], 0, 108, 890, boss2.nyokkiKeepSheets, boss2.nyokkiSwitchAnimationFrame, boss2.nyokkiKeepAnimationFrame, keeptorunedo, Feed::Feedout(boss2.rightNyokkiT[i], 0.01f, WHITE), false);
							if (screen.isPause == false) {
								boss2.nyokkiKeepAnimationFrame--;
							}
						}
					}
				}
			}
			//プレイヤーソード描画
			playermain.BladeDraw(screen, mainaBladeImg, upMainaBladeImg, downMainaBladeImg, upSubBladeImg, downSubBladeImg, subBladeImg, 0x20a8b4FF, kBlendModeAdd);
			playerEffectSword.Draw(screen, 128, circleEffectImg, 0x20a8b4FF, kBlendModeAdd);

			//ポーズ描画
			stopper.PauseDraw();

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
		
		
		Novice::ScreenPrintf(0, 400, "FPS:%0.1f", 1.0f / ((double)(clock() - offset) / CLOCKS_PER_SEC));
		offset = clock();

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
