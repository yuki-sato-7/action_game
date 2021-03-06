/**
 * @file TitleScene.cpp
 * @brief タイトルシーン管理クラスソースファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#include "TitleScene.h"

void TitleScene::Initialize() {

	//各画像の読み込み
	tittle_                = GraphicsDevice.CreateSpriteFromFile(_T("UI/tittle_ui.png"));
	press_start_           = GraphicsDevice.CreateSpriteFromFile(_T("UI/press_start.png"));
	operation_explanation_ = GraphicsDevice.CreateSpriteFromFile(_T("UI/operation_explanation.png"));
	operation_button       = GraphicsDevice.CreateSpriteFromFile(_T("UI/main_button.png"));
	MediaManager.Attach(GraphicsDevice);

	//各変数の初期化
	tittle_count_   = 0.0f;
	tittle_state_   = 0.0f;
	alpha_state_     = 0.0f;

    next_flag_      = false;
	select_se_flag_ = false;

	se_manager().Initialize();
	se_manager().OpBgmPlay();
	InputDevice.CreateGamePad(1);

}

TitleScene::~TitleScene()
{
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

void TitleScene::Update() {

	//ゲームパットの押した瞬間、押している状態取得
	pad_state_ = GamePad(0)->GetState();
	pad_buffer_ = GamePad(0)->GetBuffer();

	FlashInterval();

	if (pad_buffer_.IsPressed(GamePad_Button8)) {
		if (select_se_flag_ == false) {
			se_manager().SelectSePlay();
			select_se_flag_ = true;
		}
		next_flag_ = true;
	}

	if (next_flag_ == true) {
		tittle_count_++;
		if (tittle_count_ >= kAdjustTittleTime) {
			tittle_state_ = kAdjustTittleState;
		}
	}

	if (tittle_state_ == kAdjustTittleState) {
		if (pad_buffer_.IsPressed(GamePad_Button8)) {
			se_manager().SelectSePlay();
			//メインシーンを生成する
			SceneManager::ChangeScene(SceneManager::MAIN);
		}
	}
}

void TitleScene::Draw3D() {

}

void TitleScene::Draw2D() {

	if (tittle_state_ == 0) {
		SpriteBatch.Draw(*tittle_, Vector3_Zero);
		SpriteBatch.Draw(*press_start_, Vector3_Zero, alpha_clear_);
	}

	else if (tittle_state_ == 1) {
		SpriteBatch.Draw(*operation_explanation_, Vector3_Zero);
		SpriteBatch.Draw(*operation_button, Vector3_Zero, alpha_clear_);
	}
}

/**
 * @brief　文字を点滅させる処理
 */
void TitleScene::FlashInterval() {

	if (alpha_state_ == ALPHA_MIN)
	{
		alpha_clear_ -= kAdjustAlphaChange;

		if (alpha_clear_ <= 0.0f)
		{
			alpha_clear_ = 0.0f;
			alpha_state_ = ALPHA_MAX;
		}
	}

	//アルファ増やす
	if (alpha_state_ == ALPHA_MAX)
	{
		alpha_clear_ += kAdjustAlphaChange;

		if (alpha_clear_ >= kAdjustAlphaMax)
		{
			alpha_clear_ = kAdjustAlphaMax;
			alpha_state_ = ALPHA_MIN;
		}
	}
}