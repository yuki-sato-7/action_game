#include "TimeManager.h"

/**
 * @brief 時間管理クラスを初期化する
 * @return 常にtrue
 */
bool TimeManager::Initialize()
{
	//各変数の初期化
	start_time_count_ = 3000.0f;
	time_limit_count_ = 7200;

	game_start_       = false;
	time_limit_over_  = false;

	return true;
}

/**
 * @brief 更新（制限時間の計算）
 */
void TimeManager::Update()
{
	//制限時間の計算
	time_limit_count_ -= kAdjustTimeLimitMove;
	
	if (time_limit_count_ <= 0) {
		time_limit_over_ = true;
		result_manager().SetTimeOverFlag();
	}
}

/**
 * @brief ゲーム開始カウントダウンを計算する
 */
void TimeManager::GameStartCount()
{
	if (start_time_count_ >= -kAdjustCountTimeMin) {
		start_time_count_ -= GameTimer.GetElapsedMilliSecond();

		if (start_time_count_ < 0) {
			game_start_ = true;
		}
	}
}

/**
 * @brief 制限時間を計算する
*/
void TimeManager::TimeLimitCount()
{
	if (result_manager().GetGameClearFlag() == false && result_manager().GetGameOverFlag() == false && result_manager().GetTimeOverFlag() == false) {
		//制限時間の計算
		time_limit_count_ -= kAdjustTimeLimitMove;

		if (time_limit_count_ <= 0) {
			time_over_subject_.notifyObservers(TIME_OVER_STATE);  //タイムオーバーになったことをオブザーバーに通知
		}
	}
}