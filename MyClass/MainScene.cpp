/**
 * @file MainScene.cpp
 * @brief メインシーン管理クラスソースファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#include "MainScene.h"

MainScene::~MainScene()
{
	//フォントデータの削除
	RemoveFontResource(_T("Text/CAMELIAB.TTF"));

	MediaManager.ReleaseAllMedia();

	GraphicsDevice.ReleaseAllRenderTargets();
	GraphicsDevice.ReleaseAllStateBlocks();
	GraphicsDevice.ReleaseAllFonts();
	GraphicsDevice.ReleaseAllSprites();
	GraphicsDevice.ReleaseAllAnimationModels();
	GraphicsDevice.ReleaseAllModels();
	GraphicsDevice.ReleaseAllVertexBuffers();
	GraphicsDevice.ReleaseAllEffects();

}

void MainScene::Initialize() {

	//ファイルからフォントを読み込む
	AddFontResource(_T("CAMELIAB.TTF"));
	time_limit_font_       = GraphicsDevice.CreateSpriteFont(_T("Cameliabold"), 60);
	game_start_count_font_ = GraphicsDevice.CreateSpriteFont(_T("Cameliabold"), 100);

	//プレイヤークラスの初期化
	player.Initialize(enemy);
	
	//背景クラスの初期化
	ground.Initialize();

	//カメラクラスの初期化
	camera_main.Initialize(player);

	//エフェクトクラスの初期化
	effectmanager().Initialize(camera_main, player);

	//UIクラスの初期化
	ui_manager().Initialize();

	//時間管理クラスの初期化
	time_manager().Initialize();

	//敵の生成
	enemy.CreateEnemy(player, Vector3(   0, 0, 1235));
	enemy.CreateEnemy(player, Vector3(   0, 0, -1235));
	enemy.CreateEnemy(player, Vector3( 839, 0, 45));
	enemy.CreateEnemy(player, Vector3( 844, 0, 850));
	enemy.CreateEnemy(player, Vector3(-950, 0, -756));
	enemy.CreateEnemy(player, Vector3(-925, 0, 788));
	enemy.CreateEnemy(player, Vector3( 755, 0, -942));
	enemy.CreateEnemy(player, Vector3( 370, 0, 400));
	enemy.CreateEnemy(player, Vector3(-370, 0, -300));
	enemy.CreateEnemy(player, Vector3( 370, 0, -400));
	enemy.CreateEnemy(player, Vector3(-370, 0, 300));

	//ライトクラスの初期化
	my_light.Initialize();

	//リザルト画面クラスの初期化
	result_manager().Initialize(enemy);

	//メインBGMの再生
	se_manager().MainBgmPlay();

	//ゲームパットを使用可能にする
	InputDevice.CreateGamePad(1);

}

void MainScene::Update() {

	//ゲームパットの押した瞬間、押している状態取得
	pad_state_ = GamePad(0)->GetState();
	pad_buffer_ = GamePad(0)->GetBuffer();

	time_manager().GameStartCount();

	//カメラクラスのアップデート
	camera_main.Update(player, pad_buffer_, pad_state_);

	if (time_manager().GetGameStart() == true) {

		//アップデート前のプレイヤー座標取得
		Vector3 old_pos = player.GetPlayerPos();

		//プレイヤークラスのアップデート
		player.Update(ground, camera_main, enemy, pad_buffer_, pad_state_);

		//衝突判定クラスのアップデート
		collision_enemy.Update(enemy, player);

		//アップデート語のプレイヤー座標取得
		Vector3 new_pos = player.GetPlayerPos();

		//敵クラスのアップデート
		enemy.Update(player, ground);

		//カメラの座標の取得
		camera_main.GetCameraPos() += new_pos - old_pos;

		//UIクラスのアップデート
		ui_manager().Update();

		//エフェクトクラスのアップデート
		effectmanager().Update(camera_main);

		//制限時間のカウントスタート
		time_manager().TimeLimitCount();

		//リザルト画面管理クラスのアップデート
		result_manager().Update();

		//リザルト画面に遷移
		if (result_manager().GetGameClearFlag() == true ||
			result_manager().GetGameOverFlag() == true ||
			result_manager().GetTimeOverFlag() == true) {
			if (pad_buffer_.IsPressed(GamePad_Button8)) {
				se_manager().GcBgmStop();
				se_manager().GameOverBgmStop();
				SceneManager::ChangeScene(SceneManager::TITLE);
			}
		}
	}
}

void MainScene::Draw3D() {
	
	//床のモデル描画
	ground.GetModel()->Draw();

	//背景用モデル描画
	ground.GetModelWall()->Draw();

	//敵モデルの描画
	enemy.Draw();

	//プレイヤークラスの描画
	player.Draw();

	//エフェクトクラスの描画
	effectmanager().Draw(camera_main);			
}

void MainScene::Draw2D() {

	//カウントダウンタイマーの描画
	if (time_manager().GetStartTimeCount() > 0) {
		SpriteBatch.DrawString(game_start_count_font_, Vector2(600.0f, 200.0f), Color(255, 255, 255),
			_T("%d"), time_manager().GetStartTimeCount() / 1000 + 1);
	}

	else if (time_manager().GetStartTimeCount() < 0.0f && time_manager().GetStartTimeCount() > -1000.0f) {
		SpriteBatch.DrawString(game_start_count_font_, Vector2(280.0f, 200.0f), Color(255, 255, 255),
			_T("GAME START"));
	}

	//制限時間の描画
	if (time_manager().GetTimeLimitCount() > 660.0f) {
		SpriteBatch.DrawString(time_limit_font_, Vector2(600.0f, 20.0f), Color(255, 255, 255),
			_T("%d"), time_manager().GetTimeLimitCount() / 60);
	}
	else {
		SpriteBatch.DrawString(time_limit_font_, Vector2(600.0f, 20.0f), Color(255, 0, 0),
			_T("%d"), time_manager().GetTimeLimitCount() / 60);
	}

	//UIクラスの描画
	ui_manager().Draw();

	//リザルト画面の描画
	result_manager().Draw();
}

