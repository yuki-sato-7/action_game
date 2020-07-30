/**
 * @file Se_Manager.cpp
 * @brief SE.BGM管理クラスソースファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#include "SeManager.h"
#include "Player.h"

/**
 * @brief SE.BGM管理クラスを初期化する
 * @return 常にtrue
 */
bool SeManager::Initialize()
{
	//各SE,BGMの読み込み
	if (hit_se_ == nullptr) {  //一度読んだら読み込まない
		hit_se_         = SoundDevice.CreateSoundFromFile(_T("Se/hit_bgm.wav"));
		punch_se_       = SoundDevice.CreateSoundFromFile(_T("Se/enemy_punch.wav"));
		explosion_se_   = SoundDevice.CreateSoundFromFile(_T("Se/enmy_explosion.wav"));
		main_bgm_       = SoundDevice.CreateMusicFromFile(_T("Se/main_bgm.wav"));
		select_se_      = SoundDevice.CreateSoundFromFile(_T("Se/select_se.wav"));
		op_bgm_         = SoundDevice.CreateMusicFromFile(_T("Se/op_bgm.wav"));
		game_over_bgm_  = SoundDevice.CreateMusicFromFile(_T("Se/over_bgm.wav"));
		game_clear_bgm_ = SoundDevice.CreateMusicFromFile(_T("Se/clear_bgm.wav"));
	}

	return true;
}

/**
 * @brief OPBGMを再生する
 */
void SeManager::OpBgmPlay() {
	op_bgm_->Play();
}

/**
 * @brief OPBGMを停止する
 */
void SeManager::OpBgmStop() {
	op_bgm_->Stop();
}

/**
 * @brief ゲームクリアBGMを再生する
 */
void SeManager::GcBgmPlay() {
	game_clear_bgm_->Play();
}

/**
 * @brief ゲームクリアBGMを停止する
 */
void SeManager::GcBgmStop() {
	game_clear_bgm_->Stop();
}

/**
 * @brief 決定音を再生する
 */
void SeManager::SelectSePlay() {

	select_se_->Play();
}

/**
 * @brief ヒット音を再生する
 */
void SeManager::HitSe()
{
	hit_se_->Play();
}

/**
 * @brief メインBGMを再生する
 */
void SeManager::MainBgmPlay()
{
	main_bgm_->Play();
}

/**
 * @brief メインBGMを停止する
 */
void SeManager::MainBgmStop()
{
    main_bgm_->Stop();
}

/**
 * @brief ゲームオーバーBGMを再生する
 * @param[in] (player) プレイヤー管理クラス
 */
void SeManager::GameOverBgmPlay()
{
    game_over_bgm_->Play();
}

/**
 * @brief ゲームオーバーBGMを停止する
 * @param[in] (player) プレイヤー管理クラス
 */
void SeManager::GameOverBgmStop()
{
	game_over_bgm_->Stop();
}

/**
 * @brief パンチ音を再生する
 */
void SeManager::PunchSePlay()
{
	punch_se_->Play();
}

/**
 * @brief 敵の爆発音を再生する
 */
void SeManager::ExplosionSePlay()
{
	explosion_se_->Play();
}