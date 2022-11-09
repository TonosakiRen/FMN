#include "main.h"
#include "Randam.h"

const char kWindowTitle[] = "FMN";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, SCREEN_WIDTH, SCREEN_HEIGHT);



	Controller::SetLeftStickDeadZone(0, 14000);


	int tex = Novice::LoadTexture("white1x1.png");
	int effect01Img = Novice::LoadTexture("./Resources/Images/Effect01.png");
	int effect02Img = Novice::LoadTexture("./Resources/Images/Effect02.png");
	int effect03Img = Novice::LoadTexture("./Resources/Images/Effect03.png");
	int effect04Img = Novice::LoadTexture("./Resources/Images/Effect04.png");
	int effect05Img = Novice::LoadTexture("./Resources/Images/Effect05.png");
	int bossImg = Novice::LoadTexture("./Resources/Images/Boss/Boss.png");
	int bossheadImg = Novice::LoadTexture("./Resources/Images/Boss/Head.png");
	int bossbodyImg = Novice::LoadTexture("./Resources/Images/Boss/Body.png");
	int bosslegImg = Novice::LoadTexture("./Resources/Images/Boss/Leg.png");
	int bossrightarmImg = Novice::LoadTexture("./Resources/Images/Boss/RightArm.png");
	int bossleftarmImg = Novice::LoadTexture("./Resources/Images/Boss/LeftArm.png");
	int ziki = Novice::LoadTexture("./Resources/Images/ziki.png");
	int background = Novice::LoadTexture("./Resources/Images/background.png");
	Randam::SRAND();



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

		if (stopper.Pause() == false) {
			if (stopper.HitStopUpdate() == false) {
				playermain.Move();
				boss.UpDate();
				boss.RandamMoveSelect(Randam::RAND(0, MAX_PATTERN - 1), playermain, screen);

				playermain.PlayerHit(boss.GetBossAttackQuad(), screen);
				for (int i = 0; i < 5; i++) {
					playermain.PlayerHit(boss.GetBossQuad(i), screen);
					playermain.SwordHit(boss.GetBossQuad(i));
				}

				boss.BossHit(playermain.GetHitSword());

				effect01.Update(true, playermain.GetPlayerQuad());
				effect02.Update(boss.GetSwordAttack(), boss.GetBossBladeQuad());
				effect03.Update(true,{{0,-Floor},SCREEN_WIDTH,Floor});

				if (playermain.GetHitSword() == true) {
					if (playermain.GetisFaceUp()) {
						effect04.minDirection = { -0.6f , 0.1f };
						effect04.maxDirection = { 0.6f , 0.9f };
					}else if (playermain.GetisFaceDown()) {
						effect04.minDirection = { -0.6f , -0.1f };
						effect04.maxDirection = { 0.6f , -0.9f };
					}else if (playermain.GetisFaceRigh()) {
						effect04.minDirection = { 0.1f,-0.6f };
						effect04.maxDirection = { 0.9f,0.6f };
					}
					else {
						effect04.minDirection = { -0.9f,-0.6f };
						effect04.maxDirection = { -0.1f,0.6f };
					}
					
				}
				effect04.Update(playermain.GetHitSword(), playermain.GetHitAttackPos());
			}
		}


		stopper.HitStopMake(playermain.HitStopOver());
		

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, BLACK, kFillModeSolid);

		Novice::SetBlendMode(kBlendModeAdd);
		screen.DrawQuad2Normal(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, background, WHITE);
		Novice::SetBlendMode(kBlendModeNormal);
		effect01.Draw(screen, 128, effect04Img, WHITE, kBlendModeAdd);
		effect02.Draw(screen, 128, effect01Img, WHITE, kBlendModeAdd);
		effect03.Draw(screen, 128, effect03Img, RED, kBlendModeAdd);
		effect04.Draw(screen, 128, effect03Img, 0x20a8b4FF, kBlendModeAdd);
		playermain.Draw(screen,ziki);
		boss.Draw(screen,bossImg, bossheadImg, bossbodyImg,bosslegImg,bossleftarmImg,bossrightarmImg
		);
		
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
