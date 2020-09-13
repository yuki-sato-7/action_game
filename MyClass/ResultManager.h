/**
 * @file Result_Manager.h
 * @brief リザルト画面管理クラスヘッダーファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#pragma once
#include "ESGLib.h"
#include "SeManager.h"
#include "Enum.h"
#include "TimeManager.h"
#include "UiManager.h"
#include "EnemyManager.h"
#include "Observer.h"

class ResultManager : public IObserver
{
public:

	/**
 　　* @brief リザルト管理クラスを初期化する
　　 * @return 常にtrue
　　 */
	virtual bool Initialize(EnemyManager& enemy_manager);

	/**
 　　* @brief リザルト管理クラスを描画する
 　　*/
	virtual void Update();

	/**
 　　* @brief リザルト管理クラスを描画する
 　　*/
	virtual void Draw();

	//ゲームオーバー状態か取得
	bool GetGameOverFlag() { return game_over_flag_; };

	//タイムーオーバーか取得
	bool GetTimeOverFlag() { return time_over_flag_; };

	//ゲームクリア状態か取得
	bool GetGameClearFlag() { return game_clear_flag_; };

	//ゲームオーバー状態にする
	void  ResultManager::SetGameOverFlag() {
		game_over_flag_ = true;
	};

	//ゲームクリア状態にする
	void  ResultManager::SetGameClearFlag() {
		game_clear_flag_ = true;
	};

	//タイムオーバー状態にする
	void  ResultManager::SetTimeOverFlag() {
		time_over_flag_ = true;
	};

	/**
	 * @brief オブザーバーから通知で状態を切り替える
	 * @param[in] (notify) オブザーバーからの通知内容
	 */
	void ReceiveNotify(int notify) {
		switch (notify) {
		case TIME_OVER_STATE:
			SetTimeOverFlag();
			break;

		case GAME_OVER_STATE:
			SetGameOverFlag();
			break;

		case GAME_CLEAR_STATE:
			SetGameClearFlag();
			break;
		}
	}

	// シングルトンインスタンスの取得
	static ResultManager& GetInstance()
	{
		static ResultManager result_manager;
		return result_manager;
	}

private:
	//定数
	const float kAdjustAlphaChange_ = 0.02f;    //文字の透明度の
	const float kAdjustAlphaMax     = 1.0f;     //文字の透明度（最大）

	//!ゲームオーバー画面
	SPRITE game_over_;

	//!ゲームクリア画面
	SPRITE game_clear_;

	//!タイムオーバー画面
	SPRITE time_over_;

	//!戻りボタン表示
	SPRITE return_button_;

	//!ゲームオーバー状態か
	bool game_over_flag_;

	//!ゲームクリア状態か
	bool game_clear_flag_;

	//!タイムオーバー状態か
	bool time_over_flag_;

	//!ゲームクリアBGMを鳴らしたか
	bool game_clear_bgm_flag_;

	//!タイムオーバーBGMを鳴らしたか
	bool game_over_bgm_flag_;

	//!文字の透明度
	float alpha_clear_;

	//!文字の透明度
	float alpha_state_;
	

	ResultManager() {} 

	ResultManager(const ResultManager&);
	ResultManager& operator=(const ResultManager&);
};

inline ResultManager& result_manager() { return ResultManager::GetInstance(); }