/**
 * @file TimeManager.h
 * @brief 時間管理クラスヘッダーファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#pragma once
#include "ESGLib.h"
#include "ResultManager.h"
#include "Observer.h"
#include "Enum.h"

class TimeManager
{
public:

	/**
 　　* @brief 時間管理クラスを初期化する
　　 * @return 常にtrue
　　 */
	virtual bool Initialize();

	/**
　　 * @brief 更新（制限時間の計算）
 　　*/
	virtual void Update();

	/**
　　 * @brief ゲーム開始カウントダウンを計算する
 　　*/
	void GameStartCount();

	/**
　　 * @brief 制限時間を計算する
 　　*/
	void TimeLimitCount();
	
	//ゲームスタートのカウントを取得する
	int GetStartTimeCount() { return start_time_count_; }; 

	//制限時間を取得する
	int GetTimeLimitCount() { return time_limit_count_; };

	//ゲームスタートか取得する
	bool GetGameStart() { return game_start_; };

	//ゲームスタートか取得する
	bool GetTimeLimitOver() { return time_limit_over_; };

	/**
　　 * @brief オブザーバーに新たなオブザーバーを追加
	 * @param[in] (notify) オブザーバーの通知内容
 　　*/
	void AddObserver(IObserver* observer)
	{
		time_over_subject_.addObserver(observer);
	}

	/**
　　 * @brief オブザーバーのリストからオブザーバーを削除
	 * @param[in] (notify) オブザーバーの通知内容
 　　*/
	void RemoveObserver(IObserver* observer)
	{
		time_over_subject_.removeObserver(observer);
	}

	/**
　　 * @brief リストに登録されているオブザーバーの変化を通知
	 * @param[in] (notify) オブザーバーの通知内容
 　　*/
	void AllDelteObserver(IObserver* observer)
	{
		time_over_subject_.alldelteObservers();
	}

	static TimeManager& GetInstance()
	{
		static TimeManager time_manager;
		return time_manager;
	}

private:
	// 定数
	const float kAdjustTimeLimitMove = 1.0f;     //制限時間の変化する速度調整
	const float kAdjustCountTimeMin  = 2000.0f;  //カウントダウンを消す時間調整

	//!ゲームスタートのカウント
	int start_time_count_;

	//!制限時間
	int time_limit_count_;

	//!ゲームスタートか判断
	bool game_start_;

	//!制限時間
	int time_limit_over_;

	Subject time_over_subject_;

	TimeManager() {} 

	TimeManager(const TimeManager&);
	TimeManager& operator=(const TimeManager&);
};

inline TimeManager& time_manager() { return TimeManager::GetInstance(); }


