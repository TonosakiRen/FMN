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
	int StyleChangeTornadoImg = Novice::LoadTexture("./Resources/Images/Boss/StyleChangeTornado.png");

	int playerstand_gra = Novice::LoadTexture("./Resources/Images/Player/PlayerStand.png");
	int playerwalk_gra = Novice::LoadTexture("./Resources/Images/Player/PlayerWalk.png");
	int playerdash_gra = Novice::LoadTexture("./Resources/Images/Player/PlayerDash.png");
	int playerjump_gra = Novice::LoadTexture("./Resources/Images/Player/PlayerJump.png");
	int playerfall_gra = Novice::LoadTexture("./Resources/Images/Player/PlayerFall.png");
	int playerattack_gra = Novice::LoadTexture("./Resources/Images/Player/PlayerAttack.png");
	int playerdeath_gra = Novice::LoadTexture("./Resources/Images/Player/PlayerDeath.png");

	int bg1_gra = Novice::LoadTexture("./Resources/images/Background/Background1.png"); //bg = background
	int bg2_gra = Novice::LoadTexture("./Resources/images/Background/Background2.png");
	int bg3_gra = Novice::LoadTexture("./Resources/images/Background/Background3.png");
	int bg5_gra = Novice::LoadTexture("./Resources/images/Background/Background5.png");
	int bg6_gra = Novice::LoadTexture("./Resources/images/Background/Background6.png");
	int bg7_gra = Novice::LoadTexture("./Resources/images/Background/Background7.png");

	int inPauseGra = Novice::LoadTexture("./Resources/images/UI/InPause.png");
	int PauseSelectGra = Novice::LoadTexture("./Resources/images/UI/PauseSelect.png");

	int Tutorial1 = Novice::LoadTexture("./Resources/images/Tutorial/1.png");
	int Tutorial2 = Novice::LoadTexture("./Resources/images/Tutorial/2.png");
	int Tutorial3 = Novice::LoadTexture("./Resources/images/Tutorial/3.png");
	int TutorialEx = Novice::LoadTexture("./Resources/images/Tutorial/PlayBoss.png");

	int LetJumpGra = Novice::LoadTexture("./Resources/images/Tutorial/LetJump.png");
	int LetAttackGra = Novice::LoadTexture("./Resources/images/Tutorial/LetAttack.png");
	int LetDashGra = Novice::LoadTexture("./Resources/images/Tutorial/LetDash.png");
		
	int orbitImg = Novice::LoadTexture("./Resources/Images/kidou.png");

	int uptorunedo = Novice::LoadTexture("./Resources/Images/Boss2/Uptorune-do.png");
	int keeptorunedo = Novice::LoadTexture("./Resources/Images/Boss2/keeptorune-do.png");

	boss.LoadGra();
	boss2.LoadGra();
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
					stopper.canselect = true;
				}
			}

			if (feedoutT >= 1) {
				playermain.Init();
				InitFeedout();
				isTitleStart = false;
				scene = stage;
				isFeedin = true;
				//isMovie = true;
				playermain.MovieInit();
				boss.Init();
				boss2.Init();
				//boss.MovieInit();
			}

			playermain.Move();

			for (int i = 0; i < 2; i++) {
				playermain.SwordHit(tutorial.GetLetAttackQuad(i));
			}

			playermain.PlayerHitKnockBack(tutorial.GetLetJumpQuad());
			playermain.PlayerHitKnockBack(tutorial.GetLetDashQuad());

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



			//tutorial.HitLetAttack(playermain.GetSwordQuad());

			

			tutorial.Update();

			break;
		case stage:
			//ステージ処理
			//if(boss.IsLife==false&&boss2.IsLife==false)
			

			if (boss.MovieEnded() == true) {
				isMovie = false;
			}

			if (isMovie == true) {
				playermain.Movie();
				boss.Movie();
				stopper.canselect = false;
			}
			else {
				stopper.canselect = true;
			}
			
			isPause = stopper.Pause();

			if (isPause == false) {
				screen.Pause(false);
				if (stopper.HitStopUpdate() == false) {



					playermain.Move();
					if (boss.IsLife == false && boss2.IsLife == false) {
						//第二形態のセットここで
						boss2.Set();
						boss2.PosLink(boss.GetBossX());
						boss.StyleChangeFalse();
						InitbossEffect();
						//bossのエフェクト
						boss.isWhiteFeedout = true;
						boss.isEmitwhite = false;
					}
					//bossのアップデート
					if (boss.IsLife == true) {


						///デバック用
						boss.IsLife = false;
						///デバック用

						boss.UpDate();
						boss.RandamMoveSelect(Randam::RAND(0, MAX_PATTERN - 1), playermain, screen);
						//boss.ShockWaveAttack2(playermain, screen);
						//当たり判定とかいれて！！！
						if (boss.isBossDead() == false) {
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
					}
					//boss2のアップデート
					if (boss2.IsLife == true) {
						

						//サウンド
						//sound.BGMStop(&sound.StageBgm);
						boss2.RandamMoveSelect(Randam::RAND(0, MAX2_PATTERN - 1), playermain, screen);
						boss2.UpDate();
						
						//当たり判定とかいれて！！！
						for (int i = 0; i < 30; i++) {
							if (boss2.centerOfDarknessUnder.particles[i].isActive == true) {
								playermain.PlayerHit({ boss2.centerOfDarknessUnder.particles[i].quad.GetCenter(),boss2.centerOfDarknessUnder.particles[i].quad.GetWidth() / 2.0f });
								playermain.PlayerHit({ boss2.centerOfDarknessLeft.particles[i].quad.GetCenter(),boss2.centerOfDarknessLeft.particles[i].quad.GetWidth() / 2.0f });
								playermain.PlayerHit({ boss2.centerOfDarknessRight.particles[i].quad.GetCenter(),boss2.centerOfDarknessRight.particles[i].quad.GetWidth() / 2.0f });
							}
						}
						if (boss2.iscenterNyokkiCollision == true) {
							for (int i = 0; i < 3; i++) {
								playermain.PlayerHit(boss2.centerNyokki[i]);
							}
						}
						if (boss2.isBulletAttack == true) {
							for (int i = 0; i < swordNum; i++) {
								if (boss2.isSword[i] == true) {
									playermain.PlayerHit({ boss2.sword[i].GetCenter(), boss2.sword[i].GetWidth() / 2.0f });
								}
							}
						}
						if (boss2.isUndertaleAttack == true) {
							if (boss2.isUndertaleCollision == false) {
								for (int i = 0; i < rotateBulletNum; i++) {
									if (boss2.isRotateBullet[i] == true) {
										playermain.PlayerHit({ boss2.rotateBullet[i].GetCenter(),boss2.rotateBullet[i].GetWidth() / 2.0f });
									}
								}
								for (int i = 0; i < chaseBulletNum; i++) {
									if (boss2.chaseEffect.particles[i].isActive == true) {
										playermain.PlayerHit({ boss2.chaseEffect.particles[i].quad.GetCenter(),boss2.chaseEffect.particles[i].quad.GetWidth() / 2.0f });
									}
								}
							}
						}

						if (boss2.isNyokkiCollsion == true) {
							for (int i = 0; i < nyokkiNum / 2; i++) {
								playermain.PlayerHit(boss2.leftNyokki[i].Quad);
								playermain.PlayerHit(boss2.rightNyokki[i].Quad);
							}
						}

						if (boss2.isAsgoreAttack == true) {
							for (int i = 0; i < boss2.emitNum; i++) {
								playermain.PlayerHit({ boss2.AsgoreBullet[i].quad.GetCenter(),boss2.AsgoreBullet[i].quad.GetWidth() / 2.0f});
							}
						}

						if (boss2.ismoveMoveAttack == true) {
							for (int i = 0; i < 4; i++) {
								if (boss2.ismoveBullet[i] == true) {
									playermain.PlayerHit({ boss2.moveBullet[i].GetCenter(),boss2.moveBullet[i].GetWidth() / 2.0f });
								}
							}
							for (int i = 0; i < 16; i++) {
								if (boss2.ismovemoveBullet[i] == true) {
									playermain.PlayerHit({ boss2.movemoveBullet[i].GetCenter(),boss2.movemoveBullet[i].GetWidth() / 2.0f });
								}
							}
						}

						if (boss2.TelechaseEffect.particles[0].isActive == true) {
							playermain.PlayerHit({ boss2.TelechaseEffect.particles[0].quad.GetCenter(),boss2.TelechaseEffect.particles[0].quad.GetWidth() / 2.0f });
						}

						//boss自体の当たり判定
						playermain.PlayerHit(boss2.GetBossQuad());
						playermain.SwordHit(boss2.GetBossQuad());
						boss2.BossHit(playermain.GetHitSword());

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

					for (int i = 0; i < kMAX_CIR; i++) {
						if (i == 0) {
							if (boss.Circleofdeath[i].Set == true) {
								white0.Update(boss.isEmitwhite, boss.isWhiteFeedout, boss.Circleofdeath[i].Quad_Pos, boss.Circleofdeath[i].Quad_Pos.GetCenter());
							}
							else {
								white0.Update(false, boss.isWhiteFeedout, boss.Circleofdeath[i].Quad_Pos, boss.Circleofdeath[i].Quad_Pos.GetCenter());
							}
						}
						if (i == 1) {
							if (boss.Circleofdeath[i].Set == true) {
								white1.Update(boss.isEmitwhite, boss.isWhiteFeedout, boss.Circleofdeath[i].Quad_Pos, boss.Circleofdeath[i].Quad_Pos.GetCenter());
							}
							else {
								white1.Update(false, boss.isWhiteFeedout, boss.Circleofdeath[i].Quad_Pos, boss.Circleofdeath[i].Quad_Pos.GetCenter());
							}
						}
						if (i == 2) {
							if (boss.Circleofdeath[i].Set == true) {
								white2.Update(boss.isEmitwhite, boss.isWhiteFeedout, boss.Circleofdeath[i].Quad_Pos, boss.Circleofdeath[i].Quad_Pos.GetCenter());
							}
							else {
								white2.Update(false, boss.isWhiteFeedout, boss.Circleofdeath[i].Quad_Pos, boss.Circleofdeath[i].Quad_Pos.GetCenter());
							}
						}
						if (i == 3) {
							if (boss.Circleofdeath[i].Set == true) {
								white3.Update(boss.isEmitwhite, boss.isWhiteFeedout, boss.Circleofdeath[i].Quad_Pos, boss.Circleofdeath[i].Quad_Pos.GetCenter());
							}
							else {
								white3.Update(false, boss.isWhiteFeedout, boss.Circleofdeath[i].Quad_Pos, boss.Circleofdeath[i].Quad_Pos.GetCenter());
							}
						}
						if (i == 4) {
							if (boss.Circleofdeath[i].Set == true) {
								white4.Update(boss.isEmitwhite, boss.isWhiteFeedout, boss.Circleofdeath[i].Quad_Pos, boss.Circleofdeath[i].Quad_Pos.GetCenter());
							}
							else {
								white4.Update(false, boss.isWhiteFeedout, boss.Circleofdeath[i].Quad_Pos, boss.Circleofdeath[i].Quad_Pos.GetCenter());
							}
						}
						if (i == 5) {
							if (boss.Circleofdeath[i].Set == true) {
								white5.Update(boss.isEmitwhite, boss.isWhiteFeedout, boss.Circleofdeath[i].Quad_Pos, boss.Circleofdeath[i].Quad_Pos.GetCenter());
							}
							else {
								white5.Update(false, boss.isWhiteFeedout, boss.Circleofdeath[i].Quad_Pos, boss.Circleofdeath[i].Quad_Pos.GetCenter());
							}
						}
						if (i == 6) {
							if (boss.Circleofdeath[i].Set == true) {
								white6.Update(boss.isEmitwhite, boss.isWhiteFeedout, boss.Circleofdeath[i].Quad_Pos, boss.Circleofdeath[i].Quad_Pos.GetCenter());
							}
							else {
								white6.Update(false, boss.isWhiteFeedout, boss.Circleofdeath[i].Quad_Pos, boss.Circleofdeath[i].Quad_Pos.GetCenter());
							}
						}
						
					}

					//boss2のエフェクト

					boss2Effect.Update(boss2.IsLife, boss2.GetBossQuad());

					boss2.centerOfDarknessUnder.target = boss2.GetBossQuad().GetCenter();
					boss2.centerOfDarknessLeft.target = boss2.GetBossQuad().GetCenter();
					boss2.centerOfDarknessRight.target = boss2.GetBossQuad().GetCenter();

					boss2.centerOfDarknessUnder.deleteQuad = Quad{ {boss2.GetBossQuad().GetCenter().x - 20,boss2.GetBossQuad().GetCenter().y + 20},40,40 };
					boss2.centerOfDarknessLeft.deleteQuad = Quad{ {boss2.GetBossQuad().GetCenter().x - 20,boss2.GetBossQuad().GetCenter().y + 20},40,40 };
					boss2.centerOfDarknessRight.deleteQuad = Quad{ {boss2.GetBossQuad().GetCenter().x - 20,boss2.GetBossQuad().GetCenter().y+20},40,40 };

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
			playermain.PauseLag();

				
			}

			boss.StyleChangeUpdate();

			if (isStageStart == false) {
				isFeedin = true;
				if (feedinT >= 1) {
					InitFeedin();
					isStageStart = true;
					stopper.canselect = true;
				}

			}
			

			 stopper.HitStopMake(playermain.HitStopOver());

			 if (stopper.ReturnRestartFlag() && isFeedout == false && isFeedin == false) {
				 stopper.RestartFlaggFalse();
				 isFeedout = true;
				 isRestart = true;
			 }

			 if (stopper.TitileBackFlag == true && isFeedout == false && isFeedin == false) {
				 isFeedout = true;
				 stopper.TitileBackFlag = false;
				 isTitle = true;
			 }

			if (playermain.Returngameoverflag() && isFeedout == false && isFeedin == false) {
				isFeedout = true;
				isGameover = true;
				stopper.canselect = false;
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
		
			playermain.Move();
			InitEffect();
			playermain.GameOver(screen);
			boss.Init();
			boss2.Init();
			gameoverclass.Update();

			if (gameoverclass.RestartFlag == true && isFeedout == false && isFeedin == false) {
				isFeedout = true;

				gameoverclass.RestartFlag = false;
			}
			if (feedoutT >= 1) {
				
				sound.BGMStop(&sound.GameOver);


			}
			
				

			
			break;
		case gameclear:
			//ゲームクリア処理
			isGameclear = false;
			if (Key::IsTrigger(DIK_R) && isFeedout == false && isFeedin == false) {
				isFeedout = true;
			}
			boss.Init();
			boss2.Init();
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
			sound.BGMStop(&sound.StageBgm);
			sound.BGMStop(&sound.StageBgm2);
			sound.BGMStop(&sound.GameClear);
			sound.BGMStop(&sound.GameOver);
			
			sound.BGM(&sound.Title,0.2f, "./Resources/sounds/TitleBgm.mp3");

		//title描画処理1
			background.Draw(screen, bg1_gra, bg2_gra, bg3_gra, bg5_gra, bg6_gra, bg7_gra);


			//Novice::ScreenPrintf(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, "Press R");

			tutorial.Draw(screen, Tutorial1, Tutorial2, Tutorial3, LetJumpGra, LetAttackGra, LetDashGra);
			
			playermain.BladeDraw(screen, mainaBladeImg, upMainaBladeImg, downMainaBladeImg, upSubBladeImg, downSubBladeImg, subBladeImg, 0x20a8b4FF, kBlendModeAdd);
			playerEffectSword.Draw(screen, 128, circleEffectImg, 0x20a8b4FF, kBlendModeAdd);
			playerEffect.Draw(screen, 128, quadBlueEffectImg, WHITE, kBlendModeAdd);
			
			playermain.Draw(screen, playerstand_gra, playerwalk_gra, playerdash_gra, playerjump_gra, playerfall_gra, playerattack_gra, playerdeath_gra);

			break;
		case stage:
			
			//サウンド
			sound.BGMStop(&sound.Title);
			
			sound.BGMStop(&sound.GameClear);
			sound.BGMStop(&sound.GameOver);

			//ステージ描画処理
			//背景d

			background.Draw(screen, bg1_gra, bg2_gra, bg3_gra,bg5_gra,bg6_gra, bg7_gra);

			//Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, BLACK, kFillModeSolid);
			//Novice::SetBlendMode(kBlendModeAdd);
			//screen.DrawQuad2Normal(0 - screen.Scroll.x, 0, SCREEN_WIDTH * 1.25, SCREEN_HEIGHT, 0, 0, SCREEN_WIDTH * 1.25, SCREEN_HEIGHT, background, WHITE);
			//Novice::SetBlendMode(kBlendModeNormal);

			//エフェクト描画
			playerEffect.Draw(screen, 128, quadBlueEffectImg, WHITE, kBlendModeAdd);
			boss2Effect.Draw(screen, 128, quadRedEffectImg, WHITE, kBlendModeAdd);
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
				white0.Draw(screen, 128, circleEffectImg, WHITE);
				white1.Draw(screen, 128, circleEffectImg, WHITE);
				white2.Draw(screen, 128, circleEffectImg, WHITE);
				white3.Draw(screen, 128, circleEffectImg, WHITE);
				white4.Draw(screen, 128, circleEffectImg, WHITE);
				white5.Draw(screen, 128, circleEffectImg, WHITE);
				white6.Draw(screen, 128, circleEffectImg, WHITE);

			}
			if (white0.particles[0].t >= 1.0f) {
				boss.isWhiteFeedout = false;
			}
			boss2.centerOfDarknessRight.Draw(screen, 128, circleRedEffectImg, RED, kBlendModeNormal);
			boss2.centerOfDarknessLeft.Draw(screen, 128, circleRedEffectImg, RED, kBlendModeNormal);
			boss2.centerOfDarknessUnder.Draw(screen, 128, circleRedEffectImg, BLACK, kBlendModeNormal);
			boss2.chaseEffect.Draw(screen, 128, circleRedEffectImg, WHITE);
			boss2.TelechaseEffect.Draw(screen, 128, circleRedEffectImg, WHITE);
			//プレイヤー描画
			playermain.Draw(screen, playerstand_gra, playerwalk_gra, playerdash_gra, playerjump_gra, playerfall_gra,playerattack_gra, playerdeath_gra);
			
			//ボス描画
			if (boss.IsLife == true) {
				//サウンド
				sound.BGMStop(&sound.StageBgm2);
				sound.BGM(&sound.StageBgm,0.1f, "./Resources/sounds/BossBgm.mp3");
				boss.Draw(screen, bossImg, bossheadImg, bossbodyImg, bosslegImg, bossleftarmImg, bossrightarmImg, deadbossbodyImg,deadbossleftarmImg, deadbossrightarmImg);
			}
			if (boss2.IsLife == true) {
				sound.BGMStop(&sound.StageBgm);
				sound.BGM(&sound.StageBgm2, "./Resources/sounds/Boss2Bgm.mp3");

				boss2.Draw(screen);
			}

			//CenterofDarkness
			if (boss2.iscenterNyokki == true) {
				for (int i = 0; i < 3; i++) {
					if (boss2.centerNyokkistats == boss2.Up) {
						Quad tmp1({ boss2.centerNyokki[i].LeftTop.x - 32.0f,boss2.centerNyokki[i].LeftTop.y + 32.0f }, 172, 952);
						screen.DrawQuad2Renban(tmp1, boss2.centerNyokkiUpSrcX[i], 0, 172, 952, boss2.centerNyokkiUpSheets, boss2.centerNyokkiSwitchAnimationFrame, boss2.centerNyokkiUpAnimationFrame, uptorunedo, WHITE, false);
						if (screen.isPause == false) {
							boss2.centerNyokkiUpAnimationFrame--;
						}

					}
					if (boss2.centerNyokkistats == boss2.Keep) {
						if (boss2.isFeedCenterNyokki == false) {
							Quad tmp2({ boss2.centerNyokki[i].LeftTop.x - 32.0f,boss2.centerNyokki[i].LeftTop.y + 32.0f }, 172, 952);
							screen.DrawQuad2Renban(tmp2, boss2.centerNyokkiKeepSrcX[i], 0, 172, 952, boss2.centerNyokkiKeepSheets, boss2.centerNyokkiSwitchAnimationFrame, boss2.centerNyokkiKeepAnimationFrame, keeptorunedo, WHITE, false);
							if (screen.isPause == false) {
								boss2.centerNyokkiKeepAnimationFrame--;
							}

						}
						if (boss2.isFeedCenterNyokki == true) {
							Quad tmp3({ boss2.centerNyokki[i].LeftTop.x - 32.0f,boss2.centerNyokki[i].LeftTop.y + 32.0f }, 172, 952);
							screen.DrawQuad2Renban(tmp3, boss2.centerNyokkiKeepSrcX[i], 0, 172, 952, boss2.centerNyokkiKeepSheets, boss2.centerNyokkiSwitchAnimationFrame, boss2.centerNyokkiKeepAnimationFrame, keeptorunedo, Feed::Feedout(boss2.centerNyokkiT[i], 0.1f, WHITE), false);
							if (screen.isPause == false) {
								boss2.centerNyokkiKeepAnimationFrame--;
							}

						}
					}
				}
			}

			//nyokkiAttack
			if (boss2.isNyokki == true) {
				for (int i = 0; i < nyokkiNum / 2; i++) {
					if (boss2.nyokkistats == boss2.Up) {
						Quad tmp4({ boss2.leftNyokki[i].Quad.LeftTop.x - 32.0f,boss2.leftNyokki[i].Quad.LeftTop.y + 32.0f }, 172, 952);
						screen.DrawQuad2Renban(tmp4, boss2.leftNyokkiUpSrcX[i], 0, 172, 952, boss2.nyokkiUpSheets, boss2.nyokkiSwitchAnimationFrame, boss2.nyokkiUpAnimationFrame, uptorunedo, WHITE, false);
						if (screen.isPause == false) {
							boss2.nyokkiUpAnimationFrame--;
						}
						Quad tmp5({ boss2.rightNyokki[i].Quad.LeftTop.x - 32.0f,boss2.rightNyokki[i].Quad.LeftTop.y + 32.0f }, 172, 952);
						screen.DrawQuad2Renban(tmp5, boss2.rightNyokkiUpSrcX[i], 0, 172, 952, boss2.nyokkiUpSheets, boss2.nyokkiSwitchAnimationFrame, boss2.nyokkiUpAnimationFrame, uptorunedo, WHITE, false);
						if (screen.isPause == false) {
							boss2.nyokkiUpAnimationFrame--;
						}
					}
					if (boss2.nyokkistats == boss2.Keep) {
						if (boss2.isFeedNyokki == false) {
							Quad tmp6({ boss2.leftNyokki[i].Quad.LeftTop.x - 32.0f,boss2.leftNyokki[i].Quad.LeftTop.y + 32.0f }, 172, 952);
							screen.DrawQuad2Renban(tmp6, boss2.leftNyokkiKeepSrcX[i], 0, 172, 952, boss2.nyokkiKeepSheets, boss2.nyokkiSwitchAnimationFrame, boss2.nyokkiKeepAnimationFrame, keeptorunedo, WHITE, false);
							if (screen.isPause == false) {
								boss2.nyokkiKeepAnimationFrame--;
							}
							Quad tmp7({ boss2.rightNyokki[i].Quad.LeftTop.x - 32.0f,boss2.rightNyokki[i].Quad.LeftTop.y + 32.0f }, 172, 952);
							screen.DrawQuad2Renban(tmp7, boss2.rightNyokkiKeepSrcX[i], 0, 172, 952, boss2.nyokkiKeepSheets, boss2.nyokkiSwitchAnimationFrame, boss2.nyokkiKeepAnimationFrame, keeptorunedo, WHITE, false);
							if (screen.isPause == false) {
								boss2.nyokkiKeepAnimationFrame--;
							}
						}
						if (boss2.isFeedNyokki == true) {
							Quad tmp8({ boss2.leftNyokki[i].Quad.LeftTop.x - 32.0f,boss2.leftNyokki[i].Quad.LeftTop.y + 32.0f }, 172, 952);
							screen.DrawQuad2Renban(tmp8, boss2.leftNyokkiKeepSrcX[i], 0, 172, 952, boss2.nyokkiKeepSheets, boss2.nyokkiSwitchAnimationFrame, boss2.nyokkiKeepAnimationFrame, keeptorunedo, Feed::Feedout(boss2.leftNyokkiT[i], 0.1f, WHITE), false);
							if (screen.isPause == false) {
								boss2.nyokkiKeepAnimationFrame--;
							}
							Quad tmp9({ boss2.rightNyokki[i].Quad.LeftTop.x - 32.0f,boss2.rightNyokki[i].Quad.LeftTop.y + 32.0f }, 172, 952);
							screen.DrawQuad2Renban(tmp9, boss2.rightNyokkiKeepSrcX[i], 0, 172, 952, boss2.nyokkiKeepSheets, boss2.nyokkiSwitchAnimationFrame, boss2.nyokkiKeepAnimationFrame, keeptorunedo, Feed::Feedout(boss2.rightNyokkiT[i], 0.1f, WHITE), false);
							if (screen.isPause == false) {
								boss2.nyokkiKeepAnimationFrame--;
							}
						}
					}
				}
			}

			//ボス描画
			if (boss.IsLife == true) {

				boss.Draw(screen, bossImg, bossheadImg, bossbodyImg, bosslegImg, bossleftarmImg, bossrightarmImg, deadbossbodyImg,deadbossleftarmImg, deadbossrightarmImg);
			}
			if (boss2.IsLife == true) {
				boss2.Animation();
				boss2.Draw(screen);
			}

			//CenterofDarkness
			

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
					screen.DrawQuad2(boss2.rotateBullet[i], 0, 0, 128, 128, quadRedEffectImg, Feed::Feedout(boss2.rotateBulletT[i], 0.1f, WHITE));
				}
			}

			

			//AsgoreAttack
			for (int i = 0; i < boss2.emitNum; i++) {
				if (boss2.AsgoreBullet[i].isBullet == true) {
					if (boss2.isAsgoreFeed == true) {
						screen.DrawQuad2(boss2.AsgoreBullet[i].quad, 0, 0, 128, 128, circleRedEffectImg, Feed::Feedout(boss2.AsgoreBullet[i].t,0.1,WHITE));
					}
					else {
						screen.DrawQuad2(boss2.AsgoreBullet[i].quad, 0, 0, 128, 128, circleRedEffectImg, WHITE);
					}
				}
			}

			//moveAttack
			for (int i = 0; i < 4; i++) {
				if (boss2.ismoveBullet[i] == true) {
					if (boss2.moveIsFeedout == false) {
						screen.DrawQuad2(boss2.moveBullet[i], 0, 0, 128, 128, circleRedEffectImg, Feed::Feedin(boss2.moveAttackBulletFeedinT[i], 0.1f, WHITE));
					}
					else {
						screen.DrawQuad2(boss2.moveBullet[i], 0, 0, 128, 128, circleRedEffectImg, Feed::Feedout(boss2.moveAttackBulletFeedoutT[i], 0.1f, WHITE));
					}


				}
			}
			for (int i = 0; i < 16; i++) {
				if (boss2.ismovemoveBullet[i] == true) {
					if (boss2.moveIsFeedout == false) {
						screen.DrawQuad2(boss2.movemoveBullet[i], 0, 0, 128, 128, circleRedEffectImg, Feed::Feedin(boss2.movemoveAttackBulletFeedinT[i], 0.1f, WHITE));
					}
					else {
						screen.DrawQuad2(boss2.movemoveBullet[i], 0, 0, 128, 128, circleRedEffectImg, Feed::Feedout(boss2.movemoveAttackBulletFeedoutT[i], 0.1f, WHITE));
					}
				}
			}

			boss.DrawStyleChange(screen, StyleChangeTornadoImg);

			//プレイヤーソード描画
			playermain.BladeDraw(screen, mainaBladeImg, upMainaBladeImg, downMainaBladeImg, upSubBladeImg, downSubBladeImg, subBladeImg, 0x20a8b4FF, kBlendModeAdd);
			playerEffectSword.Draw(screen, 128, circleEffectImg, 0x20a8b4FF, kBlendModeAdd);

			//ポーズ描画

			stopper.PauseDraw(inPauseGra, PauseSelectGra);

			if (isPause == true) {
				tutorial.PlayDrawEx(TutorialEx, 1);
			}
			else {
				tutorial.PlayDrawEx(TutorialEx, 0);
			}

			if (feedoutT >= 1 ) {
				InitFeedout();
				isStageStart = false;
				if (isGameover == true) {
					sound.BGM(&sound.GameOver, "./Resources/sounds/GameOverBgm.mp3");

					scene = gameover;
					isFeedin = true;
				}
				if (isGameclear == true) {
					scene = gameclear;
					isFeedin = true;
				}
				if (isRestart == true) {
					isRestart = false;
					isFeedin = true;
					if (boss.IsLife == true) {
						boss.Init();
						
					}
					else {
						boss2.Set();
					}
					playermain.Init();
					stopper.isPauseFalse();
				}
				if (isTitle == true) {
					scene = title;
					isFeedin = true;
					playermain.Init();
					isTitle = false;
				}
			}
			else {
				break;
			}

			break;
		case gameover:
			if (isGameoverStart == false) {
				isFeedin = true;
				if (feedinT >= 1) {
					InitFeedin();
					isGameoverStart = true;
					gameoverclass.canselect = true;
				}
			}
			//ゲームオーバー描画処理
			//Novice::ScreenPrintf(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, "Press R");
			//sound.BGM(&sound.GameOver, "./Resources/sounds/GameOverBgm.mp3");

			//サウンド
			sound.BGMStop(&sound.StageBgm);
			sound.BGMStop(&sound.StageBgm2);
			sound.BGMStop(&sound.GameClear);
			sound.BGMStop(&sound.Title);

			Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, BLACK, kFillModeSolid);

			gameoverclass.Draw(screen, PauseSelectGra);

			playermain.Draw(screen, playerstand_gra, playerwalk_gra, playerdash_gra, playerjump_gra, playerfall_gra, playerattack_gra,playerdeath_gra);

			tutorial.PlayDrawEx(TutorialEx, 1);

			if (feedoutT >= 1) {
				InitFeedout();
				InitEffect();
				if (boss.IsLife == true) {
					boss.Init();
				}
				else {
					boss2.Set();
				}
				playermain.Init();
				playermain.Move();
				boss.UpDate();
				boss2.UpDate();
				stopper.canselect = true;
				isGameoverStart = false;
				scene = stage;
				isFeedin = true;
				//サウンド
				sound.BGMStop(&sound.GameOver);
			}
			
			break;
		case gameclear:
			if (isGameclearStart == false) {
				isFeedin = true;
				if (feedinT >= 1) {
					InitFeedin();
					isGameclearStart = true;
				}
			}
			//ゲームクリア描画

			Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, BLACK, kFillModeSolid);
			
			tutorial.PlayDrawEx(TutorialEx, 1);
			//サウンド
			sound.BGMStop(&sound.StageBgm);
			sound.BGMStop(&sound.StageBgm2);
			sound.BGMStop(&sound.Title);
			sound.BGMStop(&sound.GameOver);
			sound.BGM(&sound.GameClear, "./Resources/sounds/GameClear.mp3");
			if (feedoutT >= 1) {
				InitFeedout();
				InitEffect();
				isGameclearStart = false;
				scene = stage;
				isFeedin = true;
			}
			else {
				break;
			}
			break;
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
		if (Key::IsTrigger(DIK_ESCAPE) || stopper.ReturnQuitFlag() == true || gameoverclass.QuitFlag == true) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
