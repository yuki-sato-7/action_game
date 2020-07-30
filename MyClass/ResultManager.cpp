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
bool ResultManager::Initialize()
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
	alfa_state_          = 0.0f;

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
			game_over_bgm_flag_ = true;
		}
	}

	else if (game_clear_flag_ == true) {
		if (game_clear_bgm_flag_ == false) {
			se_manager().MainBgmStop();
			se_manager().GcBgmPlay();
			game_clear_bgm_flag_ = true;
		}
	}

	if (alfa_state_ == ALFA_MAX)
	{
		alfa_clear_ -= kAdjustAlfaChange_;

		if (alfa_clear_ <= 0.0f)
		{
			alfa_clear_ = 0.0f;
			alfa_state_ = ALFA_MIN;
		}
	}
	//アルファ増やす
	if (alfa_state_ == ALFA_MIN)
	{
		alfa_clear_ += kAdjustAlfaChange_;

		if (alfa_clear_ >= kAdjustAlfaMAX)
		{
			alfa_clear_ = kAdjustAlfaMAX;
			alfa_state_ = ALFA_MAX;
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
		SpriteBatch.Draw(*return_button_, Vector3_Zero, alfa_clear_);
	}

	else if(game_clear_flag_ == true) {
		SpriteBatch.Draw(*return_button_, Vector3_Zero, alfa_clear_);
		SpriteBatch.Draw(*game_clear_,    Vector3_Zero);
		
	}
	
	else if (time_over_flag_ == true) {
		SpriteBatch.Draw(*time_over_,     Vector3_Zero);
		SpriteBatch.Draw(*return_button_, Vector3_Zero, alfa_clear_);
	}

}

