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

class ResultManager
{
public:

	/**
 　　* @brief リザルト管理クラスを初期化する
　　 * @return 常にtrue
　　 */
	virtual bool Initialize();

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

	// シングルトンインスタンスの取得
	static ResultManager& GetInstance()
	{
		static ResultManager result_manager;
		return result_manager;
	}

private:
	//定数
	const float kAdjustAlfaChange_ = 0.02f;    //文字の透明度の
	const float kAdjustAlfaMAX     = 1.0f;     //文字の透明度（最大）

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

	//!ゲームクリア状態か
	bool game_clear_bgm_flag_;

	//!タイムオーバー状態か
	bool game_over_bgm_flag_;

	//!文字の透明度
	float alfa_clear_;

	//!文字の透明度
	float alfa_state_;
	

	ResultManager() {} 

	ResultManager(const ResultManager&);
	ResultManager& operator=(const ResultManager&);
};

inline ResultManager& result_manager() { return ResultManager::GetInstance(); }