/**
 * @file Result_Manager.cpp
 * @brief リザルト画面管理クラスソースファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#include "ResultManager.h"

/**
 * @brief リザルト管理クラスを初期化する
 * @return 常にtrue
 */
bool ResultManager::Initialize(EnemyManager& enemy_manager)
{
	//各画像の読み込み
	game_over_       = GraphicsDevice.CreateSpriteFromFile(_T("UI/Game Over.png"));
	game_clear_      = GraphicsDevice.CreateSpriteFromFile(_T("UI/GAME CLEAR_.png"));
	time_over_       = GraphicsDevice.CreateSpriteFromFile(_T("UI/TIME UP.png"));
	return_button_   = GraphicsDevice.CreateSpriteFromFile(_T("UI/RETURN_TO_ TITLE.png"));

	//各変数の初期化
	game_over_flag_      = false;
	game_clear_flag_     = false;
	time_over_flag_      = false;
	game_clear_bgm_flag_ = false;
	game_over_bgm_flag_  = false;
	alpha_state_          = 0.0f;

	time_manager().AddObserver(this);
	ui_manager().AddObserver(this);
	enemy_manager.AddObserver(this);

	return true;
}

/**
 * @brief リザルト管理クラスを描画する
 * @return 常にtrue
 */
void ResultManager::Update() {

	if (game_over_flag_ == true || time_over_flag_ == true) {
		if (game_over_bgm_flag_ == false) {
			se_manager().MainBgmStop();
			se_manager().GameOverBgmPlay();
			ui_manager().AllDelteObserver(this);
			time_manager().AllDelteObserver(this);
			game_over_bgm_flag_ = true;
		}
	}

	else if (game_clear_flag_ == true) {
		if (game_clear_bgm_flag_ == false) {
			se_manager().MainBgmStop();
			se_manager().GcBgmPlay();
			ui_manager().AllDelteObserver(this);
			time_manager().AllDelteObserver(this);
			game_clear_bgm_flag_ = true;
		}
	}

	if (alpha_state_ == ALPHA_MAX)
	{
		alpha_clear_ -= kAdjustAlphaChange_;

		if (alpha_clear_ <= 0.0f)
		{
			alpha_clear_ = 0.0f;
			alpha_state_ = ALPHA_MIN;
		}
	}
	//アルファ増やす
	if (alpha_state_ == ALPHA_MIN)
	{
		alpha_clear_ += kAdjustAlphaChange_;

		if (alpha_clear_ >= kAdjustAlphaMax)
		{
			alpha_clear_ = kAdjustAlphaMax;
			alpha_state_ = ALPHA_MAX;
		}
	}		
}

/**
 * @brief リザルト管理クラスを描画する
 * @return 常にtrue
 */
void ResultManager::Draw()
{
	if (game_over_flag_ == true) {
		SpriteBatch.Draw(*game_over_,     Vector3_Zero);
		SpriteBatch.Draw(*return_button_, Vector3_Zero, alpha_clear_);
	}

	else if(game_clear_flag_ == true) {
		SpriteBatch.Draw(*return_button_, Vector3_Zero, alpha_clear_);
		SpriteBatch.Draw(*game_clear_,    Vector3_Zero);
		
	}
	
	else if (time_over_flag_ == true) {
		SpriteBatch.Draw(*time_over_,     Vector3_Zero);
		SpriteBatch.Draw(*return_button_, Vector3_Zero, alpha_clear_);
	}

}

